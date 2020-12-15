#include "hls.h"

int Process(HLS*, string);
int processXBitrate(HLS*, Node*, string);
int processXStreamInf(HLS*, Node*);
int processXIFrameStreamInf(HLS*, Node*);
int processXMedia(HLS*, Node*);
string getAttrib(string, string, string);

HLS* CreateHLS()
{
    HLS* hls = (HLS*) malloc(sizeof(HLS));
    hls->DeleteHLS = &DeleteHLS;
    hls->Process = &Process;
    
    hls->version = -1;
    hls->segmentsDependent = 1;

    hls->variantStreams = CreateList();
    hls->iFrameStreams = CreateList();
	hls->media = CreateList();
    
    string template = (string)malloc(19 * sizeof(char));
	strncpy(template, "/tmp/tempdirXXXXXX", 19);
    hls->tempDir = mkdtemp(template);
    return hls;
}

void DeleteHLS(HLS* self)
{
    // Remove temp folder
    rmdir(self->tempDir);

    self->baseurl->DeleteURLData(self->baseurl);    
    //self->list->DeleteList(self->list);
    free(self);
}

int Process(HLS* self, string out)
{
    int retCode = 0;

    Node* node = self->list->head;
    for(int i = 0; i < self->list->length; i++)
    {
        #ifdef DEBUG
        printf("INPUT: %s --- %s --- %s\n", node->tag, node->attribute, node->value);
        #endif /* DEBUG */

        if (strstr(EXT_X_VERSION, node->tag) != NULL)
            self->version = atoi(node->attribute);

        if (strstr(EXT_IS_INDEPENDENT_SEGMENTS, node->tag) != NULL)
            self->segmentsDependent = 0;

        if (strstr(EXT_X_BITRATE, node->tag) != NULL)
            processXBitrate(self, node, out);

        if (strstr(EXT_X_ENDLIST, node->tag) != NULL)
            // TODO finish all
            printf("List Ended");

        if (strstr(EXT_X_STREAM_INF, node->tag) != NULL)
            processXStreamInf(self, node);
        
        if (strstr(EXT_X_STREAM_INF, node->tag) != NULL)
            processXIFrameStreamInf(self, node);
        
        if (strstr(EXT_X_MEDIA, node->tag) != NULL)
            processXMedia(self, node);
            

        // Get next node
        node = node->next;
    }

    return retCode;
}

int processXBitrate(HLS* self, Node* node, string out)
{
    int retCode = 0;
    int urlLength = 0;
    string url = NULL;
    struct stat sb;
    string filepath;
    string temp;

    
    // Check the node value is filename or whole url
    if (strlen(self->baseurl->baseurl) + strlen(node->value) != strlen(self->baseurl->url))
    {
        urlLength = strlen(self->baseurl->baseurl) + strlen(node->value) + 1;
        url = (string)malloc(urlLength * sizeof(char));
        memcpy(url, self->baseurl->baseurl, strlen(self->baseurl->baseurl) + 1);

        
        strcat(url, node->value);
    }

    #ifdef DEBUG
    printf("Download: %s\n", url);
    #endif /* DEBUG */
	
    
    // If tempdir exists
    if (stat(self->tempDir, &sb) == 0 && S_ISDIR(sb.st_mode)) 
    {
        // If Value is filename
        if (url != NULL)
        {
            filepath = (string)malloc((strlen(self->tempDir) + strlen(node->value) + 1) * sizeof(char));
            strncpy(filepath, self->tempDir, strlen(self->tempDir) + 1);
            strcat(filepath, node->value);

            // Download to temp folder
            retCode = downloadFile(&url, filepath);
        }
        else
        {
            temp = strrchr(node->value, '/');

            filepath = (string)malloc((strlen(self->tempDir) + strlen(temp+1) + 1) * sizeof(char));
            strncpy(filepath, self->tempDir, strlen(self->tempDir) + 1);
            strcat(filepath, temp+1);
            
            // Download to temp folder
            retCode = downloadFile(&(node->value), filepath);
        }

        
    }
    else
    {
        retCode = -1;
        fprintf(stderr, "Missing temp directory\n");
    }

    
	
    // Add to output
    if(retCode == 0)
	{
		string command = (string)malloc(sizeof(char) * (strlen(out) + strlen(filepath) + 9));
		sprintf(command, "cat %s >> %s", filepath, out); 
		system(command);
	}

    return retCode;
}

int processXStreamInf(HLS* self, Node* node)
{
    int retCode = 0;
    int urlLength = 0;
    string url = NULL;
    
    // Check the node value is filename or whole url
    if (strlen(self->baseurl->baseurl) + strlen(node->value) != strlen(self->baseurl->url))
    {
        urlLength = strlen(self->baseurl->baseurl) + strlen(node->value) + 1;
        url = (string)malloc(urlLength * sizeof(char));
        memcpy(url, self->baseurl->baseurl, strlen(self->baseurl->baseurl) + 1);

        
        strcat(url, node->value);
    }

    #ifdef DEBUG
    printf("Stream: %s\n", url);
    #endif /* DEBUG */

    // Add to playlist
    if(retCode == 0)
	{
        Node* tempNode = node->Copy(node);
        // IF value is just filename, set it to whole url
        if(url != NULL)
            tempNode->value = url;
		self->variantStreams->Add(self->variantStreams, tempNode);
	}

    return retCode;
}

int processXIFrameStreamInf(HLS* self, Node* node)
{
    int retCode = 0;
    int urlLength = 0;
    string url = NULL;
    
    // Check the node value is filename or whole url
    if (strlen(self->baseurl->baseurl) + strlen(node->value) != strlen(self->baseurl->url))
    {
        urlLength = strlen(self->baseurl->baseurl) + strlen(node->value) + 1;
        url = (string)malloc(urlLength * sizeof(char));
        memcpy(url, self->baseurl->baseurl, strlen(self->baseurl->baseurl) + 1);

        
        strcat(url, node->value);
    }

    #ifdef DEBUG
    printf("I Frame Stream: %s\n", url);
    #endif /* DEBUG */

    // Add to playlist
    if(retCode == 0)
	{
        Node* tempNode = node->Copy(node);

        // IF value is just filename, set it to whole url
        if(url != NULL)
            tempNode->value = url;
		self->iFrameStreams->Add(self->iFrameStreams, tempNode);
	}

    return retCode;
}

int processXMedia(HLS* self, Node* node)
{
    int retCode = 0;
    int urlLength = 0;
    string attribute = NULL;
    string url = NULL;
    string temp = NULL;
    string type = NULL;

    // Copy Attribute
    attribute = (string)malloc((strlen(node->attribute) + 1) * sizeof(char));
    memcpy(attribute, node->attribute, strlen(node->attribute) + 1);

    // Get TYPE
    type = getAttrib(attribute, "TYPE=", ",");

    if(strstr(type, "AUDIO") != NULL)
	{
        // Get URI
        temp = getAttrib(attribute, "URI=\"", "\"");

		urlLength = strlen(self->baseurl->baseurl) + strlen(temp) + 1;
		url = (string)malloc(urlLength * sizeof(char));
		memcpy(url, self->baseurl->baseurl, strlen(self->baseurl->baseurl) + 1);
		strcat(url, temp);

		#ifdef DEBUG
		printf("Media: %s\n", url);
		#endif /* DEBUG */

		// Add to playlist
		if(retCode == 0)
		{
			node->value = url;
			Node* tempNode = node->Copy(node);
			self->media->Add(self->media, tempNode);
		}
	}
	else if(strstr(type, "SUBTITLES") != NULL)
	{
        // Get URI
        temp = getAttrib(attribute, "URI=\"", "\"");

		urlLength = strlen(self->baseurl->baseurl) + strlen(temp) + 1;
		url = (string)malloc(urlLength * sizeof(char));
		memcpy(url, self->baseurl->baseurl, strlen(self->baseurl->baseurl) + 1);
		strcat(url, temp);

		#ifdef DEBUG
		printf("Media: %s\n", url);
		#endif /* DEBUG */

		// Add to playlist
		if(retCode == 0)
		{
			node->value = url;
			Node* tempNode = node->Copy(node);
			self->media->Add(self->media, tempNode);
		}
	}
	else if(strstr(type, "CLOSED-CAPTIONS") != NULL)
	{
        // Get URI
        temp = getAttrib(attribute, "INSTREAM-ID=\"", "\"");

		#ifdef DEBUG
		printf("Media: %s\n", url);
		#endif /* DEBUG */

		// Set node value to instream-id
		if(retCode == 0)
		{
			node->value = temp;
		}
	}
	else
	{
		retCode = -1; // Not Defined Media
		fprintf(stderr, "Media is not defined");
	}

    return retCode;
}

string getAttrib(string attribs, string attribtag, string endToken)
{
    string temp = NULL;
	string rest = NULL;
    int tagLen = 0;
    
    temp = (string)malloc((strlen(attribs) + 1) * sizeof(char));
    memcpy(temp, attribs, strlen(attribs) + 1);
    tagLen = strlen(attribtag);
    temp = strstr(temp, attribtag);
    temp += tagLen;
    strtok_r(temp, endToken, &rest);
    return temp;
}
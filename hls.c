#include "hls.h"

int Process(HLS*);
int processXBitrate(HLS*, Node*);

HLS* CreateHLS()
{
    HLS* hls = (HLS*) malloc(sizeof(hls));
    hls->DeleteHLS = &DeleteHLS;
    hls->Process = &Process;
    
    hls->version = -1;
    hls->segmentsDependent = 1;

    hls->variantStreams = CreateList();
    hls->iFrameStreams = CreateList();
    hls->segments = CreateList();

	hls->tempFolderCreated = 0;
    hls->tempDir = "./m3u8_temp/";
    return hls;
}

void DeleteHLS(HLS* self)
{
    // Remove temp folder
	if(self->tempFolderCreated)
	{
		string delCommand = (string)malloc(strlen(self->tempDir) + 6);
		sprintf(delCommand, "rm -r %s", self->tempDir); 
		system(delCommand);
	}
    self->baseurl->DeleteURLData(self->baseurl);
    self->segments = CreateList();
    //self->list->DeleteList(self->list);
    free(self);
}

int Process(HLS* self)
{
    int retCode = 0;
    int folderRet = 0;
    struct stat buf = {0};

    // Check and create download temp folder
    if (stat(self->tempDir, &buf) == -1) 
    {
        folderRet = mkdir(self->tempDir, 0700); 
		self->tempFolderCreated = 1;


        // I don't like this type indented style however
        // it has to one exit point
        if(folderRet == 0)
        {
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
                    processXBitrate(self, node);

                if (strstr(EXT_X_ENDLIST, node->tag) != NULL)
                    mergeFiles(self);


                // Get next node
                node = node->next;
            }
        }
        else
        {
            retCode = -2; // mkdir error
            fprintf(stderr, "mkdir error");
        }
    }
    else
    {
        retCode = -1; // Temp folder exists
        fprintf(stderr, "Temp folder exists");
    }

    return retCode;
}

int processXBitrate(HLS* self, Node* node)
{
    int retCode = 0;
    //Node* tempNode = (Node*)malloc(sizeof(Node));
    int urlLength = strlen(self->baseurl->baseurl) + strlen(node->value) + 1;
    string url = (string)malloc(urlLength);
    memcpy(url, self->baseurl->baseurl, strlen(self->baseurl->baseurl) + 1);

    strcat(url, node->value);
    #ifdef DEBUG
    printf("Download: %s\n", url);
    #endif /* DEBUG */
	
	string filepath = (string)malloc(strlen(self->tempDir) + strlen(node->value) + 1);
    strncpy(filepath, self->tempDir, strlen(node->value) + 1);
    strcat(filepath, node->value);

    // Download to temp folder
    retCode = downloadFile(&url, filepath);
	
    // Add to output
    if(retCode == 0)
	{
		string output = "output";
		string command = (string)malloc(sizeof(char) * (strlen(output) + strlen(filepath) + 9));
		sprintf(command, "cat %s >> %s", filepath, output); 
		system(command);
	}

    return retCode;
}
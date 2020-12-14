#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "curl.h"
#include "parser.h"
#include "url.h"
#include "hls.h"

int main(int argc, char *argv[])
{
    int retCode;
    string dataStr;
    URLData* url;
    HLS* hls;

    url = InitURLData("https://devstreaming-cdn.apple.com/videos/streaming/examples/img_bipbop_adv_example_ts/v5/prog_index.m3u8");
    hls = CreateHLS();
    
    hls->baseurl = url;
    hls->list = CreateList();

    #ifdef DEBUG
    printf("URLScheme: %s\n", hls->baseurl->scheme);
    printf("URLNetLoc: %s\n", hls->baseurl->netloc);
    printf("URLPath: %s\n", hls->baseurl->path);
    printf("URL: %s\n", hls->baseurl->url);
    #endif /* DEBUG */

    retCode = get_data(&hls->baseurl->url, &dataStr);

    retCode = Parse(dataStr, hls);
    retCode = hls->Process(hls);
	
	Node* node = hls->variantStreams->head;
	for(int i = 0; i < hls->variantStreams->length; i++)
	{
		printf("%s\n", node->value);
		node = node->next;
	}
	
	Node* tempNode = hls->iFrameStreams->head;
	for(int i = 0; i < hls->iFrameStreams->length; i++)
	{
		printf("%s\n", tempNode->value);
		tempNode = tempNode->next;
	}

    printf("\nREMOVE EVERYTHING!!!\n");
    //clear_data();
    hls->DeleteHLS(hls);
    return retCode;
}

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

    hls = CreateHLS();
    url = InitURLData("https://devstreaming-cdn.apple.com/videos/streaming/examples/img_bipbop_adv_example_ts/master.m3u8");
    hls->baseurl = url;
    hls->list = CreateList();

    #ifdef DEBUG
    printf("URLScheme: %s\n", hls->baseurl->scheme);
    printf("URLNetLoc: %s\n", hls->baseurl->netloc);
    printf("URLPath: %s\n", hls->baseurl->path);
    printf("URL: %s\n", hls->baseurl->url);
    #endif /* DEBUG */

    retCode = get_data(&hls->baseurl->url, &dataStr);

    Parse(dataStr, hls);

    Node* node = hls->list->head;
    for(int i = 0; i < hls->list->length; i++)
    {
         printf("INPUT: %s --- %s --- %s\n", node->tag, node->attribute, node->value);
         node = node->next;
    }

    printf("\nREMOVE EVERYTHING!!!\n");
    //clear_data();
    hls->DeleteHLS(hls);
    return retCode;
}

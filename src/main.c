#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "curl.h"
#include "parser.h"
#include "url.h"
#include "hls.h"

int runHLS(string, HLS*, string);

int main(int argc, char *argv[])
{
    int retCode = 0;
    string rawURL = NULL;
    string output = NULL;
    HLS* hls = NULL;

    #ifdef DEBUG
        rawURL = "https://devstreaming-cdn.apple.com/videos/streaming/examples/img_bipbop_adv_example_ts/master.m3u8";
        output = "output.ts";

    #else
        // Basic opt parser
        if(argc == 3)
        {
                rawURL = argv[1];
                output = argv[2];
                
            retCode = 0;
        }
        else
        {
            retCode = -1;
            fprintf(stderr, "%d is invalid\nHelp:\nCommand M3U8_URL OUTPUT_FILE\n\n", argc);
        }
    #endif /* DEBUG */
        

    if(retCode == 0)
    {
        retCode = runHLS(rawURL, hls, output);

        printf("\nREMOVE EVERYTHING!!!\n");
        //clear_data();
        hls->DeleteHLS(hls);

    }
    return retCode;
}

int runHLS(string rawURL, HLS* hls, string out)
{
    int retCode = 0;
    URLData* url;
    string dataStr;
    HLS* variantHLS = NULL;
    HLS* iFrameHLS = NULL;
    HLS* mediaHLS = NULL;

    // Create url and HLS objects
    url = InitURLData(rawURL);
    hls = CreateHLS();
    
    // Bind HLS and URL
    hls->baseurl = url;
    // Create a list for each tag in m3u8 file
    hls->list = CreateList();

    #ifdef DEBUG
    printf("URLScheme: %s\n", hls->baseurl->scheme);
    printf("URLNetLoc: %s\n", hls->baseurl->netloc);
    printf("URLPath: %s\n", hls->baseurl->path);
    printf("URL: %s\n", hls->baseurl->url);
    #endif /* DEBUG */

    // Get m3u8 file from URL
    retCode = get_data(&hls->baseurl->url, &dataStr);

    // Parse the m3u8 data
    retCode = Parse(dataStr, hls);
    // Parse and download segments
    retCode = hls->Process(hls, out);

    Node* variantNode = hls->variantStreams->head;
    for(int i = 0; i < hls->variantStreams->length; i++)
    {
        runHLS(variantNode->value, variantHLS, out);
        variantNode = variantNode->next;
    }
    
    Node* iFrameNode = hls->iFrameStreams->head;
    for(int i = 0; i < hls->iFrameStreams->length; i++)
    {
        runHLS(iFrameNode->value, iFrameHLS, out);
        iFrameNode = iFrameNode->next;
    }

    Node* mediaNode = hls->media->head;
    for(int i = 0; i < hls->media->length; i++)
    {
        runHLS(mediaNode->value, mediaHLS, out);
        mediaNode = mediaNode->next;
    }

    return retCode;
}

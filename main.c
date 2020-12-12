#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "curl.h"
#include "parser.h"
#include "url.h"

int main(int argc, char *argv[])
{
    int retCode;
    string dataStr;
    URLData url;
    HLS hls;

    //hls.baseurl.url = "123";
    url = InitURLData("https://devstreaming-cdn.apple.com/videos/streaming/examples/img_bipbop_adv_example_ts/master.m3u8");
    hls.baseurl = url;

    #ifdef DEBUG
    printf("URLScheme: %s\n", hls.baseurl.scheme);
    printf("URLNetLoc: %s\n", hls.baseurl.netloc);
    printf("URLPath: %s\n", hls.baseurl.path);
    printf("URL: %s\n", *hls.baseurl.url);
    #endif /* DEBUG */

    retCode = get_data(url, &dataStr);

    Parse(dataStr, hls);

    clear_data();
    hls.baseurl.ClearStruct();
    return retCode;
}

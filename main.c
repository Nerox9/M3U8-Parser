#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "curl.h"
#include "parser.h"

int main(int argc, char *argv[])
{
    int retCode;
    string dataStr;
    struct HLS hls;

    retCode = get_data("https://devstreaming-cdn.apple.com/videos/streaming/examples/img_bipbop_adv_example_ts/master.m3u8", &dataStr);

    Parse(dataStr, hls);

    clear_data();
    return retCode;
}

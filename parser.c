#include "parser.h"

void readlines(string);
int parseLine(string);

int Parse(string data, HLS hls)
{
    int retCode = 0;
    string format = "#EXTM3U";
    string line, temp;

    // Get the first line and check format in it
    line = strtok_r(data, "\n", &temp);
    line = strstr(line, format);

    if(line == NULL)
        retCode = -1;
    
    /* If it is not a M3U8 file, abort the process */
    if(retCode == 0)
    {
        #ifdef DEBUG
        printf("Format = %s\n", format);
        #endif /* DEBUG */

        do
    {
        // Get next line
        line = strtok_r(NULL, "\n", &temp);
        parseLine(line);
    }
    while(line != NULL);
    }
    
    return retCode;
}

/* Parse the line */
int parseLine(string data)
{
    int retCode = 0;
    string tag, value;

    tag = strtok_r(data, ":", &value);
    printf("tag = %s\n", tag);
    printf("value = %s\n", value);

    return retCode;
}
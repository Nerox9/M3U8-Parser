#include "parser.h"

void readlines(string);
Node* parseLine(string);

int Parse(string data, HLS* hls)
{
    int retCode = 0;
    string format = "#EXTM3U";
    string line, temp;
    Node* node;

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

        // Get first line
        line = strtok_r(NULL, "#", &temp);
        do
        {
            node = parseLine(line);
            hls->list->Add(hls->list, node);
            // Get next tag, attributes and value
            line = strtok_r(NULL, "#", &temp);
        }
        while(line != NULL);
    }
    
    return retCode;
}

/* Parse the line to node */
Node* parseLine(string data)
{
    Node* node;
    string tag, attribute, value, rest;

    // Parse the each node
    tag = strtok_r(data, ":", &rest);
    tag = strtok(tag, "\n");
    attribute = strtok_r(NULL, "\n", &rest);
    rest = strtok(rest, "\n");
    value = rest;

    node = CreateNode(tag, attribute, value);
    #ifdef DEBUG
    printf("tag = %s\n", tag);
    printf("attribute = %s\n", attribute);
    printf("value = %s\n", value);
    #endif /* DEBUG */

    return node;
}
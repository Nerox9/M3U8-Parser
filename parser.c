#include "parser.h"

void readlines(string);
int parseFileHeader(string);
int checkFormat(string*, string);
int checkVersion(string*, string*);

int Parse(string data, struct HLS hls)
{
    int retCode = 0;

    /* 
    // It can be copied to temp data and process on it
    // however it continued with original buffer because of optimization
    string temp;
    strncpy(temp, data, sizeof(data));
    */
    
    readlines(data);
    retCode = parseFileHeader(data);
    
    return retCode;
}

/* Parse the header */
int parseFileHeader(string data)
{
    int retCode = 0;
    string line = data;
    string format = "#EXTM3U";
    string version = 0;

    retCode = checkFormat(&line, format);
    /* If it is not a M3U8 file, abort the process */
    if(retCode == 0)
    {
        #ifdef DEBUG
        printf("Format = %s\n", format);
        #endif /* DEBUG */

        /* CHECK VERSION */
        //retCode = checkVersion(&line, &version);
        #ifdef DEBUG/*
        if(retCode == 0)
        {
            printf("Version = %s\n", version);
        }*/
        #endif /* DEBUG */

    }

    return retCode;
}

/* Check the header format */
int checkFormat(string* line, string format)
{
    int retCode = 0; 
    string p, temp;
    
    // Get the first line and check header in it
    p = strtok_r(*line, "\n", &temp);
    p = strstr(p, format);

    if(p == NULL)
        retCode = -1;
    else
    {
        // Set pointer to remaining part
        *line = temp;
    }

    return retCode;
}

/* Check the header version */
int checkVersion(string* line, string* version)
{
    int retCode = 0; 
    int notVerTag = 0;
    string p, temp, ver;
    string verToken = "#EXT-X-VERSION";

    // Get the first line and check version in it
    p = strtok_r(*line, "\n", &temp);
    p = strtok_r(p, ":", &ver);
    notVerTag = strncmp(p, verToken, strlen(verToken) + 1);

    // Check the Tag is version
    if(notVerTag == 0)
    {
        *line = temp;
        *version = ver;
        retCode = 0;
    }
    else
        retCode = -2;

    return retCode;
}

void readlines(string str)
{
  string p, temp;


  p = strtok_r(str, "\n", &temp);
  while(p != NULL)
  {
      

      // Get next line
      p = strtok_r(NULL, "\n", &temp);
      printf("current line = %s\n", p);
  }
}
#include "url.h"

int ParseURL(URLData*);
void ClearStruct();

URLData InitURLData(const string url)
{
    URLData urlData;

    urlData.ClearStruct = &ClearStruct;
    urlData.url = &url;
    ParseURL(&urlData);
    urlData.GetURL = &GetURL;
    urlData.SetURL = &SetURL;

    return urlData;
}

int ParseURL(URLData* self)
{
    int retCode = 0;
    string temp;
    string p;
    string rest;
    unsigned int pathLen;
    string endToken;
    char* pEndToken;
    
    temp = malloc((strlen(*(self->url)) + 1) * sizeof(char));
    memcpy(temp, *(self->url), strlen(*(self->url)) + 1);

    p = strtok_r(temp, "://", &rest);
    if(p == NULL)
        retCode = -1;
    else
        self->scheme = p;

    p = strtok_r(NULL, "/", &rest);
    if(p == NULL)
        retCode = -1;
    else
        self->netloc = p;

    endToken = strrchr(rest, '/');
    pathLen = strlen(rest) - strlen(endToken); // this could be efficient however it doesnt work and i passed
    if(endToken != NULL)
    {
        self->path = malloc((pathLen + 1) * sizeof(char));
        memcpy(self->path, rest, pathLen + 1);
        pEndToken = self->path + pathLen + 1;
        *pEndToken = NULL;
    }

    return retCode;
}

void ClearStruct(URLData* self)
{
    printf("Clear URL");
    free(*self->url);
    free(self->scheme);
    free(self->netloc);
    free(self->path);
}

string GetURL()
{
    return "GetTest";
}

void SetURL(URLData *self, const string url)
{
    self->url = &url;
}
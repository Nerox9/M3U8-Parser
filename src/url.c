#include "url.h"

int ParseURL(URLData*);
string GetBaseURL(string);
void DeleteURLData(URLData*);

URLData* InitURLData(const string url)
{
    URLData* urlData = (URLData*) malloc(sizeof(URLData));

    urlData->DeleteURLData = &DeleteURLData;
    urlData->url = url;
    urlData->baseurl = GetBaseURL(url);
    ParseURL(urlData);
    urlData->GetURL = &GetURL;
    urlData->SetURL = &SetURL;

    return urlData;
}

int ParseURL(URLData* self)
{
    int retCode = 0;
    string temp;
    string p;
    string rest;
    
    temp = (string)malloc((strlen(self->baseurl) + 1) * sizeof(char));
    memcpy(temp, self->baseurl, strlen(self->baseurl) + 1);

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

    self->path = rest;

    return retCode;
}

string GetBaseURL(string url)
{
    unsigned int pathLen;
    string endToken;
    string baseURL;

    baseURL = (string)malloc((strlen(url) + 1) * sizeof(char));
    memcpy(baseURL, url, strlen(url) + 1);
    endToken = strrchr(baseURL, '/');
    pathLen = strlen(baseURL) - strlen(endToken);
    free(baseURL);
    if(endToken != NULL)
    {
        baseURL = (string)malloc(pathLen + 1);
        memset(baseURL, '\0', pathLen + 1);
        memcpy(baseURL, url, pathLen + 1);
    }
    return baseURL;
}

string GetURL(URLData *self)
{
    return self->url;
}

void SetURL(URLData *self, const string url)
{
    self->url = url;
}

void DeleteURLData(URLData* self)
{
    printf("Clear URL");
    free(self->netloc);
    free(self->path);
    free(self->scheme);
    free(self->url);
    
    free(self);
}
#ifndef __alyo_url_h__
#define __alyo_url_h__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char* string;

typedef struct URLData {
    string url;
    string baseurl;
    string scheme;
    string netloc;
    string path;
    void (*DeleteURLData)(struct URLData*);
    string (*GetURL)(struct URLData*);
    void (*SetURL)(struct URLData*, string);
} URLData;

URLData* InitURLData(const string);
string GetURL(URLData *);
void SetURL(URLData *, string);

#endif
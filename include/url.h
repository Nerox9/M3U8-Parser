#ifndef __alyo_url_h__
#define __alyo_url_h__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char* string;

typedef struct URLData {
    string* url;
    string scheme;
    string netloc;
    string path;
    void (*ClearStruct)();
    string (*GetURL)();
    void (*SetURL)(struct URLData*, string);
} URLData;

URLData InitURLData(const string);
string GetURL();
void SetURL(URLData *, string);

#endif
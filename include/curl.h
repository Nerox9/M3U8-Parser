#ifndef __curl_h__
#define __curl_h__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <curl/easy.h>

#include "url.h"

typedef char* string;

struct ResponseData;
size_t write_data(void *, size_t, size_t, struct ResponseData *);
int get_data(string*, string*);
int downloadFile(string*, string);
void clear_data();

#endif /*__curl_h__*/
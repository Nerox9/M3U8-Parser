#ifndef __alyo_curl_h__
#define __alyo_curl_h__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <curl/easy.h>

typedef char* string;

struct url_data;
size_t write_data(void *, size_t, size_t, struct url_data *);
int get_data(string url, string* dataOut);

#endif /*__alyo_curl_h__*/
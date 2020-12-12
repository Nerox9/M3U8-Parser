#include "curl.h"

struct url_data {
    size_t size;
    string data;
};

size_t write_data(void *ptr, size_t size, size_t nmemb, struct url_data *data) 
{
    
}


int get_data(string url, string* dataOut)
{
    CURL *curl;
    CURLcode res;
    int retCode = 0;
    
    
    return retCode;
}
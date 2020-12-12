#include "curl.h"

struct ResponseData {
    size_t size;
    string data;
};

struct ResponseData* responseData_ptr;

/* Write callback */
size_t write_data(void *ptr, size_t size, size_t nmemb, struct ResponseData *data) 
{
    size_t index = data->size;
    size_t n = (size * nmemb);
    char* tmp;

    data->size += (size * nmemb);

#ifdef DEBUG
    fprintf(stderr, "data at %p size=%ld nmemb=%ld\n", ptr, size, nmemb);
#endif

    tmp = realloc(data->data, data->size + 1);

    if(tmp) {
        data->data = tmp;
    } else {
        if(data->data) {
            free(data->data);
        }
        fprintf(stderr, "Failed to allocate memory.\n");
        return 0;
    }

    memcpy((data->data + index), ptr, n);
    data->data[data->size] = '\0';

    return size * nmemb;
}


int get_data(URLData url, string* dataOut)
{
    CURL *curl;
    CURLcode res;
    int retCode = 0;
    
    struct ResponseData data;
    responseData_ptr = &data;

    data.size = 0;
    data.data = malloc(4096); /* initial buffer */

    if(NULL == data.data) {
        fprintf(stderr, "Failed to allocate memory.\n");
        retCode = -3; // Memory Allocation Error
    }

    data.data[0] = '\0';


    curl = curl_easy_init();
    if (curl)
    {
        // Set curl options
        curl_easy_setopt(curl, CURLOPT_URL, *(url.url));
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &data);   // get output as string

        res = curl_easy_perform(curl);

        // Check curl perform
        if(res != CURLE_OK) 
        {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
            retCode = -2; // CURL Download Error
        }
        
        *dataOut = data.data;
        curl_easy_cleanup(curl);
    }

    else
    {
        fprintf(stderr, "curl_easy_init failed.\n");
            retCode = -1; // CURL İnitialize Error
    }
    
    return retCode;
}

void clear_data()
{
    printf("Clear CURL data\n");
    free(responseData_ptr->data);
    printf("Clear CURL data\n");
}
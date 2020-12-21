#ifndef __hls_h__
#define __hls_h__

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "list.h"
#include "url.h"
#include "protocol.h"
#include "curl.h"


typedef char* string;
typedef struct HLS
{
    URLData* baseurl;
    List* list;
    void (*DeleteHLS)(struct HLS*);
    int (*Process)(struct HLS*, string);

    int version;
    char segmentsDependent;

    List* variantStreams;
    List* iFrameStreams;
	List* media;

    string tempDir;
} HLS;

HLS* CreateHLS();
void DeleteHLS(HLS*);

#endif /* __hls_h__ */
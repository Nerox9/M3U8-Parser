#ifndef __alyo_hls_h__
#define __alyo_hls_h__

#include "list.h"
#include "url.h"

typedef char* string;
typedef struct HLS
{
    URLData* baseurl;
    List* list;
    void (*DeleteHLS)(struct HLS*);
    int (*Process)(struct HLS*);
} HLS;

HLS* CreateHLS();
void DeleteHLS(HLS*);

#endif /* __alyo_hls_h__ */
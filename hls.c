#include "hls.h"

HLS* CreateHLS()
{
    HLS* hls = (HLS*) malloc(sizeof(hls));
    hls->DeleteHLS = &DeleteHLS;
    return hls;
}

void DeleteHLS(HLS* self)
{
    self->baseurl->DeleteURLData(self->baseurl);
    //self->list->DeleteList(self->list);
    free(self);
}

int Process(struct HLS* self)
{
    int retCode = 0;

    

    return retCode;
}
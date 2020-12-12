#ifndef __alyo_parser__
#define __alyo_parser__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char* string;
struct HLS
{
    char* baseurl; 
};

int Parse(string, struct HLS);

#endif /* __alyo_parser__ */
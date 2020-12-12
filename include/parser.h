#ifndef __alyo_parser__
#define __alyo_parser__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "url.h"

typedef char* string;
typedef struct HLS
{
    URLData baseurl; 
} HLS;

int Parse(string, HLS);

#endif /* __alyo_parser__ */
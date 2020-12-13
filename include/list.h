#ifndef __alyo_list_h__
#define __alyo_list_h__

#include <stdio.h>
#include <stdlib.h>

typedef char* string;

typedef struct Node 
{ 
    string tag;
    string attribute;
    string value;
    struct Node* next; 
} Node; 

typedef struct List 
{
    Node* head;
    Node* last;
    unsigned int length;
    int (*Add)(struct List*, Node*); 
    void (*DeleteList)(struct List*);
} List;

Node* CreateNode(string, string, string);
List* CreateList();
int Add(List*, Node*);
void DeleteList(List*);

#endif /* __alyo_list_h__ */
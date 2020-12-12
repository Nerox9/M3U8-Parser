#include "list.h"

Node* CreateNode(string tag, string attribute, string value)
{
    Node* node = (Node*)malloc(sizeof(Node));

    node->tag = tag;
    node->attribute = attribute;
    node->value = value;

    return node;
}

List* CreateList()
{
    List* list = malloc(sizeof(List));
    list->Add = &Add;

    return list;
}

int Add(List* self, Node* node)
{
    int retCode = 0;

    
    if(self->last == NULL)
        self->head = node;
    else
        self->last->next = node;

    self->last = node;
    self->last->next = NULL;

    // TODO: check

    return retCode;
}

void DeleteNode(Node* self)
{
    // TODO
}

void DeleteList()
{
    // TODO
}
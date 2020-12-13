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
    List* list = (List*) malloc(sizeof(List));
    list->length = 0;
    list->Add = &Add;

    return list;
}

int Add(List* self, Node* node)
{
    int retCode = 0;

    if (self == NULL)
        retCode = -1;
    else if(node == NULL)
        retCode = -2;
    else
    {
        if(self->last == NULL)
            self->head = node;
        else
            self->last->next = node;

        self->last = node;
        self->last->next = NULL;
        self->length++;
    }

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
#include "list.h"

Node* Copy(Node* self);

Node* CreateNode(string tag, string attribute, string value)
{
    Node* node = (Node*)malloc(sizeof(Node));

    node->tag = tag;
    node->attribute = attribute;
    node->value = value;
	
	node->Copy = &Copy;

    return node;
}

List* CreateList()
{
    List* list = (List*) malloc(sizeof(List));
    list->length = 0;
    list->Add = &Add;
    list->DeleteList = &DeleteList;

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

Node* Copy(Node* self)
{
    Node* newNode = (Node*)malloc(sizeof(Node));

    string tag = (string)malloc(strlen(self->tag) + 1);
    string attribute = (string)malloc(strlen(self->attribute) + 1);
    string value = (string)malloc(strlen(self->value) + 1);

    memcpy(tag, self->tag, strlen(self->tag) + 1);
    memcpy(attribute, self->attribute, strlen(self->attribute) + 1);
    memcpy(value, self->value, strlen(self->value) + 1);

    newNode->tag = tag;
    newNode->attribute = attribute;
    newNode->value = value;
	
	return newNode;
}

void DeleteNode(Node* self)
{
    free(self);
}

void DeleteList(List* self)
{
    Node* head = self->head;
    Node* temp;

    while(head != NULL)
    {
        temp = head;
        head = head->next;
        free(temp);
    }
}
#ifndef _FORWARD_forward_list_H_
#define _FORWARD_forward_list_H_

#include "node.h"

typedef struct
{
    Node *head;
    int size;
} ForwardList;

ForwardList *forward_list_construct();

void forward_list_push_front(ForwardList *l, data_type data);

int forward_list_size(ForwardList *l);

void forward_list_destroy(ForwardList *l);

#endif
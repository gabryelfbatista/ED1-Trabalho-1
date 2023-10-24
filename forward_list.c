#include "./headers/forward_list.h"
#include "./headers/node.h"
#include <stdlib.h>
#include <stdio.h>

ForwardList *forward_list_construct() 
{
    return calloc(1, sizeof(ForwardList));
};

void forward_list_push_front(ForwardList *l, data_type data)
{
    l->head = node_construct(data, l->head);
    l->size++;
};

int forward_list_size(ForwardList *l)
{
    return l->size;
};

void forward_list_print(ForwardList *l, void (*print_fn)(data_type))
{
    Node *aux = l->head;
    for (int i=0; i<l->size; i++){
        if (i == l->size-1) {
            print_fn(aux->value);
            aux = aux->next;
            printf("\n");
        } else {
            print_fn(aux->value);
            printf("\n");
            aux = aux->next;
        }
    }
};


data_type forward_list_find(ForwardList *l, void *val, int (*cmp_fn)(void *, data_type))
{
    Node *aux = l->head;

    while (aux != NULL)
    {
        if (cmp_fn(val, aux->value) == 0)
            return aux->value;

        aux = aux->next;
    }
    
    return NULL;
}

data_type forward_list_get(ForwardList *l, int i)
{
    if (i < 0 || i>=l->size) {
        exit(printf("Error: index out of bounds."));
    }

    Node *aux = l->head;
    for (int j=0; j<i; j++){
        aux = aux->next;
    }
    return aux->value;
};

ForwardList *forward_list_reverse(ForwardList *l)
{
    ForwardList *l2 = forward_list_construct();
    
    Node *aux = l->head;
    while(aux != NULL)
    {
        forward_list_push_front(l2, aux->value);
        aux = aux->next;
    }
    l2->size = l->size;
    forward_list_destroy(l);
    return l2;
};

void forward_list_destroy(ForwardList *l) 
{
    Node *aux = l->head;
    Node *new_next;
    while (aux != NULL)
    {
        new_next = aux->next;
        free(aux);
        aux = new_next;
    }
    free(l);
};
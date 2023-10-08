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
    printf("[");
    for (int i=0; i<l->size; i++){
        if (i == l->size-1) {
            print_fn(aux->value);
            aux = aux->next;
        } else {
            print_fn(aux->value);
            printf(", ");
            aux = aux->next;
        }
    }
    printf("]");
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
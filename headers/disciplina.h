#ifndef _DISCPLINA_H_
#define _DISCPLINA_H_
#include "forward_list.h" 

typedef struct Disciplina
{
    char *nome;
    char *codigo;
    ForwardList *matriculas;
} Disciplina;

Disciplina *disciplina_construct(char *nome, char *codigo);

void disciplina_destroy(Disciplina *d);

#endif
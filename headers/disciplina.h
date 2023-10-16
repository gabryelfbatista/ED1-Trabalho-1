#ifndef _DISCPLINA_H_
#define _DISCPLINA_H_
#include "forward_list.h" 

typedef struct Disciplina
{
    char *nome;
    char *codigo;
    char *professor;
    ForwardList *matriculas;
    ForwardList *pre_requisito;
} Disciplina;

Disciplina *disciplina_construct(char *nome, char *codigo, char *professor);

void disciplina_destroy(Disciplina *d);

#endif
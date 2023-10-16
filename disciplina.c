#include <stdlib.h>
#include <string.h>
#include "./headers/disciplina.h"

Disciplina *disciplina_construct(char *nome, char *codigo, char *professor)
{
    Disciplina *d = (Disciplina*)calloc(1, sizeof(Disciplina));
    d->nome = nome;
    d->codigo = codigo;
    d->professor = professor;
    d->pre_requisito = forward_list_construct();
    d->matriculas = forward_list_construct();
    return d;
};

void disciplina_destroy(Disciplina *d)
{
    free(d);
};
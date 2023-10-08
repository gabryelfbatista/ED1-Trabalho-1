#include <stdlib.h>
#include <string.h>
#include "./headers/disciplina.h"

Disciplina *disciplina_construct(char *nome, char *codigo)
{
    Disciplina *d = (Disciplina*)malloc(sizeof(Disciplina));
    d->nome = nome;
    d->codigo = codigo;
    return d;
};

void disciplina_destroy(Disciplina *d)
{
    free(d);
};
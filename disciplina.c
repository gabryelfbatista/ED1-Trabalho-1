#include <stdlib.h>
#include <string.h>
#include "./headers/disciplina.h"

Disciplina *disciplina_construct(char *nome, char *codigo, char *professor)
{
    Disciplina *d = (Disciplina*)calloc(1, sizeof(Disciplina));
    d->nome = nome;
    d->codigo = codigo;
    d->professor = professor;
<<<<<<< HEAD
    d->pre_requisito = forward_list_construct();
    d->matriculas = forward_list_construct();
=======
>>>>>>> 3b9dc3978e8da59ac3bc8c1d72a68a4a9d08caaf
    return d;
};

void disciplina_destroy(Disciplina *d)
{
    free(d);
};
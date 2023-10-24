#include <stdlib.h>
#include <string.h>
#include "./headers/estudante.h"

Estudante *estudante_construct(char *nome, int matricula, char *email)
{
    Estudante *e = (Estudante *)calloc(1, sizeof(Estudante));
    e->nome = nome;
    e->matricula = matricula;
    e->email = email;
    return e;
};

void estudante_destroy(Estudante *e)
{
    free(e->nome);
    free(e->email);
    free(e);
};
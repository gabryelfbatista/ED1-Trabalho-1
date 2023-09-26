#include <stdlib.h>
#include <string.h>
#include "./estudante.h"

Estudante *estudante_construct(char nome, int matricula, char email)
{
    Estudante *e = (Estudante *)malloc(sizeof(Estudante));
    strcpy(e->nome, nome);
    e->matricula = matricula;
    strcopy(e->email, email);
    return e;
};

void estudante_destroy(Estudante *e)
{
    free(e);
};
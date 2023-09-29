#include <stdlib.h>
#include <stdio.h>
#include "./matricula.h"

Matricula *matricula_construct(Estudante *aluno, float notaFinal, float presenca, int aprovado)
{
    Matricula *m = (Matricula *)malloc(sizeof(Matricula));
    m->aluno = aluno;
    m->notaFinal = notaFinal;
    m->presenca = presenca;
    m->aprovado = aprovado;
    return m;
};

void matricula_destroy(Matricula *m)
{
    free(m);
};

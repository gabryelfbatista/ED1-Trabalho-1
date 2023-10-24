#include <stdlib.h>
#include <stdio.h>
#include "./headers/matricula.h"

Matricula *matricula_construct(Estudante *aluno, float notaFinal, float presenca, int aprovado)
{
    Matricula *m = (Matricula *)calloc(1 , sizeof(Matricula));
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

#ifndef _MATRICULA_H_
#define _MATRICULA_H_

#include "estudante.h"

typedef struct
{
    Estudante *aluno;
    float notaFinal;
    float presenca;
    int aprovado;
    
} Matricula;

Matricula *matricula_construct(Estudante *aluno, float notaFinal, float presenca, int aprovado);

void matricula_destroy(Matricula *m);

#endif
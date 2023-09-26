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

#endif
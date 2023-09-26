#ifndef _DISCPLINA_H_
#define _DISCPLINA_H_
#include "matricula.h" 

typedef struct Disciplina
{
    char nome[50];
    char codigo[10];
    Matricula *matricula;
    struct Disciplina *requisitos;
} Disciplina;

#endif
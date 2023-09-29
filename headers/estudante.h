#ifndef _ESTUDANTE_H_
#define _ESTUDANTE_H_

typedef struct
{
    char *nome;
    int matricula;
    char *email;
} Estudante;

Estudante *estudante_construct(char *nome, int matricula, char *email);

void estudante_destroy(Estudante *e);

#endif
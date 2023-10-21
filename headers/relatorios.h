#ifndef _RELATORIOS_H_
#define _RELATORIOS_H_

#include "forward_list.h"

void alunos_matriculados(char *codigo, ForwardList *d, ForwardList *e);

void pre_requisitos_diretos(char *codigo, ForwardList *d);

void pre_requisitos_completos(char *codigo, ForwardList *d);

void disciplinas_matriculadas(int matricula, ForwardList *d);

#endif
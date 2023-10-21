#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "./headers/estudante.h"
#include "./headers/matricula.h"
#include "./headers/disciplina.h"
#include "./headers/forward_list.h"
#include "./headers/relatorios.h"

int compara_string_codigo_disciplina(void *string1, data_type estrutura)
{
    char *s = string1;
    Disciplina *d = estrutura;
    return strcmp(s, d->codigo);
};

int compara_string_nome(void *string1, data_type estrutura)
{
    char *s = string1;
    Estudante *e = estrutura;
    return strcmp(s, e->nome);
};

void print_string_nome_aluno(data_type data)
{   
    Estudante *e = data;
    printf("%s", e->nome);
};

void print_string_codigo(data_type data)
{   
    Disciplina *d = data;
    printf("%s", d->codigo);
};

void alunos_matriculados(char *codigo, ForwardList *d, ForwardList *e)
{   
    ForwardList *a_matriculados = forward_list_construct(); //crio uma lista de alunos matriculados temporaria
    Disciplina *d_aux = forward_list_find(d, codigo, compara_string_codigo_disciplina); //encontro a disciplina desejada

    Node *aux = d_aux->matriculas->head;
    Matricula *m_aux;
    Estudante *e_aux;

    //itera sobre a lista de matriculas
    while (aux != NULL)
    {
        m_aux = aux->value;
        // procura o estudante apontado pela matricula 
        e_aux = forward_list_find(a_matriculados, m_aux->aluno->nome, compara_string_nome);

        //se nao existir na lista temporaria de alunos matriculados, adiciona o aluno
        if (e_aux == NULL)
        {
            forward_list_push_front(a_matriculados, m_aux->aluno);
        }
        aux = aux->next;    
    }
    printf("Alunos matriculados na disciplina %s:\n", codigo);
    forward_list_print(a_matriculados, print_string_nome_aluno);
    forward_list_destroy(a_matriculados);
};

void pre_requisitos_diretos(char *codigo, ForwardList *d)
{
    // ForwardList *pre_requisitos = forward_list_construct();
    Disciplina *d_aux = forward_list_find(d, codigo, compara_string_codigo_disciplina);

    printf("Lista de pre requisitos da disciplina %s:\n", codigo);
    forward_list_print(d_aux->pre_requisito, print_string_codigo);
};
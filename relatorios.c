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

typedef struct
{
    char *nome;
    int n_reprovacoes;
    char *cod;
} Professor;

int compara_int_reprovacoes(data_type professor1, data_type professor2)
{
    Professor *p1 = professor1;
    Professor *p2 = professor2;
    int n1 = p1->n_reprovacoes;
    int n2 = p2->n_reprovacoes;

    if (n1 > n2)
    {
        return 0;
    }

    return 1;
};

void print_reprovacoes(data_type data)
{
    Professor *p = data;
    printf("Professor %s na disciplina de %s: %d\n", p->nome, p->cod, p->n_reprovacoes);
}

void alunos_matriculados(char *codigo, ForwardList *d, ForwardList *e)
{   
    ForwardList *a_matriculados = forward_list_construct(); //crio uma lista de alunos matriculados temporaria
    Disciplina *d_aux = forward_list_find(d, codigo, compara_string_codigo_disciplina); //encontro a disciplina desejada

    Node *aux = d_aux->matriculas->head;
    Matricula *m_aux;
    Estudante *e_aux;

    if (aux == NULL){
        printf("Nao ha matriculas nessa disciplina\n");
    }
    else {
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
    }


    forward_list_destroy(a_matriculados);
};

void pre_requisitos_diretos(char *codigo, ForwardList *d)
{
    Disciplina *d_aux = forward_list_find(d, codigo, compara_string_codigo_disciplina);

    if (d_aux->pre_requisito->head == NULL)
    {
        printf("Essa disciplina não tem pre requisitos\n");
    }
    else 
    {
        printf("Lista de pre requisitos da disciplina %s:\n", codigo);
        forward_list_print(d_aux->pre_requisito, print_string_codigo);
    }
};

void pre_requisitos_completos(char *codigo, ForwardList *d)
{
    // encontro a disciplina passada
    Disciplina *d_aux = forward_list_find(d, codigo, compara_string_codigo_disciplina);

    //verifico se ela possui pre requisitos
    if (d_aux->pre_requisito->head == NULL)
    {
        printf("Essa disciplina não tem pre requisitos\n");
    }
    else 
    {
        //inverto a lista de pre requisitos pra sair na ordem de entrada
        d_aux->pre_requisito = forward_list_reverse(d_aux->pre_requisito);

        Node *aux = d_aux->pre_requisito->head;

        Disciplina *d_aux2 = aux->value;
        
        //itero sobre a lista printando pre requisitos
        printf("Pre requisitos completos da disciplina %s:\n", codigo);
        while(aux != NULL)
        {
            d_aux2 = aux->value;
            printf("%s\n", d_aux2->codigo);

            if (d_aux2->pre_requisito != NULL)
            {
                d_aux2->pre_requisito = forward_list_reverse(d_aux2->pre_requisito);
                forward_list_print(d_aux2->pre_requisito, print_string_codigo);
            }
            aux = aux->next; 
        }
    }
    
};

void disciplinas_matriculadas(int matricula, ForwardList *d)
{
    ForwardList *lista_matriculas = forward_list_construct();
    Node *it_disciplina = d->head;
    Disciplina *d_aux;
    Disciplina *d_encontrada;
    Node *it_matriculas;
    Matricula *m_aux;
    int encontrou_matricula = 0;

    //itera sobre o vetor de disciplinas
    while (it_disciplina != NULL)
    {
        d_aux = it_disciplina->value;
        it_matriculas = d_aux->matriculas->head;

        while(it_matriculas != NULL)
        {
            m_aux = it_matriculas->value;

            if (matricula == m_aux->aluno->matricula)
            {
                d_encontrada = forward_list_find(lista_matriculas, d_aux->codigo, compara_string_codigo_disciplina);
                if (d_encontrada == NULL)
                {
                    forward_list_push_front(lista_matriculas, d_aux);
                }
                encontrou_matricula = 1;
            }

            it_matriculas = it_matriculas->next;
        }

        it_disciplina = it_disciplina->next;
    }
    
    if (encontrou_matricula == 0)
    { 
        printf("Esse aluno nao esta matriculado em disciplinas\n");
    }
    else 
    {
        printf("O aluno esta matriculado nas disciplinas:\n");
        forward_list_print(lista_matriculas, print_string_codigo);
    }

    forward_list_destroy(lista_matriculas);
    node_destroy(it_disciplina);
    node_destroy(it_matriculas);
};

void reprovacoes_por_professor(ForwardList *d)
{
    ForwardList *reprovacoes = forward_list_construct();
    Node *it = d->head;
    Disciplina *d_aux = it->value;
    Node *m_it = d_aux->matriculas->head;
    Matricula *m_aux;
    while (it != NULL)
    {
        Professor *p = malloc(sizeof(Professor)); 
        p->n_reprovacoes = 0;
        d_aux = it->value;
        p->nome = d_aux->professor;
        p->cod = d_aux->codigo;
        m_it = d_aux->matriculas->head;
        while (m_it != NULL)
        {
            m_aux = m_it->value;
            if (m_aux->aprovado == 0)
            {
                p->n_reprovacoes++;
            }
            m_it = m_it->next;
        }
        forward_list_push_front(reprovacoes, p);
        it = it->next;
    }

    // forward_list_sort(reprovacoes, compara_int_reprovacoes);
    // forward_list_print(reprovacoes, print_reprovacoes);

    //OBS: nao consegui implementar a tempo :( 

    it = reprovacoes->head;
    Professor *p;
    while (it != NULL)
    {
        p = it->value;
        free(p);
        it = it->next;
    }

    forward_list_destroy(reprovacoes);
}
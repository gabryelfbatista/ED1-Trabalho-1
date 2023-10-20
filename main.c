#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "./headers/estudante.h"
#include "./headers/matricula.h"
#include "./headers/disciplina.h"
#include "./headers/forward_list.h"

int compara_string(void *string1, data_type estrutura)
{
    char *s = string1;
    Disciplina *d = estrutura;
    int i = strcmp(s, d->codigo);
    disciplina_destroy(d);
    return i;   
};

int compara_int(void *numero, data_type estrutura)
{   
    int *numero_i = numero;
    Estudante *e = estrutura;
    if ((*numero_i) == e->matricula)
    {
        estudante_destroy(e);
        return 1;
    }
    estudante_destroy(e); 
    return 0;
};

void print_string_nome_estudante(data_type data)
{
    Estudante *e = data;
    printf("%s", e->nome);
    estudante_destroy(e);
};

void print_string_codigo_disciplina(data_type data)
{
    Disciplina *d = data;
    printf("%s", d->codigo);
    disciplina_destroy(d);
};

ForwardList *cria_lista_alunos(FILE *arq)
{
    ForwardList *alunos = forward_list_construct();

    /* VARIAVEIS PARA AUXILIAR NA LEITURA DOS ARQUIVOS*/
    int qtd_alunos;
    char linha[100];
    char *resultado = " ";
    char *pedaco_texto;
    char separador[2] = ";";

    char *nome;
    int matricula;
    char *email;

    fscanf(arq, "%d\n", &qtd_alunos);

    for (int i = 0; i < qtd_alunos; i++)
    {
        resultado = fgets(linha, 100, arq);

        // printf("Resultado: %s\n", resultado);

        pedaco_texto = strtok(resultado, separador);
        nome = malloc(sizeof(pedaco_texto));
        strcpy(nome, pedaco_texto);

        // printf("Nome: %s\n", nome);

        pedaco_texto = strtok(NULL, separador);
        matricula = atoi(pedaco_texto);

        pedaco_texto = strtok(NULL, "\n");
        email = malloc(sizeof(pedaco_texto));               
        strcpy(email, pedaco_texto);

        Estudante *e = estudante_construct(nome, matricula, email);
        forward_list_push_front(alunos, e);
    }

    return alunos;
}

ForwardList *cria_lista_disciplinas(FILE *arq)
{
    ForwardList *disciplinas = forward_list_construct();

    /* VARIAVEIS PARA AUXILIAR NA LEITURA DOS ARQUIVOS*/
    int qtd_disciplinas;
    char linha[200];
    char *resultado;
    char *pedaco_texto;
    char separador[2] = ";";

    char *nome;
    char *codigo;
    char *nome_professor;

    fscanf(arq, "%d\n", &qtd_disciplinas);

    for (int i = 0; i < qtd_disciplinas; i++)
    {
        resultado = fgets(linha, 200, arq);

        pedaco_texto = strtok(resultado, separador);
        nome = malloc(sizeof(pedaco_texto));
        strcpy(nome, pedaco_texto);

        pedaco_texto = strtok(NULL, separador);
        codigo = malloc(sizeof(pedaco_texto));
        strcpy(codigo, pedaco_texto);

        pedaco_texto = strtok(NULL, "\n");
        nome_professor = malloc(sizeof(pedaco_texto));
        strcpy(nome_professor, pedaco_texto);

        Disciplina *d = disciplina_construct(nome, codigo, nome_professor);
        forward_list_push_front(disciplinas, d);
    }

    return disciplinas;
}

void cria_lista_requisitos(FILE *arq, ForwardList *disciplinas)
{

    /* VARIAVEIS PARA AUXILIAR NA LEITURA DOS ARQUIVOS*/
    int qtd_requisitos;
    char linha[200];
    char *resultado;
    char *pedaco_texto;
    char separador[2] = ";";

    char *codigo;
    char *codigo_requisito;

    fscanf(arq, "%d\n", &qtd_requisitos);

    for (int i = 0; i < qtd_requisitos; i++)
    {
        resultado = fgets(linha, 200, arq);

        pedaco_texto = strtok(resultado, separador);
        codigo = malloc(sizeof(pedaco_texto));
        strcpy(codigo, pedaco_texto);

        Node *aux = node_construct(NULL, NULL);
        aux->value = forward_list_find(disciplinas, codigo, compara_string);

        Disciplina *d_aux = aux->value;

        pedaco_texto = strtok(NULL, "\n");
        codigo_requisito = malloc(sizeof(pedaco_texto));
        strcpy(codigo_requisito, pedaco_texto);

        Node *aux2 = node_construct(NULL, NULL); 
        aux2->value = forward_list_find(disciplinas, codigo_requisito, compara_string);

        forward_list_push_front(d_aux->pre_requisito, aux2->value);

        disciplina_destroy(d_aux);
        node_destroy(aux);
        node_destroy(aux2);
    }
    // return requisitos;
}

ForwardList *cria_lista_matriculas(FILE *arq, ForwardList *disciplinas, ForwardList *aluno)
{
    ForwardList *matriculas = forward_list_construct();

    /* VARIAVEIS PARA AUXILIAR NA LEITURA DOS ARQUIVOS*/
    int qtd_matriculas;
    char linha[200];
    char *resultado;
    char *pedaco_texto;
    char separador[2] = ";";

    char *codigo;
    int matricula_aluno;
    float nota;
    float presenca;
    int aprovado;

    fscanf(arq, "%d\n", &qtd_matriculas);

    for (int i = 0; i < qtd_matriculas; i++)
    {
        resultado = fgets(linha, 200, arq);

        pedaco_texto = strtok(resultado, separador);
        codigo = malloc(sizeof(pedaco_texto));
        strcpy(codigo, pedaco_texto);

        Node *aux = node_construct(NULL, NULL);
        aux->value = forward_list_find(disciplinas, codigo, compara_string);

        Disciplina *d_aux = aux->value;

        pedaco_texto = strtok(NULL, separador);
        matricula_aluno = atoi(pedaco_texto);
        
        Node *aux2 = forward_list_find(aluno, &matricula_aluno, compara_int);

        pedaco_texto = strtok(NULL, separador); 
        nota = atof(pedaco_texto);
        
        pedaco_texto = strtok(NULL, separador);
        presenca = atof(pedaco_texto);
        
        pedaco_texto = strtok(NULL, "\n");
        aprovado = atoi(pedaco_texto);
        
        Matricula *m = matricula_construct(aux2->value, nota, presenca, aprovado);

        forward_list_push_front(matriculas, m);

        disciplina_destroy(d_aux);
        node_destroy(aux);
        node_destroy(aux2);

        // Disciplina *d = estudante_construct(nome, codigo, nome_professor);
        // forward_list_push_front(requisitos, d);
    }
    return matriculas;
}

int main(){
    char entrada[20] = "entrada.txt";
    FILE *arq = fopen(entrada, "r");

    ForwardList *alunos = cria_lista_alunos(arq);
    printf("Lista de alunos cadastrados: ");
    forward_list_print(alunos, print_string_nome_estudante);

    ForwardList *disciplinas = cria_lista_disciplinas(arq);
    printf("Codigo de disciplinas cadastradas: ");
    forward_list_print(disciplinas, print_string_codigo_disciplina);
    // cria_lista_requisitos(arq, disciplinas);

    // scanf("%s", entrada);
    
    free(alunos);
    free(disciplinas);

    fclose(arq);
    return 0;
}

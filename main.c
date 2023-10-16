#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "./headers/estudante.h"
#include "./headers/matricula.h"
#include "./headers/disciplina.h"
#include "./headers/forward_list.h"

ForwardList *cria_lista_alunos(FILE *arq)
{
    ForwardList *alunos = forward_list_construct();

    /* VARIAVEIS PARA AUXILIAR NA LEITURA DOS ARQUIVOS*/
    int qtd_alunos;
    char linha[200];
    char *resultado;
    int contador_linhas;
    char *pedaco_texto;
    char separador[2] = ";";

    char *nome;
    int matricula;
    char *email;

    fscanf(arq, "%d", &qtd_alunos);

    for (int i = 0; i < qtd_alunos; i++)
    {
        resultado = fgets(linha, 200, arq);

        pedaco_texto = strtok(resultado, separador);
        nome = malloc(sizeof(pedaco_texto));
        strcpy(nome, pedaco_texto);

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
    int qtd_requisitos;
    char linha[200];
    char *resultado;
    int contador_linhas;
    char *pedaco_texto;
    char separador[2] = ";";

    char *nome;
    char *codigo;
    char *nome_professor;

    fscanf(arq, "%d", &qtd_disciplinas);

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

        Disciplina *d = estudante_construct(nome, codigo, nome_professor);
        forward_list_push_front(disciplinas, d);
    }

    fscanf(arq, "%d", &qtd_requisitos);

    Node *aux = disciplinas->head;

    for (int i = 0; i < qtd_requisitos; i++)
    {
        pedaco_texto = strtok(resultado, separador);
        nome = malloc(sizeof(pedaco_texto));
        strcopy(codigo, pedaco_texto);
    }

    return disciplinas;
}

ForwardList *cria_lista_requisitos(FILE *arq)
{
    ForwardList *requisitos = forward_list_construct();

    /* VARIAVEIS PARA AUXILIAR NA LEITURA DOS ARQUIVOS*/
    int qtd_requisitos;
    char linha[200];
    char *resultado;
    int contador_linhas;
    char *pedaco_texto;
    char separador[2] = ";";

    char *nome;
    char *codigo;
    char *nome_professor;

    fscanf(arq, "%d", &qtd_requisitos);

    for (int i = 0; i < qtd_requisitos; i++)
    {
        resultado = fgets(linha, 200, arq);

        pedaco_texto = strtok(resultado, separador);
        codigo = malloc(sizeof(pedaco_texto));
        strcpy(codigo, pedaco_texto);

        pedaco_texto = strtok(resultado, separador);
        nome_professor = malloc(sizeof(pedaco_texto));
        strcpy(nome_professor, pedaco_texto);

        Disciplina *d = estudante_construct(nome, codigo, nome_professor);
        forward_list_push_front(requisitos, d);
    }

    return requisitos;
}

int main(){
    char entrada[20] = "entrada.txt";
    FILE *arq = fopen("entrada.txt", "r");

    ForwardList *alunos = cria_lista_alunos(arq);
    ForwardList *disciplinas = cria_lista_disciplinas(arq);

    /* VARIAVEIS PARA AUXILIAR NA LEITURA DOS ARQUIVOS*/
    

    /* VARIAVEIS PARA AUXILIAR NA CONSTRUÇAO DAS ESTRUTURAS*/

    // scanf("%s", entrada);

    FILE *arq = fopen("entrada.txt", "r");
    
    free(alunos);
    // free(matriculas);
    free(disciplinas);

    fclose(arq);
    return 0;
}

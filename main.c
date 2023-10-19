#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "./headers/estudante.h"
#include "./headers/matricula.h"
#include "./headers/disciplina.h"
#include "./headers/forward_list.h"

int compara_string(void *string1, data_type disciplina)
{
    char *s = string1;
    Disciplina *d = disciplina;
    return strcmp(s, d->codigo);   
};

int compara_int(void *numero, void *estrutura)
{   
    Estudante *e = estrutura;
    if (numero == e->matricula)
    {
        return 1;
    } 
    return 0;
};

ForwardList *cria_lista_alunos(FILE *arq)
{
    ForwardList *alunos = forward_list_construct();

    /* VARIAVEIS PARA AUXILIAR NA LEITURA DOS ARQUIVOS*/
    int qtd_alunos;
    char linha[200];
    char *resultado;
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
    char linha[200];
    char *resultado;
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

    fscanf(arq, "%d", &qtd_requisitos);

    for (int i = 0; i < qtd_requisitos; i++)
    {
        resultado = fgets(linha, 200, arq);

        pedaco_texto = strtok(resultado, separador);
        codigo = malloc(sizeof(pedaco_texto));
        strcpy(codigo, pedaco_texto);

        Node *aux = forward_list_find(disciplinas, codigo, compara_string);

        Disciplina *d_aux = aux->value;

        pedaco_texto = strtok(NULL, "\n");
        codigo_requisito = malloc(sizeof(pedaco_texto));
        strcpy(codigo_requisito, pedaco_texto);

        Node *aux2 = forward_list_find(disciplinas, codigo_requisito, compara_string);

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

    fscanf(arq, "%d", &qtd_matriculas);

    for (int i = 0; i < qtd_matriculas; i++)
    {
        resultado = fgets(linha, 200, arq);

        pedaco_texto = strtok(resultado, separador);
        codigo = malloc(sizeof(pedaco_texto));
        strcpy(codigo, pedaco_texto);

        Node *aux = forward_list_find(disciplinas, codigo, compara_string);

        Disciplina *d_aux = aux->value;

        pedaco_texto = strtok(NULL, separador);
        matricula_aluno = atoi(pedaco_texto);
        
        Node *aux2 = forward_list_find(aluno, matricula_aluno, compara_int);

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
    ForwardList *disciplinas = cria_lista_disciplinas(arq);

    /* VARIAVEIS PARA AUXILIAR NA LEITURA DOS ARQUIVOS*/
    

    /* VARIAVEIS PARA AUXILIAR NA CONSTRUÇAO DAS ESTRUTURAS*/

    // scanf("%s", entrada);
    
    free(alunos);
    // free(matriculas);
    free(disciplinas);

    fclose(arq);
    return 0;
}

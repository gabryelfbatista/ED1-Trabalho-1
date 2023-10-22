#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "./headers/estudante.h"
#include "./headers/matricula.h"
#include "./headers/disciplina.h"
#include "./headers/forward_list.h"
#include "./headers/relatorios.h"

int compara_string_codigo(void *string1, data_type estrutura)
{
    char *s = string1;
    Disciplina *d = estrutura;
    return strcmp(s, d->codigo);
};

int compara_int(void *numero, data_type estrutura)
{   
    int *numero_i = numero;
    Estudante *e = estrutura;
    if ((*numero_i) == e->matricula)
    {
        return 0;
    }
    return 1;
};

void print_string_nome_estudante(data_type data)
{
    Estudante *e = data;
    printf("%s", e->nome);
};

void print_string_codigo_disciplina(data_type data)
{
    Disciplina *d = data;
    printf("%s", d->codigo);
};

void checa_existencia_disciplina(ForwardList *d, char *codigo)
{
    if (forward_list_find(d, codigo, compara_string_codigo) == NULL)
        {
            exit(printf("Essa disciplina nao foi encontrada \n"));
        };
}

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

void cria_lista_requisitos(FILE *arq, ForwardList *d)
{
    /* VARIAVEIS PARA AUXILIAR NA LEITURA DOS ARQUIVOS*/
    int qtd_requisitos;
    char linha[200];
    char *resultado;
    char *pedaco_texto;
    char separador[2] = ";";

    char *codigo;
    char *codigo_requisito;
    Disciplina *d_aux;
    Disciplina *d_aux2;

    fscanf(arq, "%d\n", &qtd_requisitos);
    // printf("qtd_requisitos: %d\n", qtd_requisitos);

    for (int i = 0; i < qtd_requisitos; i++)
    {
        resultado = fgets(linha, 200, arq);
        // printf("Resultado: %s\n", resultado);

        pedaco_texto = strtok(resultado, separador);
        codigo = malloc(sizeof(pedaco_texto));
        strcpy(codigo, pedaco_texto);
        // printf("Codigo: %s\n", codigo);

        // d_aux = d->head->value;

        d_aux = forward_list_find(d, codigo, compara_string_codigo);
        // printf("Codigo disciplina encontrada: %s\n", d_aux->codigo);

        pedaco_texto = strtok(NULL, "\n");
        codigo_requisito = malloc(sizeof(pedaco_texto));
        strcpy(codigo_requisito, pedaco_texto);

        d_aux2 = forward_list_find(d, codigo_requisito, compara_string_codigo);
        // printf("Codigo pre requisito encontrado: %s\n", d_aux2->codigo);

        forward_list_push_front(d_aux->pre_requisito, d_aux2);
    }
}

void cria_lista_matriculas(FILE *arq, ForwardList *disciplinas, ForwardList *alunos)
{
    // ForwardList *matriculas = forward_list_construct();

    /* VARIAVEIS PARA AUXILIAR NA LEITURA DOS ARQUIVOS*/
    int qtd_matriculas;
    char linha[200];
    char *resultado;
    char *pedaco_texto;
    char *pedaco_codigo;
    char *pedaco_matricula;
    char separador[2] = ";";

    char *codigo;
    int matricula_aluno;
    char *matricula_comparador; //pra comparar uma matricula com outra
    float nota;
    float presenca;
    int aprovado;

    Disciplina *d_aux;
    Estudante *e_aux;

    fscanf(arq, "%d\n", &qtd_matriculas);

    /*
        OBS: como na logica que eu usei a primeira matricula nunca tem um igual,
        no primeiro ciclo de iteração ele sempre soma +1 entao tem q iterar
        até chegar a ao numero de quantidade de matriculas
    */
    for (int i = 0; i <= qtd_matriculas; i++) 
    {
        // printf("O valor de i eh: %d\n", i);
        resultado = fgets(linha, 200, arq);

        pedaco_codigo = strtok(resultado, separador);
        
        pedaco_matricula = strtok(NULL, separador);       
        
        // se o codigo da disciplina e a matricula do aluno for a mesma, então n conta a linha
        if (strcmp(pedaco_codigo, codigo) == 0 && strcmp(pedaco_matricula, matricula_comparador) == 0)
        {
            codigo = malloc(sizeof(pedaco_codigo));
            strcpy(codigo, pedaco_codigo);

            d_aux = forward_list_find(disciplinas, codigo, compara_string_codigo);

            matricula_aluno = atoi(pedaco_matricula);

            e_aux = forward_list_find(alunos, &matricula_aluno, compara_int);

            matricula_comparador = malloc(sizeof(pedaco_matricula));
            strcpy(matricula_comparador, pedaco_matricula);

            pedaco_texto = strtok(NULL, separador); 
            nota = atof(pedaco_texto);
            
            pedaco_texto = strtok(NULL, separador);
            presenca = atof(pedaco_texto);
            
            pedaco_texto = strtok(NULL, "\n");
            aprovado = atoi(pedaco_texto);

            Matricula *m = matricula_construct(e_aux, nota, presenca, aprovado);

            // forward_list_push_front(matriculas, m);

            forward_list_push_front(d_aux->matriculas, m);
            
            i--;
        }
        else 
        {
            codigo = malloc(sizeof(pedaco_codigo));
            strcpy(codigo, pedaco_codigo);

            d_aux = forward_list_find(disciplinas, codigo, compara_string_codigo);

            matricula_aluno = atoi(pedaco_matricula);

            e_aux = forward_list_find(alunos, &matricula_aluno, compara_int);

            // printf("Nome do aluno encontrado: %s\n", e_aux->nome);

            matricula_comparador = malloc(sizeof(pedaco_matricula));
            strcpy(matricula_comparador, pedaco_matricula);

            pedaco_texto = strtok(NULL, separador); 
            nota = atof(pedaco_texto);
            
            pedaco_texto = strtok(NULL, separador);
            presenca = atof(pedaco_texto);
            
            pedaco_texto = strtok(NULL, "\n");
            aprovado = atoi(pedaco_texto);

            Matricula *m = matricula_construct(e_aux, nota, presenca, aprovado);

            // forward_list_push_front(matriculas, m);

            forward_list_push_front(d_aux->matriculas, m);
        }
    }
}

int main(){
    /* VARIAVEIS OBTIDAS PRA LER O ARQUIVO DE ENTRADA */
    char entrada[20];
    int num_relatorio;

    /* VARIAVEIS USADAS PARA GERAR RELATORIOS */
    char codigo_disciplina[20];
    int num_matricula;

    scanf("%s", entrada);
    scanf("%d", &num_relatorio);
    FILE *arq = fopen(entrada, "r");

    ForwardList *alunos = cria_lista_alunos(arq);
    ForwardList *disciplinas = cria_lista_disciplinas(arq);
    cria_lista_requisitos(arq, disciplinas);
    cria_lista_matriculas(arq, disciplinas, alunos);

    if (num_relatorio == 1)
    {
        printf("Digite o codigo da disciplina:\n");
        scanf("%s", codigo_disciplina);

        checa_existencia_disciplina(disciplinas, codigo_disciplina);

        alunos_matriculados(codigo_disciplina, disciplinas, alunos);
    }
    else if (num_relatorio == 2)
    {
        printf("Digite o codigo da disciplina:\n");
        scanf("%s", codigo_disciplina);

        checa_existencia_disciplina(disciplinas, codigo_disciplina);

        pre_requisitos_diretos(codigo_disciplina, disciplinas);
    }
    else if (num_relatorio == 3)
    {
        printf("Digite o codigo da disciplina:\n");
        scanf("%s", codigo_disciplina);

        checa_existencia_disciplina(disciplinas, codigo_disciplina);

        pre_requisitos_completos(codigo_disciplina, disciplinas);
    }
    else if (num_relatorio == 4)
    {
        scanf("%d", &num_matricula);
        disciplinas_matriculadas(num_matricula, disciplinas);
    }

    forward_list_destroy(disciplinas);
    forward_list_destroy(alunos);

    fclose(arq);
    return 0;
}

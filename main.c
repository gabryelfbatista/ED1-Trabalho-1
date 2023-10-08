#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "./headers/estudante.h"
#include "./headers/matricula.h"
#include "./headers/forward_list.h"

int main(){
    
    ForwardList *alunos = forward_list_construct();
    ForwardList *matriculas = forward_list_construct();

    /* VARIAVEIS PARA AUXILIAR NA LEITURA DOS ARQUIVOS*/
    char separador[2] = ";";
    char entrada[20] = "entrada.txt";
    int qtd_alunos;
    int qtd_matriculas;
    int qtd_requisitos;
    int qtd_disciplinas;
    char linha[100];
    char *resultado;
    int count_lines = 0;
    char *pedaco_texto;

    /* VARIAVEIS PARA AUXILIAR NA CONSTRUÇAO DAS ESTRUTURAS*/
    char *nome;
    int matricula;
    char *email;
    char *codigo;



    // scanf("%s", entrada);

    FILE *arq = fopen("entrada.txt", "r");

    while (!feof(arq))
    {
        resultado = fgets(linha, 100, arq);
        printf("resultado: %s", resultado);

        if (resultado == NULL){
            break;
        }

        if (count_lines == 0){
            qtd_alunos = atoi(resultado);
            // printf("%d\n", qtd_alunos);
        } 
        else if (count_lines >= 1 && count_lines < qtd_alunos+1)
        {   
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
        else if (count_lines == qtd_alunos+1)
        {
            qtd_disciplinas = atoi(resultado);
            // printf("Numero de disciplinas: %d\n", qtd_disciplinas);
        }
        else if (count_lines > qtd_alunos+1 && count_lines < qtd_alunos + qtd_disciplinas)
        {
            pedaco_texto = strtok(resultado, separador);
            nome = malloc(sizeof(pedaco_texto));
            strcpy(nome, pedaco_texto);

            pedaco_texto = strtok(resultado, separador);
            codigo = malloc(sizeof(pedaco_texto));
            strcpy(codigo, pedaco_texto);
        }
        count_lines++;
        printf("a Count lines eh: %d\n", count_lines);
    }


    // if (argc == 2)
    // {
    //     FILE *arq = fopen(argv[1], "r");

    //     if (arq == NULL)
    //     {
    //         exit(printf("Problemas na CRIACAO do arquivo\n"));    
    //     }

    //     resultado = fgets(linha, 100, arq);
    //     printf("%s", resultado);
    // }
    // else 
    // {
    //     printf("Quantidade de argumentos insuficientes\n");
    // }
    

    fclose(arq);
    return 0;
}

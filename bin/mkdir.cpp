
/*
mkdir Cria um novo diretório.
*/
#include <stdio.h> // entrada e saída em c
#include <stdlib.h> // funções como alocação de memória, conversão de números etc
#include <sys/stat.h>  // Para mkdir

int main(int argc, char *argv[]){

    if(argc != 2){
        printf("Não é possível criar diretório com os dados fornecidos:\n");
        // função de c para imprimir dados formatados em um arquivo de saída - fprintf
        fprintf(stderr, "Comando esperado: %s <diretório>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

     mkdir(argv[1], 0777); // tenta criar o diretório com as permissões especificadas (0777 neste caso, que permite leitura, escrita e execução para o usuário atual).

    return 0;
}
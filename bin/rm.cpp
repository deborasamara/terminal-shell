/*
CHAMADA RM - remove arquivo
*/

#include <stdio.h> // entrada e saída 
#include <stdlib.h> // funções como alocação de memória, conversão de números etc

// verificar quantidade de argumentos

int main(int argc, char *argv[]){
    // testa os argumentos
    if(argc != 2){
        printf("Não é possível executar com os dados fornecidos:\n");
        // função de c para imprimir dados formatados em um arquivo de saída - fprintf
        fprintf(stderr, "Comando esperado: %s <arquivo>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Remove o arquivo do segundo argumento
    if (remove(argv[1]) == 0) { // se o retorno da função remove() for igual a 0, foi bem sucessido
        printf("Arquivo %s removido com sucesso!!!.\n", argv[1]);
        return EXIT_SUCCESS;
    } else {
        perror("Erro ao remover arquivo");
        return EXIT_FAILURE;
    }

    return 0;
}
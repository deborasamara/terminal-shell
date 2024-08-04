
/*
cat Mostra no terminal o conteúdo de um arquivo. Considera arquivos em modo texto, mostrando cada
byte como um valor ASCCII.
*/
#include <stdio.h> // entrada e saída padrão
#include <stdlib.h> // usado para o "exit(exit_failure)"

int main(int argc, char* argv[]){
    // Olha se a quantidade de argumentos é igual a dois
    if (argc != 2) {
        printf("Não é possível executar com os dados fornecidos:\n");
        fprintf(stderr, "Comando esperado: %s <arquivo>\n", argv[0]);
        exit(EXIT_FAILURE); // Retorna erro
    }

    // Abertura do arquivo
    FILE *arquivoler; // variável ponteiro do tipo file
    arquivoler = fopen(argv[1], "r"); // r é read

    // Printa cada byte
    int cadabyte;
    while ((cadabyte = fgetc(arquivoler)) != EOF) {
        printf("%c", cadabyte);
    }

    printf("\n");

    // fecha o arquivo
    fclose(arquivoler);

    return 0; // retorna zero para indicar sucesso
}
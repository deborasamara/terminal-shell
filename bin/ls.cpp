/*
CHAMADA ls - Lista os arquivos localizados em um determinado diretório. 
            Caso não seja especificado o diretório, usa
            o diretório de trabalho atual, que pode ser recuperado pela chamada de 
            sistema getcwd().
*/
#include <dirent.h> // manipulação de diretórios
#include <stdlib.h> // funções como alocação de memória, conversão de números etc
#include <unistd.h> // getcwd()
#include <iostream> // entrada e saída c++

// uso e chamadas de sistema opendir, readdir e closedir.

// código em si

/*
    parâmetros da função main() 

    agrc - inteiro que representa o num de argumentos passados (argument count)
    argv - array de strings  (argument )
*/

int main(int argc, char *argv[]){ // argumentos da função main
    // declaração de uma variável que é uma estrutura de dados usada para representar um diretório, sendo usada para manipulações e abrir
    DIR *dir; // declaração de ponteiro para um objeto do tipo DIR
    // declaração de uma var do tipo struct dirent, que contem informações sobre UM arquivo no diretório, ela lerá todos os nomes dos arquivos do diretório
    struct dirent *entry; // estrutura de dados específica já definida. usada para armazenar infos sobre um arquivo de um diretório(nome, tipo, tamanho, etc)
    // *entry é um ponteiro do tipo struct dirent. aponta para a estrutura de dados.
    // testa os argumentos
    if(argc == 1){ // diretório atual
        char memoria_temp[100]; // cria uma variável do tipo char, temporária para guardar o nome do dir atual 
        argv[1] = getcwd(memoria_temp, sizeof(memoria_temp)); // getcwd() é uma função da biblioteca padrão, usada para obter o diretório de trabalho atual
        // sizeof(memoria_temp) retorna o tamanho de memoria_temp em bytes
        argc++; // atualização do número de argumentos pra 2
    }
    if(argc > 2){ // diretório especificado
        std::cerr << "Não é possível executar com os dados fornecidos" << std::endl;
        std::cerr << "Comando esperado: %s <diretório>\n", argv[0];
        std::cerr << "OU:\n" << "para mostrar os itens da pasta atual)\n" << argv[0] << std::endl;

        exit(EXIT_FAILURE);
    }
    // tentativa de abrir o diretório especificado
    dir = opendir(argv[1]); 
    if( dir  == NULL ){// se não for possível abrir o diretório
        perror("opendir");
        exit(EXIT_FAILURE);
    }
    // leitura dos nomes dos arquivos
    std::cout << "Listagem dos arquivos: " << std::endl;
    while( (entry = readdir(dir)) != NULL){
        std::cout << entry->d_name << std::endl;
    }

    closedir(dir); 

    return 0;
}
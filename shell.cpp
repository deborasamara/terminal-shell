// BIBLIOTECAS
#include <unistd.h> // entrada/saída e manipulação de processos
#include <sys/wait.h> // gerenciamento de processos filho 
#include <iostream> // funcionalidade de entrada e saída std::cout , std::cin
#include <stdlib.h> // para recuperar o caminho do diretório atual
#include <sstream> // manipulação de strings
#include <vector> // vetores
#include <limits.h>
#include <string> // para manipular strings
 
std::vector<std::string> vector_history; // vetor de comandos 
std::string path_atual_string;

void caminho_atual(){
    char path_atual_char[PATH_MAX]; // buffer
    getcwd(path_atual_char, sizeof(path_atual_char));
    path_atual_string = path_atual_char; 
}

// COMANDOS INTERNOS
void process_pwd(){ // mostrar diretorio de trabalho
    char dir_atual[1048];
    getcwd(dir_atual, sizeof(dir_atual));
    std::cout <<"Diretório atual: " << dir_atual << std::endl;
}

void process_cd(std::string directory){ // mudar diretório
    if(directory == ".."){
        // Mudar para o diretório pai
        if (chdir("..") == 0) {
            std::cout << "Diretório acima." << std::endl;
        } else {
            std::cout << "Erro ao mudar para o diretório acima" << std::endl;
        }
    }else{
        if( chdir(directory.c_str()) == 0){
            std::cout << "Diretório Atual : " <<  directory  << std::endl;
                }else{
            std::cout << "ERROR"  << std::endl;
        }
    }
}

void process_history(){ // histórico de comandos digitados pelo usuário
    if(vector_history.empty()){// se o vetor estiver vazio
        std::cout << "Nenhum comando executado ainda.";
    }else{ // se o vetor tiver alguma coisa
        std::cout << "histórico: " << std::endl;
        for (size_t i = 0; i < vector_history.size(); ++i) {
            std::cout<<"# "<< vector_history[i] << std::endl;
        }
    }
    
}

// PROCESSADOR DE COMANDOS
void process_command(std::string command) { // recebe texto de comando
    vector_history.push_back(command); // comando adicionado ao history
    // Se for comando interno...

    // verificador de espaços
    std::string arg1_command;
    std::string arg2;
    std::vector<std::string> partes_linha_comando;
    
    size_t position_space = command.find(' ');

    if (position_space != std::string::npos) {
        // Extrair o comando principal (antes do espaço)
        arg1_command = command.substr(0, position_space);

        // Extrair o argumento (depois do espaço)
        arg2 = command.substr(position_space + 1); // +1 para pular o espaço
        //argumentos.push_back(arg2);
    } else {
        arg2 = ""; 
        arg1_command = command;
    }
   
    if (arg1_command  == "exit"){ // se a string for "exit", finaliza. 
        exit(0); 
    }else if(arg1_command  == "pwd"){
        process_pwd();
    }else if(arg1_command == "cd"){ // por verificação de algo digitadoo + string com o nome do diretorio para mudar
        process_cd(arg2);

    }else if(arg1_command  == "history"){
        process_history();
        
    }else{ // COMANDO EXTERNO
        // Se for comando externo
        //      Se for absoluto verifica se comando existe

        //std::string absolute_path = "/mnt/c/Users/Débora/Desktop/so-shell/terminal-shell/bin/"+ arg1_command; // caminho absoluto para o comando
        std::string absolute_path = path_atual_string + "/bin/" + arg1_command;

        if (access(absolute_path.c_str(), F_OK) == 0) { // Arquivo existe no diretório, verificar se é executável
            if (access(absolute_path.c_str(), X_OK) == 0) { // Arquivo é executável
                pid_t pid = fork(); // cria processo e retorna id do processo filho
                if (pid < 0){ // Erro - retornou -1. (Pid = -1)
                    std::cout << "Erro de execução!" << std::endl;
                    return;
                } else if (pid == 0){ //processo filho. (Pid = 0)
                    std::vector<char*> array_ponteiros_lc; // array de ponteiros a ser preenchido
                    array_ponteiros_lc.push_back(const_cast<char*>(arg1_command.c_str()));

                    if (!arg2.empty()) {
                        array_ponteiros_lc.push_back(const_cast<char*>(arg2.c_str()));
                    }
                    array_ponteiros_lc.push_back(nullptr); 
                    
                    //char * argv[2] = {(char *)command.c_str(), nullptr}; // converte o código do comando em array de strings
                    //execve(absolute_path.c_str(), argv, NULL); // executa o programa no caminho absoluto
                    execve(absolute_path.c_str(),array_ponteiros_lc.data(), nullptr ); // executa o programa no caminho absoluto
                } else { // Processo pai. (Pid > 0)
                    // Deve adicionar processo filho na lista (std::vector)
                    // de processos em execução para gerenciar background. ∗/
                    // Processo pai espera processo filho terminar. ∗/
                    // waitpid(pid, nullptr, 0);
                      waitpid(pid, nullptr, 0);
                }
            } else { // Arquivo não é executável
                std::cout << "permission denied: " << command << std::endl;
            }
        } else { // Arquivo não existe
            std::cout << "Command not found: " << command << std::endl;
        }
    }
}
//      Leitura do que o usuário quer
int main() {
    caminho_atual();
    while (true) { // looping infinito
        std::cout << "$> ";
        std::string command;
        getline(std::cin, command); // leitura do comando
        process_command(command); // processar comando
    }
    return 0;
}

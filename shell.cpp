// BIBLIOTECAS
#include <unistd.h> // entrada/saída e manipulação de processos
#include <sys/wait.h> // gerenciamento de processos filho 
#include <iostream> // funcionalidade de entrada e saída std::cout , std::cin


// CÓDIGO PRÁTICO
void process_command(std::string command) { // recebe texto de comando
    // Se for comando interno...
    if (command == "exit") // se a string for "exit", finaliza. Exit é comando interno
    exit(0);
    // Se for comando externo
    // ∗ necessário verificar se é para ser executado em background
    //  Se for caminho relativo, procurar o comando na lista de diretórios
    //  Se for absoluto verifica se comando existe

    std::string absolute_path = "/bin/" + command; // caminho absoluto para o comando
    if (access(absolute_path.c_str(), F_OK) == 0) { // Arquivo existe no diretório, verificar se é executável
        if (access(absolute_path.c_str(), X_OK) == 0) { // Arquivo é executável
            pid_t pid = fork(); // cria processo e retorna id do processo filho
            if (pid < 0){ // Erro - retornou -1. (Pid = -1)
                std::cout << "Erro de execução!" << std::endl;
                return;
            } else if (pid == 0){ //processo filho. (Pid = 0)
                char * argv[2] = {(char *)command.c_str(), nullptr}; // converte o código do comando em array de strings
                execve(absolute_path.c_str(), argv, NULL); // executa o programa no caminho absoluto
            } else { // Processo pai. (Pid > 0)
                // Deve adicionar processo filho na lista (std::vector)
                // de processos em execução para gerenciar background. ∗/
                // Processo pai espera processo filho terminar. ∗/
                // waitpid(pid, nullptr, 0);
            }
        } else { // Arquivo não é executável
            std::cout << "permission denied: " << command << std::endl;
        }
    } else { // Arquivo não existe
        std::cout << "Command not found: " << command << std::endl;
    }
}
//      Leitura do que o usuário quer
int main() {
    while (true) {
        std::cout << "$> ";
        std::string command;
        getline(std::cin, command);
        process_command(command);
    }
    return 0;
}
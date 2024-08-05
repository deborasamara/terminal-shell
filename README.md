# Terminal-shell 💻
Atividade de Sistemas Operacionais, 3° período: desenvolvimento de uma shell simples, em linguagem C/C++. 
### Organização do código
pasta "/bin/" contendo códigos externos a shell

Arquivo "shell.cpp", que executa o comando principal do terminal da shell, além de conter alguns comandos internos.
### A Shell
O funcionamento da shell é determinado por um looping infinito que espera por um comando do usuário para procurar, executar, e esperar o próximo comando, até que ele decida sair e encerrar o programa.
```
//  Leitura do que o usuário quer
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
```
Código rodando:
```
./shell
$> ls
Listagem dos arquivos: 
.
..
.git
alala
bin
dir-shell
README.md
shell
shell.cpp
teste
testecat.txt
$> history
histórico:
# ls
# history
$>
```

### Comandos internos
Comandos organizados dentro do próprio arquivo da shell.

**exit:** termina a execução do código

**history** - mostra todos os comandos enviados durante a execução da shell

**cd** - muda o diretório atual

**pwd** - retorna o valor do caminho do diretório atual

### Comandos externos

**ls** - lista todos os arquivos do diretório

**mkdir** - cria novo diretório com o nome fornecido

**rmdir** - apaga diretório solicitado

**rm** - apaga arquivo especifíco

**cat** - mostra no terminal o conteúdo de um arquivo

**uptime** - mostra a quanto tempo o computador está ligado

**date** - mostra a hora atual


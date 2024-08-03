/*
CHAMADA UPTIME - Mostra a quanto tempo o computador está ligado
*/

#include <sys/sysinfo.h> // relacionado a declarações de funções de infos do sistema
#include <iostream> // entrada e saída c++

int main () // código 
{
    struct sysinfo info; // variavel do tipo struct sysinfo, onde sysinfo tem várias informações do sistema, como tempo de atividade, quantidade de memória livre, etc
    sysinfo(&info); //a função sysinfo preenche info com informações do sistema atual. é colocado o endereço de memória de info no argumento
    std::cout << "Uptime: (tempo em segundos desde que foi iniciado ao tempo que foi chamada a função) = " << info.uptime << " segundos " << std::endl;
    return 0; // funcionou
}
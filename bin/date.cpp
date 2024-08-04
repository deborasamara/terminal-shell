
/*
CHAMADA DATE - Mostra a hora atual
*/
// Cabeçalho para entrada e saída
#include <iostream> // entrada e saída 
// Cabeçalho para manipulação de tempo
#include <time.h>
// formatação de saída
#include <iomanip> 


// implementação do programa que mostra a hora
void horaAtual(){ // função sem retorno

    time_t tempo_em_segundos;// variável time_t é usada para armazenar uma quantidade de tempo em segundos desde um certo tempo. Estamos apenas declarando uma variável do tipo.

    struct tm *data_hora;// declaração de um ponteiro para um struct "tm" que é usada para armazenar informações de data e hora. *data_hora armazena o endereço de tm

    time(&tempo_em_segundos);// A função time vai preencher a variável tempo_em_segundos com o tempo atual em segundos desde o tempo x.

    data_hora = localtime(&tempo_em_segundos);//

    // Printa a hora atual em hh:mm:ss
    printf("\nHora Atual: %02d", data_hora->tm_hour);// horas
    printf(":%02d",data_hora->tm_min);// minutos
    printf(":%02d",data_hora->tm_sec);// segundos
    printf("\n");
}

// chama o programa
int main(){
    horaAtual(); // chama a função
    return 0;
}
#include "../include/utils.h"

#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdio.h>
#include <ctype.h>

/* ============================================================
   Sessão com utilidades para o resto do código principal
   ============================================================ */

int gerarId(int min, int max)
{
    return min + rand() % (max - min + 1);
}

char *formatarTempo(unsigned long long int ms)
{
    unsigned long long horas, minutos, segundos, milisecundos;

    horas = ms / 3600000ULL;
    minutos = (ms % 3600000ULL) / 60000ULL;
    segundos = (ms % 60000ULL) / 1000ULL;
    milisecundos = ms % 1000ULL;

    char *saida = malloc(13);
    snprintf(saida, 13, "%02llu:%02llu:%02llu:%03llu",
             horas, minutos, segundos, milisecundos);

    return saida;
}

char *formatarData(time_t data)
{
    struct tm *tm_info = localtime(&data);
    char *saida = malloc(11);
    strftime(saida, 11, "%d/%m/%Y", tm_info);
    return saida;
}

int validarData(char *str)
{
    if (!str || strlen(str) != 10)
        return 0;

    if (str[2] != '/' || str[5] != '/')
        return 0;

    for (int i = 0; i < 10; i++)
    {
        if (i == 2 || i == 5)
            continue;
        if (!isdigit((unsigned char)str[i]))
            return 0;
    }

    return 1;
}

int validarTempo(int horas, int minutos, int segundos, int milissegundos)
{
    if (horas < 0)
        return 0;
    if (minutos < 0 || minutos > 59)
        return 0;
    if (segundos < 0 || segundos > 59)
        return 0;
    if (milissegundos < 0 || milissegundos > 999)
        return 0;
    return 1;
}

int validarRecordeTempo(char* str)
{
    if (!str || strlen(str) != 11) 
        return 0;

    if (str[2] != ':' || str[5] != ':' || str[8] != ':')
        return 0;

    for (int i = 0; i < 11; i++) {
        if (i == 2 || i == 5 || i == 8) continue;
        if (!isdigit((unsigned char)str[i]))
            return 0;
    }

    int hora = atoi(str);
    int minuto = atoi(str + 3);
    int segundo = atoi(str + 6);
    int ms = atoi(str + 9);

    if (hora < 0 || hora > 23) return 0;
    if (minuto < 0 || minuto > 59) return 0;
    if (segundo < 0 || segundo > 59) return 0;
    if (ms < 0 || ms > 99) return 0;

    return 1;
}

unsigned long long int converterTempo(char* tempo)
{
    int horas, minutos, segundos, milisecundos;

    sscanf(tempo, "%2d:%2d:%2d:%2d", &horas, &minutos, &segundos, &milisecundos);

    return horas * 3600000ULL + minutos * 60000ULL + segundos * 1000ULL + milisecundos;
}

void separarArgumentos(char elementos[][50], int quantidade, char* valor)
{
    int controle = 0, i = 0;
    while (valor[i] != '\0' && controle < quantidade)
    {
        if (valor[i] == '"')
        {
            i++;
            int j = 0;
            while(valor[i] != '"')
            {
                elementos[controle][j] = valor[i];
                j++;
                i++;
            }
            elementos[controle][j] = '\0';
            controle++;
        }
        i++;
    }
}

char* formatarMensagem(char* identificacao, int erro)
{
    char tipo[50], *resposta;
    switch (erro) 
    {
        case -1:
            return "[-] Falha ao alocar memória\n";
        case 0:
            return "[+] Operação realizada com sucesso\n";
        case 1:
            strcpy(tipo, "não econtrado\n");
            break;
        case 2:
            strcpy(tipo, "já existe\n");
            break;
        case 3:
            return "[-] Formato de data invalida (dd/mm/AAAA)\n";
        case 4:
            return "[-] Formato de tempo invalido (hh:mm:ss:msms)\n";
        case 5:
            strcpy(tipo, "tem um recorde associado\n");
        
    }

    identificacao[0] = toupper(identificacao[0]);
    snprintf(resposta, sizeof(resposta), "[-] %s %s\n", identificacao, tipo);

    return resposta;
}

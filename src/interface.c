#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "../include/interface.h"
#include "../include/operations.h"
#include "../include/storage.h"
#include "../include/utils.h"

void adicionar()
{
    printf("Modo de Adição\n");
    while (1)
    {
        int controle, resp;
        char campos[4][50], linha[200];

        printf("\nModo de uso: <numero> <valores> / 999 para voltar\n");
        printf("1. Usuario: apelido email nascimento pais\n");
        printf("2. Jogo: nome desenvolvedora data_lancamento genero\n");
        printf("3. Recorde: usuario jogo plataforma tempo\n");
        printf("Obs:\n- Use a data no formato: dd/mm/AAAA\n");
        printf("- Use tempo no formato hh:mm:ss:msms");
        printf("- Use os valores entre aspas duplas\n");
        printf("\n> ");
        scanf("%d", &controle);
        getchar();

        if (controle == 999) break;

        fgets(linha, sizeof(linha), stdin);
        linha[strcspn(linha, "\n")] = '\0';
        separarArgumentos(campos, 4, linha);

        switch(controle)
        {
            case 1:
                printf(usuarioAdd(campos[0], campos[1], campos[2], campos[3]));
                break;
            case 2:
                printf(jogoAdd(campos[0], campos[1], campos[2], campos[3]));
                break;
            case 3:
                printf(recordeAdd(campos[0], campos[1], campos[2], campos[3]));
                break;
            default:
                printf("Numero invalido!\n");
                break;
        }
    }
}

void editar()
{
    printf("Modo de Edição\n");
    while (1)
    {
        int controle, resp, campo;
        char linha[200], campos[3][50];
        printf("\nModo de uso: <numero> <identificador> <campo> <valor> / 999 para voltar\n");
        printf("1. Usuario: *Apelido, Email, Nascimento, Pais\n");
        printf("2. Jogos: *Nome, Desenvolvedora, Data_Lancamento, genero\n");
        printf("3. Recordes: *identificação Usuario, Jogo, Plataforma, Tempo\n");
        printf("Obs: Coloque os valores entre aspas duplas\n");
        printf("\n> ");
        scanf("%d", &controle);
        getchar();

        if (controle == 999) break;
        fgets(linha, sizeof(linha), stdin);
        linha[strcspn(linha, "\n")] = '\0';
        separarArgumentos(campos, 3, linha);

        switch (controle) {
            case 1:
                if (strcmp(campos[1], "apelido") == 0) campo = 1;
                else if (strcmp(campos[1], "email") == 0) campo = 2;
                else if (strcmp(campos[1], "nascimento") == 0) campo = 3;
                else if (strcmp(campos[1], "pais") == 0) campo = 4;
                else 
                {
                    printf("Campo de usuário invalido\n");
                    break;
                }

                printf(usuarioEdit(campos[0], campo, campos[2]));
                break;

            case 2:
                if (strcmp(campos[1], "nome") == 0) campo = 1;
                else if (strcmp(campos[1], "desenvolvedora") == 0) campo = 2;
                else if (strcmp(campos[1], "data_lancamento") == 0) campo = 3;
                else if (strcmp(campos[1], "genero") == 0) campo = 4;
                else 
                {
                    printf("Campo de jogo invalido\n");
                    break;
                }

                printf(jogoEdit(campos[0], campo, campos[2]));
                break;
            case 3:
                if (strcmp(campos[1], "usuario") == 0) campo = 1;
                else if (strcmp(campos[1], "jogo") == 0) campo = 2;
                else if (strcmp(campos[1], "plataforma") == 0) campo = 3;
                else if (strcmp(campos[1], "tempo") == 0) campo = 4;
                else 
                {
                    printf("Campo de recorde invalido\n");
                    break;
                }
                printf(recordeEdit(campos[0], campo, campos[2]));
                break;
            default:
                printf("Numero Invalido\n");
                break;
        }
    }
}

void deletar()
{
    printf("Modo de Deleção\n");
    while (1)
    {
        int controle, resp;
        char valor[30];

        printf("\nModo de uso: <numero> <identificador>\n");
        printf("1. Usuario: Apelido\n");
        printf("2. Jogo: Nome\n");
        printf("3. Recorde: identificador\n");

        scanf("%d", &controle);
        if (controle == 999) break;
        fgets(valor, sizeof(valor), stdin);
        valor[strcspn(valor, "\n")] = '\0';

        switch (controle) {
            case 1:
                printf(usuarioDelete(valor));
                break;
            case 2:
                printf(jogoDelete(valor));
                break;
            case 3:
                printf(recordeDelete(valor));
                break;
            default:
                printf("Numero invalido\n");
                break;
        }
    }
}

void consultar()
{
    printf("Modo de Consulta\n");
    while(1)
    {
        int controle;

        printf("\nModo de uso: \n1. Consulta de Recordes\n2. Listar Usuarios\n3. Listar Jogos\n");

        printf("\n> ");
        scanf("%d", &controle);
        getchar();
        if (controle == 999) break;

        switch(controle)
        {
            case 1:
                char nomeJogador[24];
                char nomeJogo[24];
                char identificacao_recorde[32];

                printf("\nDigite a sua consulta neste formato \n\napelido_jogador\nnome_jogo\nidentificação_recorde\n\nOu '*' para todos daquela posicao\n");
                printf("\nApelido Jogador> ");

                fgets(nomeJogador, sizeof(nomeJogador), stdin);
                nomeJogador[strcspn(nomeJogador, "\n")] = '\0';

                printf("\nNome jogo> ");

                fgets(nomeJogo, sizeof(nomeJogo), stdin);
                nomeJogo[strcspn(nomeJogo, "\n")] = '\0';

                printf("\nIdentificacão Recorde> ");

                fgets(identificacao_recorde, sizeof(identificacao_recorde), stdin);
                identificacao_recorde[strcspn(identificacao_recorde, "\n")] = '\0';

                struct Recordes consulta;
                consulta = consultaRecordes(nomeJogador, nomeJogo, identificacao_recorde);
                if (consulta.tamanho == 0) 
                {
                    printf("Nenhum recorde encontrado\n");
                } else 
                {
                    mostrarRecordes(consulta);
                    printf("Deseja exportar essa tabela? (0/1)\n");

                    int exportar;
                    scanf("%d", &exportar);
                    if (exportar) exportarResultado(&consulta);
                }
                break;
            case 2:
                mostrarUsuarios();
                break;
            case 3:
                mostrarJogos();
                break;
        }
    }
}

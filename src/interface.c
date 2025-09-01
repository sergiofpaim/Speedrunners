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

        printf("Modo de uso: <numero> <valor_campos> / 999 para voltar\n");
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

        for (int i = 0; i < 4; i++)
            printf("%s\n\n", campos[i]);

        switch(controle)
        {
            case 1:
                resp = usuarioAdd(campos[0], campos[1], campos[2], campos[3]);

                if (resp == -1) printf("[-] Erro ao alocar memória\n");
                if (resp == 0) printf("[+] Usuario adicionado!\n");
                if (resp == 1) printf("[-] Nome já existente na base de dados\n");
                if (resp == 2) printf("[-] Formato de data inválido\n");
                break;
            case 2:
                resp = jogoAdd(campos[0], campos[1], campos[2], campos[3]);

                if (resp == -1) printf("[-] Erro ao alocar memória\n");
                if (resp == 0) printf("[+] Jogo adicionado!\n");
                if (resp == 1) printf("[-] jogo já existe na base de dados\n");
                if (resp == 2) printf("[-] Formato de data inválido\n");
                break;
            case 3:
                resp = recordeAdd(campos[0], campos[1], campos[2], campos[3]);

                if (resp == -1) printf("[-] Erro ao alocar memória\n");
                if (resp == 0) printf("[+] Recorde adicionado!\n");
                if (resp == 1) printf("[-] Usuario não encontrado\n");
                if (resp == 2) printf("[-] Jogo não encontrado\n");
                if (resp == 3) printf("[-] Formato de tempo inválido\n");
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
        int controle, resp;
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

        for (int i = 0; campos[1][i] != '\0'; i++)
            campos[1][i] = tolower(campos[1][i]);

        for (int i = 0; i < 3; i++)
            printf("%s\n", campos[i]);

        switch (controle) {
            case 1:
                if (strcmp(campos[1], "apelido") == 0)
                {
                    resp = usuarioEdit(campos[0], 1, campos[2]);

                    if (resp == 0) printf("[+] Usuário alterado com sucesso\n");
                    if (resp == 1) printf("[-] Usuário não encontrado\n");
                    if (resp == 2) printf("[-] Nome de Usuário ja existe\n");
                    if (resp == 3) printf("[-] Formato de data Invalido\n");
                    break;
                }
                if (strcmp(campos[1], "email") == 0)
                {
                    resp = usuarioEdit(campos[0], 2, campos[2]);

                    if (resp == 0) printf("[+] Usuário alterado com sucesso\n");
                    if (resp == 1) printf("[-] Usuário não encontrado\n");
                    if (resp == 2) printf("[-] Nome de Usuário ja existe\n");
                    if (resp == 3) printf("[-] Formato de data Invalido\n");
                    break;
                }
                if (strcmp(campos[1], "nascimento") == 0)
                {
                    resp = usuarioEdit(campos[0], 3, campos[2]);

                    if (resp == 0) printf("[+] Usuário alterado com sucesso\n");
                    if (resp == 1) printf("[-] Usuário não encontrado\n");
                    if (resp == 2) printf("[-] Nome de Usuário ja existe\n");
                    if (resp == 3) printf("[-] Formato de data Invalido\n");
                    break;
                }
                if (strcmp(campos[1], "pais") == 0)
                {
                    resp = usuarioEdit(campos[0], 4, campos[2]);

                    if (resp == 0) printf("[+] Usuário alterado com sucesso\n");
                    if (resp == 1) printf("[-] Usuário não encontrado\n");
                    if (resp == 2) printf("[-] Nome de Usuário ja existe\n");
                    if (resp == 3) printf("[-] Formato de data Invalido\n");
                    break;
                }
                else 
                {
                    printf("Campo de usuário invalido\n");
                    break;
                }
            case 2:
                if (strcmp(campos[1], "nome") == 0)
                { 
                    resp = jogoEdit(campos[0], 1, campos[2]);

                    if (resp == 0) printf("[+] Jogo alterado com sucesso\n");
                    if (resp == 1) printf("[-] Jogo não encontrado\n");
                    if (resp == 2) printf("[-] Nome de jogo ja existe\n");
                    if (resp == 3) printf("[-] Formato de data Invalido\n");
                    break;
                }
                if (strcmp(campos[1], "desenvolvedora") == 0)
                {
                    resp = jogoEdit(campos[0], 2, campos[2]);

                    if (resp == 0) printf("[+] Jogo alterado com sucesso\n");
                    if (resp == 1) printf("[-] Jogo não encontrado\n");
                    if (resp == 2) printf("[-] Nome de jogo ja existe\n");
                    if (resp == 3) printf("[-] Formato de data Invalido\n");
                    break;
                }
                if (strcmp(campos[1], "data_lancamento") == 0)
                {
                    resp = jogoEdit(campos[0], 3, campos[2]);

                    if (resp == 0) printf("[+] Jogo alterado com sucesso\n");
                    if (resp == 1) printf("[-] Jogo não encontrado\n");
                    if (resp == 2) printf("[-] Nome de jogo ja existe\n");
                    if (resp == 3) printf("[-] Formato de data Invalido\n");
                    break;
                }
                if (strcmp(campos[1], "genero") == 0)
                {
                    resp = jogoEdit(campos[0], 4, campos[2]);

                    if (resp == 0) printf("[+] Jogo alterado com sucesso\n");
                    if (resp == 1) printf("[-] Jogo não encontrado\n");
                    if (resp == 2) printf("[-] Nome de jogo ja existe\n");
                    if (resp == 3) printf("[-] Formato de data Invalido\n");
                    break;
                }
                else 
                {
                    printf("Campo de jogo invalido\n");
                    break;
                }
            case 3:
                if (strcmp(campos[1], "usuario") == 0)
                { 
                    resp = recordeEdit(campos[0], 1, campos[2]);

                    if (resp == 0) printf("[+] Recorde alterado com sucesso\n");
                    if (resp == 1) printf("[-] Recorde não econtrado\n");
                    if (resp == 2) printf("[-] Usuário não encontrado\n");
                    if (resp == 3) printf("[-] Jogo não encontrado\n");
                    if (resp == 4) printf("[-] Formato de tempo invalido (hh:mm:ss:msms)\n");
                    break;
                }
                if (strcmp(campos[1], "jogo") == 0)
                {
                    resp = recordeEdit(campos[0], 2, campos[2]);

                    if (resp == 0) printf("[+] Recorde alterado com sucesso\n");
                    if (resp == 1) printf("[-] Recorde não econtrado\n");
                    if (resp == 2) printf("[-] Usuário não encontrado\n");
                    if (resp == 3) printf("[-] Jogo não encontrado\n");
                    if (resp == 4) printf("[-] Formato de tempo invalido (hh:mm:ss:msms)\n");
                    break;
                }
                if (strcmp(campos[1], "plataforma") == 0)
                {
                    resp = recordeEdit(campos[0], 3, campos[2]);

                    if (resp == 0) printf("[+] Recorde alterado com sucesso\n");
                    if (resp == 1) printf("[-] Recorde não econtrado\n");
                    if (resp == 2) printf("[-] Usuário não encontrado\n");
                    if (resp == 3) printf("[-] Jogo não encontrado\n");
                    if (resp == 4) printf("[-] Formato de tempo invalido (hh:mm:ss:msms)\n");
                    break;
                }
                if (strcmp(campos[1], "tempo") == 0)
                {
                    resp = recordeEdit(campos[0], 4, campos[2]);

                    if (resp == 0) printf("[+] Recorde alterado com sucesso\n");
                    if (resp == 1) printf("[-] Recorde não econtrado\n");
                    if (resp == 2) printf("[-] Usuário não encontrado\n");
                    if (resp == 3) printf("[-] Jogo não encontrado\n");
                    if (resp == 4) printf("[-] Formato de tempo invalido (hh:mm:ss:msms)\n");
                    break;
                }
                else 
                {
                    printf("Campo de recorde invalido\n");
                    break;
                }
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

        printf("Modo de uso: <numero> <identificador>\n");
        printf("1. Usuario: Apelido\n");
        printf("2. Jogo: Nome\n");
        printf("3. Recorde: identificador\n");

        scanf("%d", &controle);
        if (controle == 999) break;
        fgets(valor, sizeof(valor), stdin);
        valor[strcspn(valor, "\n")] = '\0';

        switch (controle) {
            case 1:
                resp = usuarioDelete(valor);

                if (resp == 0) printf("[+] Usuario deletado com sucesso\n");
                if (resp == 1) printf("[-] Usuario não econtrado\n");
                if (resp == 2) printf("[-] Usuario possui um recorde associado\n");
                break;
            case 2:
                resp = jogoDelete(valor);
                if (resp == 0) printf("[+] Usuario deletado com sucesso\n");
                if (resp == 1) printf("[-] Recorde não econtrado\n");
                if (resp == 2) printf("[-] Jogo possui um recorde associado\n");
                break;
            case 3:
                resp = recordeDelete(valor);
                if (resp == 0) printf("[+] Recorde deletado com sucesso\n");
                if (resp == 1) printf("[-] Recorde não econtrado\n");
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

        printf("Modo de uso: \n1. Consulta de Recordes\n2. Listar Usuarios\n3. Listar Jogos\n");

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

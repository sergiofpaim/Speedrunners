#include "../include/data.h"
#include "../include/utils.h"
#include "../include/queries.h"
#include "../include/storage.h"
#include "../include/interface.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* ============================================================
   Seção: Operações CRUD (Adicionar, Editar, Deletar)
   - Funções para gerenciar usuarios, jogos e recordes
   ============================================================ */

int usuarioAdd(char* apelido, char* email, char* nascimento, char* pais)
{
    struct Usuario temp;

    strncpy(temp.apelido, apelido, sizeof(temp.apelido)-1);
    strncpy(temp.email, email, sizeof(temp.email)-1);
    strncpy(temp.nascimento, nascimento, sizeof(temp.nascimento)-1);
    strncpy(temp.pais, pais, sizeof(temp.pais)-1);

    if (usuarioQuery(temp.apelido) >= 0)
        return 1;

    if (validarData(temp.nascimento) == 0)
        return 2;

    usuarios.tamanho++;
    usuarios.lista = (struct Usuario *)realloc(usuarios.lista, usuarios.tamanho * sizeof(struct Usuario));
    if (usuarios.lista != NULL)
    {
        usuarios.lista[usuarios.tamanho - 1] = temp;
        return 0;
    }
    else
    {
        usuarios.tamanho--;
        return -1;
    }
}

int jogoAdd(char* nome, char* desenvolvedora, char* data_lancamento, char* genero)
{
    struct Jogo temp;

    strncpy(temp.nome, nome, sizeof(temp.nome)-1);
    strncpy(temp.desenvolvedora, desenvolvedora, sizeof(temp.desenvolvedora)-1);
    strncpy(temp.data_lancamento, data_lancamento, sizeof(temp.data_lancamento)-1);
    strncpy(temp.genero, genero, sizeof(temp.genero)-1);

    if (jogoQuery(temp.nome) >= 0)
        return 1;

    if (validarData(temp.data_lancamento) != 1)
        return 2;

    jogos.lista = (struct Jogo *)realloc(jogos.lista, ++jogos.tamanho * sizeof(struct Jogo));

    if (jogos.lista != NULL)
    {
        jogos.lista[jogos.tamanho - 1] = temp;
        return 0;
    }
    else
    {
        jogos.tamanho--;
        return -1;
    }
}

int recordeAdd(char* usuario, char* jogo, char* plataforma, char* tempo)
{
    struct Recorde temp;

    if (usuarioQuery(usuario) >= 0)
        strcpy(temp.usuario, usuario);
    else
        return 1;

    if (jogoQuery(jogo) >= 0)
        strcpy(temp.jogo, jogo);
    else
        return 2;

    if (validarRecordeTempo(tempo) == 1)
        temp.tempo = converterTempo(tempo);
    else 
        return 3;

    strncpy(temp.plataforma, plataforma, sizeof(temp.plataforma)-1);

    temp.data_registro = time(NULL);

    temp.identificacao = gerarId(1000, 10000);

    recordes.lista = (struct Recorde *)realloc(recordes.lista, ++recordes.tamanho * sizeof(struct Recorde));
    if (recordes.lista != NULL)
    {
        recordes.lista[recordes.tamanho - 1] = temp;
        return 0;
    }
    else
    {
        recordes.tamanho--;
        return -1;
    }
}

int usuarioEdit(char* identificacao, int campo, char* valor)
{
    int posicao;

    if ((posicao = usuarioQuery(identificacao)) >= 0)
    {
        switch (campo)
        {
            case 1:
                if (usuarioQuery(valor) >= 0)
                    return 2;
                else
                {
                    strcpy(usuarios.lista[posicao].apelido, valor);
                    return 0;
                }
                break;
            case 2:
                strcpy(usuarios.lista[posicao].email, valor);
                return 0;
                break;
            case 3:
                if (validarData(valor) != 1)
                    return 3;
                else
                {
                    strcpy(usuarios.lista[posicao].nascimento, valor);
                    return 0;
                    break;
                }
                break;
            case 4:
                strcpy(usuarios.lista[posicao].pais, valor);
                return 0;
                break;
        }
    }
    else return 1;
}

int jogoEdit(char* identificacao, int campo, char* valor)
{
    int posicao;
    if ((posicao = jogoQuery(identificacao)) >= 0)
    {
        switch (campo)
            {
            case 1:
                if (jogoQuery(valor) >= 0)
                    return 2;
                else
                {
                    strcpy(jogos.lista[posicao].nome, valor);
                    return 0;
                }
            
                break;
            case 2:
                strcpy(jogos.lista[posicao].desenvolvedora, valor);
                return 0;
                break;
            case 3:
                if (validarData(valor) != 1)
                    return 3;
                else
                {
                    strcpy(jogos.lista[posicao].data_lancamento, valor);
                    return 0;
                    break;
                }
                break;
            case 4:
                strcpy(jogos.lista[posicao].genero, valor);
                return 0;
                break;
        }
    }
    else
        return 1;
}

int recordeEdit(char* identificacao, int campo, char* valor)
{
    struct Resultados resultado = recordeQuery("*", "*", identificacao);

    if (resultado.tamanho > 0)
    {
        int posicao = resultado.lista[0];
        switch (campo)
        {
            case 1:
                if (usuarioQuery(valor) < 0)
                        return 2;
                else
                {
                    strcpy(recordes.lista[posicao].usuario, usuarios.lista[usuarioQuery(valor)].apelido);
                    return 0;
                }
                break;
            case 2:
                if (jogoQuery(valor) < 0)
                    return 3;
                else
                {
                    strcpy(recordes.lista[posicao].jogo, jogos.lista[jogoQuery(valor)].nome);
                    return 0;
                }
                break;
            case 3:
                strcpy(recordes.lista[posicao].plataforma, valor);
                break;
            case 4:
                    if (validarRecordeTempo(valor) != 1)
                        return 4;
                    else
                    {
                        recordes.lista[posicao].tempo = converterTempo(valor);
                        return 0;
                        break;
                    }
                break;
        }
    }
    else
        return 1;
}

int usuarioDelete(char* identificacao)
{
    int posicao;

    if ((posicao = usuarioQuery(identificacao)) >= 0)
    {
        struct Resultados resultados = recordeQuery(usuarios.lista[posicao].apelido, "*", "*");
        if (resultados.tamanho == 0)
        {
            usuarios.lista[posicao] = usuarios.lista[usuarios.tamanho - 1];
            usuarios.lista = (struct Usuario *)realloc(usuarios.lista, --usuarios.tamanho * sizeof(struct Usuario));
            return 0;
        }
        else
            return 2;
    }
    else
        return 1;
}

int jogoDelete(char* identificacao)
{
    int posicao;
    if ((posicao = jogoQuery(identificacao)) >= 0)
    {
        struct Resultados resultados = recordeQuery("*", jogos.lista[posicao].nome, "*");
        if (resultados.tamanho == 0)
        {
            jogos.lista[posicao] = jogos.lista[jogos.tamanho - 1];
            jogos.lista = (struct Jogo *)realloc(jogos.lista, --jogos.tamanho * sizeof(struct Jogo));
            return 0;
        }
        else
            return 2;
    }
    else
        return 1;
}

int recordeDelete(char* identificacao)
{
    struct Resultados resultado = recordeQuery("*", "*", identificacao);

    if (resultado.tamanho > 0)
    {
        recordes.lista[resultado.lista[0]] = recordes.lista[recordes.tamanho - 1];
        recordes.lista = (struct Recorde *)realloc(recordes.lista, --recordes.tamanho * sizeof(struct Recorde));
        return 0;
    }
    else
        return 1;
}

void mostrarUsuarios()
{
    if (usuarios.tamanho != 0)
    {
        printf("\nUsuarios\n\n");
        printf("--------------------------\n");
        for (int i = 0; i < usuarios.tamanho; i++)
        {
            printf("\nApelido: %s\n", usuarios.lista[i].apelido);
            printf("\nEmail: %s\n", usuarios.lista[i].email);
            printf("\nNascimento: %s\n", usuarios.lista[i].nascimento);
            printf("\nPais: %s\n", usuarios.lista[i].pais);
            printf("--------------------------\n");
        }
    }
    else
        printf("\nNão há usuários adicionados\n");
}

void mostrarJogos()
{
    if (jogos.tamanho != 0)
    {
        printf("\nJogos\n\n");
        printf("\n---\n");
        for (int i = 0; i < jogos.tamanho; i++)
        {
            printf("\nNome: %s\n", jogos.lista[i].nome);
            printf("\nDesenvolvedora: %s\n", jogos.lista[i].desenvolvedora);
            printf("\nData_lancamento: %s\n", jogos.lista[i].data_lancamento);
            printf("\nGênero: %s\n", jogos.lista[i].genero);
            printf("--------------------------\n");
        }
    }
    else
        printf("\nNão há jogos adicionados\n");
}

struct Recordes consultaRecordes(char* nomeJogador, char* nomeJogo, char* identificacao_recorde)
{
    struct Recordes consulta;
    consulta.tamanho = 0;
    consulta.lista = NULL;

    struct Resultados resultados = recordeQuery(nomeJogador, nomeJogo, identificacao_recorde);

    for (int i = 0; i < resultados.tamanho; i++)
    {
        struct Recorde candidato = recordes.lista[resultados.lista[i]];

        int jaExiste = 0;
        for (int k = 0; k < consulta.tamanho; k++)
        {
            if (consulta.lista[k].identificacao == candidato.identificacao)
            {
                jaExiste = 1;
                break;
            }
        }

        if (!jaExiste)
        {
            consulta.lista = realloc(consulta.lista, (consulta.tamanho + 1) * sizeof(struct Recorde));
            consulta.lista[consulta.tamanho] = candidato;
            consulta.tamanho++;
        }
    }

    for (int i = 0; i < consulta.tamanho - 1; i++)
        for (int j = 0; j < consulta.tamanho - 1; j++)
            if (consulta.lista[j].tempo > consulta.lista[j + 1].tempo)
            {
                struct Recorde temp = consulta.lista[j];
                consulta.lista[j] = consulta.lista[j + 1];
                consulta.lista[j + 1] = temp;
            }
    
    return consulta;
}

void mostrarRecordes(struct Recordes consulta)
{
    char linha[128];

    for (int i = 0; i < consulta.tamanho; i++)
    {
        char *tempo_str = formatarTempo(consulta.lista[i].tempo);
        char *data_str = formatarData(consulta.lista[i].data_registro);

        snprintf(linha, sizeof(linha),
                 "%-4d| %-20s | %-15s | %-15s | %-9s | %-10s\n",
                 consulta.lista[i].identificacao,
                 consulta.lista[i].usuario,
                 consulta.lista[i].plataforma,
                 consulta.lista[i].jogo,
                 tempo_str,
                 data_str);

        printf("\n%s", linha);

        free(tempo_str);
        free(data_str);
    }
}

void interpretador(int prompt)
{
    char ajuda[] = "[0] = Ajuda\n[1] = Adicionar elementos\n[2] = Editar elementos\n[3] = Deletar elementos\n[4] = Consultar\n[999] = Finalizar Programa\n";

    switch (prompt)
    {
    case 0:
        printf("\n%s", ajuda);
        break;
    case 1:
        adicionar();
        break;
    case 2:
        editar();
        break;
    case 3:
        deletar();
        break;
    case 4:
        consultar();
        break;
    case 999:
        serializarAlteracoes();
        printf("\nAdeus!\n");
        break;
    default:
        printf("\nComando não encontrado\n");
        break;
    }
}

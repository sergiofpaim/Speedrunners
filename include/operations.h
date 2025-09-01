#ifndef OPERATIONS_H
#define OPERATIONS_H

int usuarioAdd(char* apelido, char* email, char* nascimento, char* pais);
int jogoAdd(char* nome, char* desenvolvedora, char* data_lancamento, char* genero);
int recordeAdd(char* usuario, char* jogo, char* plataforma, char* tempo);
int usuarioEdit(char* identificacao, int campo, char* valor);
int jogoEdit(char* identificacao, int campo, char* valor);
int recordeEdit(char* identificacao, int campo, char* valor);
int usuarioDelete(char* identificacao);
int jogoDelete(char* identificacao);
int recordeDelete(char* identificacao);
void mostrarUsuarios();
void mostrarJogos();
struct Recordes consultaRecordes(char* nomeJogador, char* nomeJogo, char* identificacao_recorde);
void mostrarRecordes(struct Recordes consulta);
void interpretador(int prompt);

#endif

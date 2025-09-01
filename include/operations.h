#ifndef OPERATIONS_H
#define OPERATIONS_H

char* usuarioAdd(char* apelido, char* email, char* nascimento, char* pais);
char* jogoAdd(char* nome, char* desenvolvedora, char* data_lancamento, char* genero);
char* recordeAdd(char* usuario, char* jogo, char* plataforma, char* tempo);
char* usuarioEdit(char* identificacao, int campo, char* valor);
char* jogoEdit(char* identificacao, int campo, char* valor);
char* recordeEdit(char* identificacao, int campo, char* valor);
char* usuarioDelete(char* identificacao);
char* jogoDelete(char* identificacao);
char* recordeDelete(char* identificacao);
void mostrarUsuarios();
void mostrarJogos();
struct Recordes consultaRecordes(char* nomeJogador, char* nomeJogo, char* identificacao_recorde);
void mostrarRecordes(struct Recordes consulta);
void interpretador(int prompt);

#endif

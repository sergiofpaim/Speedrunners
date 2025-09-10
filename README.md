### Trabalho Algoritmos e Programação 2 - Speedrunners

#### Resumo
Programa em C para gerenciar usuários, jogos e recordes (runs) de speedrunning.  
O sistema permite adicionar, editar, remover e consultar dados, além de exportar consultas para um arquivo texto.

Observação: Nosso programa tem as estruturas realocadas de acordo com a necessidade, não usamos espaços extras.

#### Compilação (Windows com MinGW)
Abra um terminal (cmd ou PowerShell) no diretório do projeto e execute:

```bash
gcc src/*.c -o speedrunners.exe
```

ou, se preferir produzir sem extensão no Linux/MinGW:

```bash
```
gcc src/*.c -o speedrunners

#### Execução
No mesmo diretório que o executável:

Windows:
```bash
./speedrunners.exe
```

Linux/Mac:
```bash
./speedrunners
```

#### Arquivos de armazenamento
O programa utiliza a pasta "armazenamento" com os arquivos:
- armazenamento/usuarios.bin
- armazenamento/jogos.bin
- armazenamento/recordes.bin

Ao encerrar o programa com a opção 999 os dados são serializados para esses arquivos.  
O comando de exportação de consulta cria:
- armazenamento/tabela_recordes.txt

#### Formato das entradas
- Datas: dd/mm/aaaa (ex: 05/08/2025)  
- Tempos: hh:mm:ss:msms (ex: 00:12:34:256)  
- Para consultas é possível usar '*' como coringa (todos)

#### Mapa rápido de comandos (menu)
[0] = Ajuda
[1] = Adicionar elementos
[2] = Editar elementos
[3] = Deletar elementos
[4] = Consultar
[999] = Finalizar Programa

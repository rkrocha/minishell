#!/bin/bash

# >
# Redireciona o output de um comando para um arquivo, sobreescrevendo-o
# echo hello > file1
# file1 vai conter apenas "hello", independente do que continha antes



# >>
# redireciona o output de um comando para um arquivo, adicionado àquilo que já está escrito dentro dele.
# echo world >> file1
# file1 vai conter "hello\nworld"




# <
# The commands that normally take their input from the standard input can have their input redirected from a file in this manner.
# Esse comportamento pode ser diferente dependendo do comando. wc e cat funcionam, echo não.

wc -l file1

# é quase o mesmo que

wc -l < file1




# <<
# A here document is used to redirect input into an interactive shell script or program.
# Here the shell interprets the << operator as an instruction to read input until it finds a line containing the specified delimiter. All the input lines up to the line containing the delimiter are then fed into the standard input of the command.
# The delimiter tells the shell that the here document has completed. Without it, the shell continues to read the input forever. The delimiter must be a single word that does not contain spaces or tabs.

# cat << EOF
# Vai ler uma lista de argumentos lidos do stdin até encontrar o delimitador "EOF"
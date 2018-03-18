#Compilateur à utiliser
CC = gcc

#Nom de l'exécutable
BIN = test_tree

#Objets nécessaires à la construction de l'exécutable
OBJECTS = main.o api.o tree.o

#Arguments à passer au compilateur
CFLAGS = -g -Wall

all: main.o api.o tree.o
	$(CC) $(OBJECTS) -o $(BIN)

main.o: main.c *.h
	$(CC) $(CFLAGS) -c main.c

api.o: api.c *.h
	$(CC) $(CFLAGS) -c api.c

tree.o: tree.c *.h
	$(CC) $(CFLAGS) -c tree.c

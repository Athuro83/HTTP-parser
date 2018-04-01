#Compilateur à utiliser
CC = gcc

#Nom de l'exécutable
BIN = test_tree2

#Objets nécessaires à la construction de l'exécutable
OBJECTS = main.o api.o tree.o split.o

#Arguments à passer au compilateur
CFLAGS = -g -Wall

all: main.o api.o tree.o split.o
	$(CC) $(OBJECTS) -o $(BIN)

main.o: main.c *.h
	$(CC) $(CFLAGS) -c main.c

api.o: api.c *.h
	$(CC) $(CFLAGS) -c api.c

tree.o: tree.c *.h
	$(CC) $(CFLAGS) -c tree.c

split.o: split.c *.h
	$(CC) $(CFLAGS) -c split.c

#Compilateur à utiliser
CC = gcc

#Nom de l'exécutable
BIN = parser

#Objets nécessaires à la construction de l'exécutable
OBJECTS = main.o api.o tree.o split.o check.o

#Arguments à passer au compilateur
CFLAGS = -g -Wall

parser: main.o api.o tree.o split.o check.o
	$(CC) $(OBJECTS) -o $(BIN)

main.o: main.c *.h
	$(CC) $(CFLAGS) -c main.c

api.o: api.c *.h
	$(CC) $(CFLAGS) -c api.c

tree.o: tree.c *.h
	$(CC) $(CFLAGS) -c tree.c

split.o: split.c *.h
	$(CC) $(CFLAGS) -c split.c

check.o: check.c *.h
	$(CC) $(CFLAGS) -c check.c

clean:
	$(RM) -f $(OBJECTS)

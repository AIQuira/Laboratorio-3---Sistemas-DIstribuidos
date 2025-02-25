#VARIABLES
CC = gcc
CFLAGS = -g -Wall -O2
SRC = server.c funciones.c funciones.h
OBJ = server.o funciones.o

#Reglas explicitas
all: $(OBJ)
	$(CC) -pthread $(CFLAGS) -o ejecutablemain $(OBJ)

clean:
	$(RM) $(OBJ) ejecutablemain

#Reglas implicitas
server.o: server.c funciones.h
funciones.o: funciones.c
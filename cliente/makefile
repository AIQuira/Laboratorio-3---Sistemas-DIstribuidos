#VARIABLES
CC = gcc
CFLAGS = -g -Wall -O2
SRC = client.c funciones.c funciones.h
OBJ = client.o funciones.o

#REGLAS EXPLICITAS
all: $(OBJ)
	$(CC) $(CFLAGS) -o ejecutablemain $(OBJ)
	
clean: 
	$(RM) $(OBJ) ejecutablemain

#REGLAS IMPLICITAS

client.o: client.c funciones.h
funciones.o: funciones.c
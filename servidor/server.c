#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <locale.h>
#include "funciones.h"
#define BACK_LOG 5

int serverSocket = 0;
struct sockaddr_in serverName;
modulo vectorModulos[3];

// Función que obtiene los datos de la petición del cliente y
// escribe el resultado en el identificador del cliente obtenido mediante accept
void *funcion(void *param)
{
	int *id;
	id = (int *)param;
	char identificacion[50];
	respuestaDTO objRespuesta;
	// Leemos el canal virtual
	read((int)*id, &identificacion, sizeof(identificacion));
	objRespuesta = asignarModulo(identificacion, vectorModulos);
	generarTiempo();
	write((int)*id, &objRespuesta, sizeof(objRespuesta));
	close(*id); // Cierra el canal virtual
	free(id);	// Libera la memoria asignada al canal virtual
}

typedef void *(*thread_start_func)(void *arg);

typedef struct
{
	pthread_t id;
	pthread_attr_t attr;
	thread_start_func start_func;
	void *arg;
} Thread;

Thread *start_thread(thread_start_func func, void *arg)
{
	Thread *t;
	t = (Thread *)malloc(sizeof(Thread));
	t->start_func = func;
	t->arg = arg;
	pthread_attr_init(&(t->attr));
	pthread_create(&(t->id), &(t->attr), (void *)t->start_func, t->arg);

	return t;
}

void generarTiempo()
{
	pthread_t thread_id = pthread_self();
	printf("\n Identificador del hilo actual: %d\n", (int)thread_id);
	sleep(10);
	fflush(stdout);
}

/*double operacion(char operador[], char numero1[], char numero2[])
{
	double resultado = 0;
	if (strcmp(operador, "*") == 0)
	{
		resultado = atof(numero1) * atof(numero2);

		printf("\n %f %f %f", resultado, atof(numero1), atof(numero2));
	}
	else if (strcmp(operador, "-") == 0)
	{
		resultado = atof(numero1) - atof(numero2);
	}
	else if (strcmp(operador, "+") == 0)
	{
		resultado = atof(numero1) + atof(numero2);
	}
	else if (strcmp(operador, "/") == 0)
	{
		resultado = atof(numero1) / atof(numero2);
	}
	else
	{
		resultado = 0;
	}
	return resultado;
}*/

// funcion que obtiene los datos de la peticion del cliente y escribe el resultado
// en el identificador del cliente obtenido mediante el accept
/*void * funcion(void *param) {
	int * id;
	id = (int*)param;
	char operador[50], numero1[50], numero2[50], resultado[50];
	char dircliente[50];
	int res;
	//leemos del canal virtual
	read((int)*id, &operador, sizeof(operador));
	read((int)*id, &numero1, sizeof(numero1));
	read((int)*id, &numero2, sizeof(numero2));

	//fflush(stdout);
	generarTiempo();
	printf("\nId canal virtual: %d, op: %s, n1: %s, n2: %s",*id, operador,numero1,numero2);

	if((atof(numero2)==0.0) && (strcmp(operador,"/")==0))
	{
		//escribimos en el canal
		char  resultado[50]="Error divicion por 0";
		write((int)*id,&resultado,sizeof(resultado));
	}
	else
	{
		char  resultado[50]="";
		double resultadoOper=operacion(operador,numero1,numero2);
		//escribimos en el canal
		sprintf(resultado,"%f",resultadoOper);
		write((int)*id,&resultado,sizeof(resultado));
	}
	close(*id);  // Cierra el canal virtual
	free(id);    // Libera la memoria asignada al canal virtual
}*/

void connectSC()
{

	int puertoServidor = 5001;
	// la funcion socket crea un socket y retorna su descriptor
	// el cual se almacena en la variable serverSocket
	serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (serverSocket == -1)
	{
		printf("Error al crear el socket");
		exit(1);
	}
	serverName.sin_family = AF_INET;
	serverName.sin_port = htons(puertoServidor);
	serverName.sin_addr.s_addr = htonl(INADDR_ANY); /*se establece la direccion de la maquina del socket, INADDR_ANY indica que la direccion corresponde
							  a la maquina donde se ejecuta el programa servidor*/

	int status = bind(serverSocket, (struct sockaddr *)&serverName, sizeof(serverName)); /*Se asocia el socket del servidor con el puerto y direccion IP del servidor*/

	if (status == -1)
	{
		printf("Error en bind()\n");
		exit(1);
	}
	int numeroMaximoConexiones = 5;

	while (1)
	{
		status = listen(serverSocket, numeroMaximoConexiones);

		if (status == -1)
		{
			printf("Error en funcion listen()\n");
			exit(1);
		}

		// acepta una conexion, crea un socket y devuleve el descritor del nuevo socket el cual es conectado con el socket del cliente
		int *referenciaSocketCliente = (int *)malloc(sizeof(int));
		*referenciaSocketCliente = accept(serverSocket, (struct sockaddr *)0, (int *)NULL);

		printf("\n\nNuevo cliente conectado ");
		fflush(stdout);

		Thread *hilo;
		hilo = start_thread(funcion, (void *)referenciaSocketCliente);
	}
}

int main(int argc, char *argv[])
{
	printf("Iniciando servidor...\n\n");
	cargarModulos(vectorModulos);
	connectSC();
	printf("Terminó el servidor...\n");
}

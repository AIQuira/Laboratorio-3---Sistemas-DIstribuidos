
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<string.h>
#include "funciones.h"

int main(int argc, char *argv[]) {

   respuestaDTO objRespuesta;
   int opcion = 0;
   int socketDelCliente, puertoDelServidor, status = 0;
   struct sockaddr_in datosConexionConElServidor={0};//CONTIENE LA DIRECCION Y PUERTO DEL SERVIDOR
   char direccionDelServidor[16]= "127.0.0.1";  //DIRECCION DEL SERVIDOR    
   puertoDelServidor= 5001;  //PUERTO PREESTABLECIDO PARA EL CLIENTE Y EL SERVIDOR
   do{
      
      socketDelCliente = socket(PF_INET,SOCK_STREAM,IPPROTO_TCP);

      if(socketDelCliente ==-1) {
         printf("No es posible crear el socket\n");
         exit(1);
      }

      datosConexionConElServidor.sin_family = AF_INET;//Espacio de direcciones que permite una conexiòn a una maquina
      datosConexionConElServidor.sin_port = htons(puertoDelServidor);//asignacion del puerto del servidor
      datosConexionConElServidor.sin_addr.s_addr = inet_addr(direccionDelServidor); //asignacion de la direccion del servidor;
      status = connect(socketDelCliente,(struct sockaddr *)& datosConexionConElServidor,sizeof(datosConexionConElServidor));

      if(status==-1) {
         printf("Error al realizar la conexion\n");
         exit(-1);
      }
      printf("--Menu--\n");
      printf("1. Asignar modulo\n");
      printf("2. Salir\n");
      printf("seleccione una opcion:");
      scanf("%d",&opcion);
      getchar();

      char identificacion[MAXIMA_LONGITUD_CADENA];
        printf("Digite la identificacion: ");
        fgets(identificacion,MAXIMA_LONGITUD_CADENA,stdin);
        strtok(identificacion,"\n");

        write(socketDelCliente,identificacion,sizeof(identificacion));
        read(socketDelCliente,&objRespuesta,sizeof(objRespuesta)); 
        if(objRespuesta.codigo==200){
            printf("EL modulo %s esta activo y libre\n",objRespuesta.nombreModuloAsignado);
        }
        else{
            printf("No hay modulos disponibles\n");
        }

        printf("El turno signado es %d \n",objRespuesta.turnoAsignado);
        close(socketDelCliente);

   }while(opcion==1); 

}

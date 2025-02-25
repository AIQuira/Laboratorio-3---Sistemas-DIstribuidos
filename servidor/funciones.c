#include <string.h>
#include <stdbool.h>
#include "funciones.h"
#include "stdio.h"

#define MAXIMA_LONGITUD_CADENA 50

int noTurno=1;

respuestaDTO asignarModulo(char identificacion[MAXIMA_LONGITUD_CADENA], modulo vectorModulos[])
{
    respuestaDTO objRespuesta;
    objRespuesta.codigo = 403;
    objRespuesta.turnoAsignado = noTurno;
    noTurno++;
    for (int i=0; i<3;i++)
    {
        if(vectorModulos[i].esActivado == true && vectorModulos[i].esLibre == true)
        {
            strcpy(objRespuesta.nombreModuloAsignado, vectorModulos[i].nombreModulo);
            vectorModulos[i].esLibre = false;
            objRespuesta.codigo = 200;
            break;
        }
    }
    return objRespuesta;
}

void cargarModulos(modulo vectorModulos[])
{
    modulo objModulo1, objModulo2, objModulo3;
    objModulo1.esLibre = false;
    objModulo1.esActivado = false;
    strcpy(objModulo1.nombreModulo, "modulo 1");
    objModulo2.esLibre = true;
    objModulo2.esActivado = true;
    strcpy(objModulo2.nombreModulo, "modulo 2");
    objModulo3.esLibre = true;
    objModulo3.esActivado = true;
    strcpy(objModulo3.nombreModulo, "modulo 3");
    vectorModulos[0] = objModulo1;
    vectorModulos[1] = objModulo2;
    vectorModulos[2] = objModulo3;
}
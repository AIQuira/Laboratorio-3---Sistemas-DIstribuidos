#include "funciones.h"
#include <stdbool.h>

typedef struct{
    char nombreModulo[MAXIMA_LONGITUD_CADENA];
    bool esLibre;
    bool esActivado;
}modulo;
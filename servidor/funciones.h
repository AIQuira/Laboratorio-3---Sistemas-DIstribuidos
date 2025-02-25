#include <stdbool.h>
#define MAXIMA_LONGITUD_CADENA 50

typedef struct{
    char nombreModulo[MAXIMA_LONGITUD_CADENA];
    bool esLibre;
    bool esActivado;
}modulo;

typedef struct{
    int turnoAsignado;
    char nombreModuloAsignado[MAXIMA_LONGITUD_CADENA];
    int codigo;
}respuestaDTO;

respuestaDTO asignarModulo(char identificacion [MAXIMA_LONGITUD_CADENA], modulo vectorModulos[]);
void cargarModulos (modulo vectorModulos[]);
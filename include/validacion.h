#ifndef VALIDACION_H
#define VALIDACION_H

#include "componentes.h"
#include "conexiones.h"

#define TAMANO_MENSAJE_VALIDACION 300

typedef struct {
    int valido;
    char mensaje[TAMANO_MENSAJE_VALIDACION];
} ResultadoValidacion;

ResultadoValidacion ValidarMicrorred(ListaComponentes *componentes,
                                     ListaConexiones *conexiones);

#endif

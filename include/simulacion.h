#ifndef SIMULACION_H
#define SIMULACION_H

#include "componentes.h"
#include "conexiones.h"

#define TAMANO_MENSAJE_SIMULACION 400

typedef struct {
    int exitosa;

    float potencia_solar_W;
    float potencia_carga_W;
    float potencia_bateria_W;

    float excedente_W;
    float deficit_W;

    float estado_carga_inicial;
    float estado_carga_final;

    char mensaje[TAMANO_MENSAJE_SIMULACION];
} ResultadoSimulacion;

/*
 * Ejecuta una simulacion basica del flujo de potencia de la microrred.
 * Antes de simular, llama al modulo de validacion.
 */
ResultadoSimulacion SimularFlujoPotencia(ListaComponentes *componentes,
                                         ListaConexiones *conexiones);

#endif

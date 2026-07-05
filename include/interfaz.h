#ifndef INTERFAZ_H
#define INTERFAZ_H
#include "raylib.h"
#include "componentes.h"
#include <stdio.h>
typedef struct {

    int componente_seleccionado;
    int arrastrando;
    float desplazamiento_x;
    float desplazamiento_y;
    int estado_validacion;
    int estado_simulacion;
    int dibujando;
} IState; // Es la estructura que almacena estado de la interfaz

void IState_Init(IState *state);
void I_Update(IState *state, ListaComponentes *componentes, ListaConexiones *conexiones);
void I_Draw(const IState *state, const ListaComponentes *componentes, const ListaConexiones *conexiones);

#endif 
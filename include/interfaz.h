#ifndef INTERFAZ_H
#define INTERFAZ_H
#include "raylib.h"
#include "componentes.h"
#include <stdio.h>
typedef struct {

    int selected_component_id;
    int dragging;
    float drag_offset_x;
    float drag_offset_y;
    int estado_validacion;
    int estado_simulacion;
} IState; // Es la estructura que almacena estado de la interfaz

void IState_Init(IState *state);
void I_Update(IState *state, ListaComponetes *componentes);
void I_Draw(const IState *state, const ListaComponetes *componentes);

#endif 
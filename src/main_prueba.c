#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"
#include "componentes.h"
#include "interfaz.h"

void main(void){   
    const int screenWidth = 800;
    const int screenHeight = 450;

    ListaComponentes componentes;
    
    IState interfaz;

    IState_Init(&interfaz);

    InitWindow(screenWidth, screenHeight, "Simulador Interactivo de Microrred en C");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        I_Update(&interfaz, &componentes);
        I_Draw(&interfaz, &componentes);
    }

    CloseWindow();
}
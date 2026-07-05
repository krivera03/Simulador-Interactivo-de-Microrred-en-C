#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"
#include "componentes.h"
#include "interfaz.h"

int main(void){   
    const int screenWidth = 1200;
    const int screenHeight = 800;

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
    return 0;
}
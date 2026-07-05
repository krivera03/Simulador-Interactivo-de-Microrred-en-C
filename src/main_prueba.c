#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"
#include "componentes.h"
#include "interfaz.h"

int main(void){   
    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight()-100;

    ListaComponentes componentes;
    Iniciar_ListaComponentes(&componentes);
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
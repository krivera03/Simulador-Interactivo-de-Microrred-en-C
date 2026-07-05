#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"
#include "componentes.h"
#include "interfaz.h"
#include "conexiones.h"
#include "validacion.h"
#include "simulacion.h"

int main(void){   
    const int screenWidth = 1200;
    const int screenHeight = 700;

    ListaComponentes componentes;
    ListaConexiones conexiones;
    
    Iniciar_ListaComponentes(&componentes);
    Iniciar_ListaConexiones(&conexiones);
    IState interfaz;

    IState_Init(&interfaz);

    InitWindow(screenWidth, screenHeight, "Simulador Interactivo de Microrred en C");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        I_Update(&interfaz, &componentes, &conexiones);
        I_Draw(&interfaz, &componentes, &conexiones);
    }

    CloseWindow();
    return 0;
}
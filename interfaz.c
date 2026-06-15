#include "raylib.h"
#include "componentes.h"
#define MAX_ELEMENTS_COUNT    5




int main(void)
{
    // Inicialización
    ListaComponetes lista = {0};  
    lista.componentes[0] = (Componente){1, panel_solar, 100, 100, 12, 100, 0, 0};
    lista.componentes[1] = (Componente){2, bateria, 200, 100, 24, 200, 5, 80};

    lista.cuenta = 2;



    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    
    

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    // Main interfaz loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        // TODO: Update your variables here

        // Draw
        BeginDrawing();

            ClearBackground(RAYWHITE);
            for (int i = 0; i < lista.cuenta; i++)
             {
            Componente c = lista.componentes[i];
            DrawRectangle(c.x, c.y, 50, 50, BLUE);
            }

            DrawText("Componentes", 190, 200, 20, LIGHTGRAY);

        EndDrawing();
    }

    // De-Initialization
    CloseWindow();        // Close window and OpenGL context

    return 0;
}

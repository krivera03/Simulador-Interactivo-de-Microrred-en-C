#include "componentes.h"
#include "interfaz.h"
#define WIDTH 100
#define HEIGHT 80


static Vector2 Centro_Componente(const Componente *componente) { //retorna el centro del componente
    Vector2 centro;
    centro.x = componente->x;
    centro.y = componente->y; // x y del rectangulo es 
    return centro;
}

static Color Componente_Color(TipoComponente tipo) {
    switch (tipo) {
        case panel_solar:
            return (Color){255, 209, 102, 255};
        case controlador:
            return (Color){17, 138, 178, 255};
        case bateria:
            return (Color){6, 214, 160, 255};
        case carga:
            return (Color){239, 71, 111, 255};
        default:
            return LIGHTGRAY;
    }
}

static Rectangle Componente_Rect(const Componente *componente) {//retorna el rectángulo del componente
    Rectangle rect;
    rect.x = componente->x - WIDTH / 2.0f; 
    rect.y = componente->y  + HEIGHT / 2.0f; // xy sera del centro, el rectangulo se dibuja desde la esquina superior izquierda, por eso se resta la mitad del ancho y se suma la mitad de la altura
    rect.width = WIDTH;
    rect.height = HEIGHT;
    
    return rect;
}

static void DrawBoton(Rectangle rect, const char *text) { //Crea botones para validar, simular y reiniciar
    Vector2 mouse = GetMousePosition();
    int lo_toca = CheckCollisionPointRec(mouse, rect);

    DrawRectangleRounded(rect, 0.18f, 8, lo_toca ? SKYBLUE : LIGHTGRAY); //debe
    DrawRectangleLinesEx(rect, 2.0f, DARKGRAY);
    DrawText(text, (int)rect.x , (int)rect.y, 20, DARKBLUE);
}

static int LeftClick(Rectangle rect) {
    return IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), rect);
}
static int RightClick(Rectangle rect) {
    return IsMouseButtonPressed(MOUSE_RIGHT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), rect);
}

static void DrawComponente(const Componente *componente) {
    Rectangle rect = Componente_Rect(componente);
    Color color = Componente_Color(componente->tipo);

    DrawRectangleRounded(rect, 0.15f, 10, color);
    //DrawRectangleLinesEx(rect, seleccionado ? 4.0f : 2.0f, seleccionado ? RED : DARKGRAY);

    DrawText(Buscar_ComponenteNombre(componente->tipo), (int)componente->x-WIDTH/2, (int)componente->y+HEIGHT/2, 18, DARKGRAY);

    char texto[96];
    snprintf(texto, sizeof(texto), "%.0f V", componente->voltaje);
    DrawText(texto, (int)componente->x-WIDTH/2 , (int)componente->y, 16, DARKGRAY);
    switch (componente->tipo) {
    case 0: // panel_solar
        snprintf(texto, sizeof(texto), " %.0f W", componente->potencia);
        break;
    case 1: // bateria
        snprintf(texto, sizeof(texto), "SOC: %.0f%%", componente->estado_carga);
        break;
    case 2: // carga    
        snprintf(texto, sizeof(texto), "Carga: %.0f W", componente->potencia);
        break;
    case 3: // controlador
        snprintf(texto, sizeof(texto), "Bat Load");
        break;
    
    default:
        snprintf(texto, sizeof(texto), "Desconocido");
    }

    DrawText(texto, (int)componente->x, (int)componente->y, 16, DARKGRAY);
}


static void DrawPanelComponentes(void) {
    DrawRectangle(0, 0, 100, GetScreenHeight(), (Color){236, 245, 245, 255});
    DrawText("Microrred", 28, 25, 30, DARKBLUE);
    DrawText("Componentes", 28, 75, 20, DARKGRAY);

    DrawRectangleRounded((Rectangle){25, 115, 170, 45}, 0.15f, 8, (Color){255, 209, 102, 255});
    DrawText("Panel solar", 45, 128, 18, DARKBLUE);

    DrawRectangleRounded((Rectangle){25, 175, 170, 45}, 0.15f, 8, (Color){17, 138, 178, 255});
    DrawText("Controlador", 45, 188, 18, RAYWHITE);

    DrawRectangleRounded((Rectangle){25, 235, 170, 45}, 0.15f, 8, (Color){6, 214, 160, 255});
    DrawText("Bateria", 45, 248, 18, DARKBLUE);

    DrawRectangleRounded((Rectangle){25, 295, 170, 45}, 0.15f, 8, (Color){239, 71, 111, 255});
    DrawText("Carga", 45, 308, 18, RAYWHITE);

    //DrawText("MVP:", 28, 390, 18, DARKBLUE);
    DrawText("Arrastre los bloques", 28, 420, 16, DARKGRAY);
    DrawText("y presione validar", 28, 420+16*1, 16, DARKGRAY);
    DrawText("o simular.", 28, 420+16*2, 16, DARKGRAY);
    DrawText("Click derecho", 28, 420+16*3, 16, DARKGRAY);
    DrawText("para eliminar", 28, 420+16*4, 16, DARKGRAY); 
}


void IState_Init(IState *state) {
    if (state == NULL) {
        printf("Error: IState_Init received a NULL pointer.\n");
        return;
    }

    state->componente_seleccionado = -1;
    state->arrastrando = 0;
    state->desplazamiento_x = 0.0f;
    state->desplazamiento_y = 0.0f;
    state->estado_validacion = 0;
    state->estado_simulacion = 0;
}


void I_Update(IState *state, ListaComponentes *componentesID) {
    if (state == NULL || componentesID == NULL) {
        return;
    }

    Rectangle boton_validar = { 1200-130-25, 50, 130, 50};
    Rectangle boton_simular = {1200-130-25, 50*2, 130, 50};
    Rectangle boton_reiniciar = {1200-130-25, 50*3, 130, 50};
    if (LeftClick(boton_validar)) {
        printf("Validar\n");
    }
    if (LeftClick(boton_simular)) {
        printf("Simular\n");
    }
    if (LeftClick(boton_reiniciar)) {
        printf("Reiniciar\n");
    }
/**
    if (RectClick(boton_validar)) {
        state->estado_validacion = FuncionValidar;
        state->estado_validacion = 1;
        state->estado_simulacion = 0;
    }

    if (RectClick(boton_simular)) {
        state->estado_simulacion = FuncionSimular;
        state->estado_simulacion = 1;
    }

    if (RectClick(boton_reiniciar)) {
        FuncionReiniciarCaso();
        state->estado_validacion = 0;
        state->estado_simulacion = 0;
        state->componente_id = -1;
    }
 **/
    Vector2 mouse = GetMousePosition();

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {

    Rectangle btnPanel = {25, 115, 170, 45};
    Rectangle btnControlador = {25, 175, 170, 45};
    Rectangle btnBateria = {25, 235, 170, 45};
    Rectangle btnCarga = {25, 295, 170, 45};

    if (LeftClick(btnPanel)) {
        AgregarComponentes(componentesID, panel_solar, mouse.x, mouse.y, 12, 100, 0, 0);
    }

    if (LeftClick(btnControlador)) {
        AgregarComponentes(componentesID, controlador, mouse.x, mouse.y, 12, 0, 0, 0);
    }

    if (LeftClick(btnBateria)) {
        AgregarComponentes(componentesID, bateria, mouse.x, mouse.y, 12, 0, 5, 50);
    }

    if (LeftClick(btnCarga)) {
        AgregarComponentes(componentesID, carga, mouse.x, mouse.y, 12, 60, 0, 0);
    }


        for (int i = componentesID->cuenta - 1; i >= 0; i--) {
            Componente *componente = &componentesID->componentes[i];
            Rectangle rect = Componente_Rect(componente);


            if (LeftClick(rect)) {
                state->componente_seleccionado = componente->id;
                state->arrastrando = 1;
                state->desplazamiento_x = mouse.x - componente->x;
                state->desplazamiento_y = mouse.y - componente->y;
                break;
            }
        }
    }

    if (state->arrastrando && IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
        Componente *componente = Buscar_ComponenteID(componentesID, state->componente_seleccionado);
        if (componente != NULL) {
            componente->x = mouse.x - state->desplazamiento_x;
            componente->y = mouse.y - state->desplazamiento_y;
            // limites de pantalla para que no se salga de la zona de trabajo
            if (componente->x < 180.0f) {
                componente->x = 180.0f;
            }
            if (componente->y < 0.0f) {
                componente->y = 0.0f;
            }
            if (componente->x > 1000.0f) {
                componente->x = 1000.0f;
            }
            if (componente->y > 700.0f) {
                componente->y = 700.0f;
            }
        }
    }

    if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
        state->arrastrando = 0;
    }

    if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {
        for (int i = componentesID->cuenta - 1; i >= 0; i--) {
            Componente *componente = &componentesID->componentes[i];
            Rectangle rect = Componente_Rect(componente);

            if (RightClick(rect)) {
                // Eliminar el componente de la lista
                for (int j = i; j < componentesID->cuenta - 1; j++) {
                    componentesID->componentes[j] = componentesID->componentes[j + 1];
                }
                componentesID->cuenta--;
                break;
            }
        }
    }

}



void I_Draw(const IState *state, const ListaComponentes *componentesID) {
    if (state == NULL || componentesID == NULL) {
        return;
    }

    BeginDrawing();
    ClearBackground(RAYWHITE);

    DrawPanelComponentes();

   // DrawText("Simulador Interactivo de Microrred en C", 260, 25, 28, DARKBLUE);
    //DrawText("Sistema base: panel solar + controlador + bateria + carga", 260, 62, 18, DARKGRAY);

    DrawRectangleLinesEx((Rectangle){220, 0, 805, 700}, 4.0f, LIGHTGRAY);
    DrawText("Area de trabajo", 240, 30, 18, GRAY);

    // Agregar funcion para dibujar conexiones entre componentes

    for (int i = 0; i < componentesID->cuenta; i++) {
        //int componente_seleccionado = componentesID->componentes[i].id == state->componente_seleccionado;
        DrawComponente(&componentesID->componentes[i]);
    }

    DrawBoton((Rectangle){1200-130-25, 50, 130, 50}, "Validar");
    DrawBoton((Rectangle){1200-130-25, 50*2, 130, 50}, "Simular");
    DrawBoton((Rectangle){1200-130-25, 50*3, 130, 50}, "Reiniciar");

    DrawRectangleRounded((Rectangle){1200-130-25, 50*4, 130, 50*4}, 0.12f, 8, LIGHTGRAY);
    DrawText("Resultado:", 1200-130-25, 50*5 + 25, 18, DARKBLUE);
    //Implementar pestaña de resultados de validacion y simulacion
    EndDrawing();
}




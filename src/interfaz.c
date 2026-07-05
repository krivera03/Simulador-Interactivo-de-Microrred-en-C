#include "componentes.h"
#include "conexiones.h"
#include "interfaz.h"
#define WIDTH 130
#define HEIGHT 80


static Vector2 Centro_Componente(const Componente *componente) { //retorna el centro del componente
    Vector2 centro;
    centro.x = componente->x+WIDTH/2; // x y del rectangulo es la esquina superior izquierda, por eso se suma la mitad del ancho y se suma la mitad de la altura
    centro.y = componente->y+HEIGHT/2; // x y del rectangulo es 
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
        case convertidor:
            return (Color){239, 138, 102, 255};
        default:
            return LIGHTGRAY;
    }
}

static Rectangle Componente_Rect(const Componente *componente) {//retorna el rectángulo del componente
    Rectangle rect;
    rect.x = componente->x ; 
    rect.y = componente->y ; // xy sera del centro, el rectangulo se dibuja desde la esquina superior izquierda, por eso se resta la mitad del ancho y se suma la mitad de la altura
    rect.width = WIDTH;
    rect.height = HEIGHT;
    
    return rect;
}

static void DrawBoton(Rectangle rect, const char *text) { //Crea botones para validar, simular y reiniciar
    Vector2 mouse = GetMousePosition();
    int lo_toca = CheckCollisionPointRec(mouse, rect);

    DrawRectangleRounded(rect, 0.18f, 8, lo_toca ? SKYBLUE : LIGHTGRAY); //debe
    DrawRectangleLinesEx(rect, 2.0f, DARKGRAY);
    DrawText(text, (int)rect.x+15 , (int)rect.y+15, 20, DARKBLUE);
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

    DrawText(Buscar_ComponenteNombre(componente->tipo), (int)componente->x+5, (int)componente->y+HEIGHT/2, 18, RAYWHITE);

    char texto[96];
    snprintf(texto, sizeof(texto), "%.0fVdc", componente->voltajeDC);
    
    DrawText(texto, (int)componente->x+5 , (int)componente->y+20, 16, RAYWHITE);
    
    snprintf(texto, sizeof(texto), "%.0fVac", componente->voltajeAC);
    
    DrawText(texto, (int)componente->x+WIDTH/2 , (int)componente->y+20, 16, RAYWHITE);
    switch (componente->tipo) {
    case 0: // panel_solar
        snprintf(texto, sizeof(texto), " %.0f W", componente->potencia);
        break;
    case 1: // bateria
        snprintf(texto, sizeof(texto), "SOC: %.0f%%", componente->estado_carga);
        DrawText(texto, (int)componente->x+WIDTH/2-5, (int)componente->y+60, 16, RAYWHITE);
        snprintf(texto, sizeof(texto), "%.1f Ah", componente->capacidad_Ah);
        break;
    case 2: // carga    
        snprintf(texto, sizeof(texto), "%.0f W", componente->potencia);
        break;
    case 3: // controlador
        snprintf(texto, sizeof(texto), "Bat   Load");
        break;
    case 4: // convertidor
        snprintf(texto, sizeof(texto), " %.0f W", componente->potencia);
        break;
    
    default:
        snprintf(texto, sizeof(texto), "Desconocido");
    }

    DrawText(texto, (int)componente->x+5, (int)componente->y+60, 16, RAYWHITE);
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

    DrawRectangleRounded((Rectangle){25, 355, 170, 45}, 0.15f, 8, (Color){239, 138, 102, 255});
    DrawText("Convertidor", 45, 368, 18, DARKBLUE);

    DrawRectangleRounded((Rectangle){25, 415, 170, 45}, 0.15f, 8, (Color){200, 200, 200, 255});
    DrawText("Dibujar", 45, 428, 18, DARKBLUE);

    //DrawText("MVP:", 28, 390, 18, DARKBLUE);

    DrawText("Arrastre los bloques", 28, 500, 16, DARKGRAY);
    DrawText("y presione validar", 28, 500+16*1, 16, DARKGRAY);
    DrawText("o simular.", 28, 500+16*2, 16, DARKGRAY);
    DrawText("Click derecho", 28, 500+16*3, 16, DARKGRAY);
    DrawText("para eliminar", 28, 500+16*4, 16, DARKGRAY); 
}

static int ObtenerComponenteBajoMouse(const ListaComponentes *lista) {
    Vector2 mouse = GetMousePosition();

    for (int i = 0; i < lista->cuenta; i++) {
        Rectangle bounds = Componente_Rect(&lista->componentes[i]);
        printf("Tipo de componente: %d, ID: %d, x: %.2f, y: %.2f\n", lista->componentes[i].tipo, lista->componentes[i].id, lista->componentes[i].x, lista->componentes[i].y);
        if (CheckCollisionPointRec(mouse, bounds)) {
            return lista->componentes[i].id;
        }
    }

    return -1;
}



static void DrawConexion(const ListaComponentes *listacomp, const ListaConexiones *listaconx) { //Dibuja conexion entre dos elementos, ahora ver como detectar que quiero una conexion
    for (int i = 0; i < listaconx->cuenta; i++) {
        const Componente *terminal1 = Buscar_ComponenteID(listacomp, listaconx->conexiones[i].origenID);
        const Componente *terminal2 = Buscar_ComponenteID(listacomp, listaconx->conexiones[i].destinoID);

        if (terminal1 == NULL || terminal2 == NULL) {
            continue;
        }

        Vector2 a = Centro_Componente(terminal1);
        Vector2 b = Centro_Componente(terminal2);
        DrawLineEx(a, b, 4.0f, DARKGRAY);
        DrawCircleV(a, 5.0f, DARKGRAY);
        DrawCircleV(b, 5.0f, DARKGRAY);
    }
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
    state->dibujando = 0;
    state->desdeID = -1;
    state->hastaID = -1;
    state->arrastrando_linea = 0;
}


void I_Update(IState *state, ListaComponentes *componentesID, ListaConexiones *conexionesID) {
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

    

    Rectangle btnPanel = {25, 115, 170, 45};
    Rectangle btnControlador = {25, 175, 170, 45};
    Rectangle btnBateria = {25, 235, 170, 45};
    Rectangle btnCarga = {25, 295, 170, 45};
    Rectangle btnConvertidor = {25, 355, 170, 45};
    ///////////////////////////////////
    Rectangle btnDibujar = {25, 415, 170, 45};

    if (LeftClick(btnDibujar)) {
        state->dibujando = !state->dibujando;

        if (state->dibujando) {
            printf("Dibujando activado\n");
            }
        else {
            state->arrastrando_linea = 0;
            state->desdeID = -1;
            printf("Dibujando desactivado\n");
        }
    }
    if (state->dibujando && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && !state->arrastrando_linea) {

        int id = ObtenerComponenteBajoMouse(componentesID);

        if (id != -1) {
            state->desdeID = id;
            state->arrastrando_linea = 1;
            printf("Inicio conexion desde %d\n", id);
    }
}

    if (state->dibujando && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && state->arrastrando_linea) {

        int id = ObtenerComponenteBajoMouse(componentesID);

        if (id != -1 && id != state->desdeID) {
            AgregarConexiones(conexionesID, state->desdeID, id);
            printf("Conexion creada: %d -> %d\n", state->desdeID, id);
            
        }
        state->arrastrando_linea = 0;
        state->desdeID = -1;
    }
    ////////////////////////////////////       
    if (LeftClick(btnPanel)) {
        AgregarComponentes(componentesID, panel_solar, mouse.x, mouse.y, 12, 0, 30, 0, 0, -1, -1);
    }

    if (LeftClick(btnControlador)) {
        AgregarComponentes(componentesID, controlador, mouse.x, mouse.y, 12, 0, 500, 0, 0, -1, -1);
    }

    if (LeftClick(btnBateria)) {
        AgregarComponentes(componentesID, bateria, mouse.x, mouse.y, 12, 0, 12*2.2, 2.2, 50, -1, -1);
    }

    if (LeftClick(btnCarga)) {
        AgregarComponentes(componentesID, carga, mouse.x, mouse.y, 0, 120, 60, 0, 0, -1, -1);
    }
    if (LeftClick(btnConvertidor)) {
        AgregarComponentes(componentesID, convertidor, mouse.x, mouse.y, 12, 120, 500, 0, 0, -1, -1);
    }
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        for (int i = componentesID->cuenta - 1; i >= 0; i--) {
            Componente *componente = &componentesID->componentes[i];
            Rectangle rect = Componente_Rect(componente);


            if (LeftClick(rect) && !state->dibujando) {
                //////////////////////////////////////
                state->componente_seleccionado = componente->id;
                state->arrastrando = 1;
                state->desplazamiento_x = mouse.x - componente->x;
                state->desplazamiento_y = mouse.y - componente->y;
            
                /////////////////////////////////////
                break;
            }
        }
    }

    if ((state->arrastrando) && IsMouseButtonDown(MOUSE_LEFT_BUTTON)&&!state->dibujando) {
        Componente *componente = Buscar_ComponenteID(componentesID, state->componente_seleccionado);
        if (componente != NULL) {
                    
            componente->x = mouse.x - state->desplazamiento_x;
            componente->y = mouse.y - state->desplazamiento_y;
            
            // limites de pantalla para que no se salga de la zona de trabajo
            if (componente->x < 220) {
                componente->x = 220;
            }
            if (componente->y < 0.0f) {
                componente->y = 0.0f;
            }
            if (componente->x > 805.0f-WIDTH+220.0f) {
                componente->x = 805.0f-WIDTH+220.0f;
            }
            if (componente->y > 700.0f-HEIGHT) {
                componente->y = 700.0f-HEIGHT;
            }
        }
    }

    if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
        state->arrastrando = 0;
    }

    if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)&&!state->dibujando) {
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



void I_Draw(const IState *state, const ListaComponentes *componentesID, const ListaConexiones *conexionesID) {
    if (state == NULL || componentesID == NULL) {
        return;
    }

    BeginDrawing();
    ClearBackground(RAYWHITE);

    DrawPanelComponentes();

   // DrawText("Simulador Interactivo de Microrred en C", 260, 25, 28, DARKBLUE);
    //DrawText("Sistema base: panel solar + controlador + bateria + carga", 260, 62, 18, DARKGRAY);
    if (state->dibujando) {
        DrawRectangleLinesEx((Rectangle){220, 0, 805, 700}, 4.0f, GRAY);
    } else {
        DrawRectangleLinesEx((Rectangle){220, 0, 805, 700}, 4.0f, LIGHTGRAY);
    }
    
    DrawText("Area de trabajo", 240, 30, 18, GRAY);

    // Agregar funcion para dibujar conexiones entre componentes

    for (int i = 0; i < componentesID->cuenta; i++) {
        //int componente_seleccionado = componentesID->componentes[i].id == state->componente_seleccionado;
        DrawComponente(&componentesID->componentes[i]);
    }
////////////////////////////////////
    DrawConexion(componentesID, conexionesID);
    if (state->arrastrando_linea && state->dibujando && state->desdeID != -1) {
        const Componente *origen = Buscar_ComponenteID(componentesID, state->desdeID);

        if (origen) {
            Vector2 a = Centro_Componente(origen);
            Vector2 mouse = GetMousePosition();

            DrawLineEx(a, mouse, 2.0f, RED); // preview
        }
    }

    //////////////////////////////////
    DrawBoton((Rectangle){1200-130-25, 50, 130, 50}, "Validar");
    DrawBoton((Rectangle){1200-130-25, 50*2, 130, 50}, "Simular");
    DrawBoton((Rectangle){1200-130-25, 50*3, 130, 50}, "Reiniciar");

    DrawRectangleRounded((Rectangle){1200-130-25, 50*4, 130, 500}, 0.12f, 8, LIGHTGRAY);
    DrawText("Resultado:", 1200-130, 50*4+5 + 25, 18, DARKBLUE);
    //Implementar pestaña de resultados de validacion y simulacion
    EndDrawing();
}




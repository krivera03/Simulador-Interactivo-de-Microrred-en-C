#include "componentes.h"
#include "interfaz.h"
#define WIDTH 100
#define HEIGHT 50


static Vector2 Centro_Componente(const Componente *commponente) {
    Vector2 centro;
    centro.x = componente->x + componente->WIDTH / 2.0f;
    centro.y = componente->y + componente->HEIGHT / 2.0f;
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

static Rectangle Componente_Rect(const Componente *componente) {
    Rectangle rect;
    rect.x = componente->x; 
    rect.y = componente->y;
    rect.width = componente->WIDTH;
    rect.height = componente->HEIGHT;
    
    return rect;
}

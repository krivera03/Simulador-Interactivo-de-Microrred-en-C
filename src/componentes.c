#include "componentes.h"
#include <stdio.h>

/* Iniciar la lista de componentes */
void Iniciar_ListaComponentes(ListaComponentes *lista)
{
    lista->cuenta = 0;
}

/* Agrega los componentes a la lista */
int AgregarComponentes(ListaComponentes *lista,
                       TipoComponente tipo,
                       float x,
                       float y,
                       float voltaje,
                       float potencia,
                       float capacidad_kWh,
                       float estado_carga)
{
    if (lista->cuenta >= MAX_COMPONENTES) {
        return -1;
    }

    Componente *nuevoComponente = &lista->componentes[lista->cuenta];

    nuevoComponente->id = lista->cuenta;
    nuevoComponente->tipo = tipo;
    nuevoComponente->x = x;
    nuevoComponente->y = y;
    nuevoComponente->voltaje = voltaje;
    nuevoComponente->potencia = potencia;
    nuevoComponente->capacidad_kWh = capacidad_kWh;
    nuevoComponente->estado_carga = estado_carga;

    lista->cuenta++;

    return nuevoComponente->id;
}

/* Buscar el componente por su id */
Componente *Buscar_ComponenteID(ListaComponentes *lista, int id)
{
    for (int i = 0; i < lista->cuenta; i++) {
        if (lista->componentes[i].id == id) {
            return &lista->componentes[i];
        }
    }

    return NULL;
}

/* Buscar el primer componente por tipo */
Componente *Buscar_ComponenteTipo(ListaComponentes *lista, TipoComponente tipo)
{
    for (int i = 0; i < lista->cuenta; i++) {
        if (lista->componentes[i].tipo == tipo) {
            return &lista->componentes[i];
        }
    }

    return NULL;
}

/* Obtener el nombre del componente */
const char *Buscar_ComponenteNombre(TipoComponente tipo)
{
    switch (tipo) {
        case panel_solar:
            return "Panel Solar";

        case bateria:
            return "Bateria";

        case carga:
            return "Carga";

        case controlador:
            return "Controlador";

        default:
            return "Desconocido";
    }
}

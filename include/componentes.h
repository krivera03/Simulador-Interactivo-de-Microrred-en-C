#ifndef COMPONENTES_H
#define COMPONENTES_H

#define MAX_COMPONENTES 20

/*Estructura que define los componentes a utilizar*/
typedef enum {
    panel_solar,
    bateria,
    carga,
    controlador,
    convertidor
}  TipoComponente;

/*Estructura que almacena toda la información necesaria de cada elemento*/
typedef struct 
{
    int id;
    TipoComponente tipo;
    float x;
    float y;
    float voltajeDC;
    float voltajeAC;
    float potencia;
    float capacidad_Ah;
    float estado_carga;
    float terminal_izquierda_id;
    float terminal_derecha_id;
} Componente;

/*Lista para almacenar componentes*/
typedef struct 
{
    Componente componentes[MAX_COMPONENTES];
    int cuenta;
} ListaComponentes;

/*Iniciar la lista de componentes*/
void Iniciar_ListaComponentes(ListaComponentes *lista);

/*Agrega los componentes a la lista*/
int AgregarComponentes(ListaComponentes *lista, TipoComponente tipo, float x, float y, float voltajeDC, float voltajeAC, float potencia, float capacidad_Ah,
                        float estado_carga, float terminal_izquierda_id, float terminal_derecha_id);

/*Buscar el componente por su id*/
Componente *Buscar_ComponenteID(ListaComponentes *lista, int id) ;

/*Obtener el nombre del componente*/
const char *Buscar_ComponenteNombre(TipoComponente tipo);

#endif



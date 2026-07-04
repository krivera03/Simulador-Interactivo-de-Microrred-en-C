#ifndef COMPONENTES_H
#define COMPONENTES_H

#define MAX_COMPONENTES 20

/*Estructura que define los componentes a utilizar*/
typedef enum {
    panel_solar,
    bateria,
    carga,
    controlador
}  TipoComponente;

/*Estructura que almacena toda la información necesaria de cada elemento*/
typedef struct 
{
    int id;
    TipoComponente tipo;
    float x;
    float y;
    float voltaje;
    float potencia;
    float capacidad_kWh;
    float estado_carga
} Componente;

/*Lista para almacenar componentes*/
typedef struct 
{
    Componente componentes[MAX_COMPONENTES];
    int cuenta;
} ListaComponetes;

#endif



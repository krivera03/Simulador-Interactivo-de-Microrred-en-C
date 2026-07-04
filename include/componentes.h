/*Estructura que define los componentes a utilizar*/
typedef enum {
    panel_solar,
    bateria,
    carga,
    controlador
}  TipoComponente;

/*Estructura que almacena toda la informacíon necesaria de cada elemento*/
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
    Componente componentes[20];
    int cuenta;
} ListaComponentes;





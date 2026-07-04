#ifndef CONEXIONES_H
#define CONEXIONES_H

/*Cantidad máxima de conexiones que puede realizar la microrred*/
#define MAX_CONEXIONES 30

/*Representación de la conexión entre dos componentes*/
typedef struct 
{
    int origenID;    
    int destinoID;
} Conexion;

/*Lista de conexiones*/
typedef struct 
{
    Conexion conexiones[MAX_CONEXIONES];
    int cuenta;
} ListaConexiones;

/*Iniciar la lista de conexiones*/
void Iniciar_ListaConexiones(ListaConexiones *lista);

/*Agregar nuevas conexcines*/
int AgregarConexiones(ListaConexiones *lista, int origenID, int destinoID);

/*Verificar si existen las conexiones*/
int ExisteConexion(ListaConexiones *lista, int origenID, int destinoID);

#endif


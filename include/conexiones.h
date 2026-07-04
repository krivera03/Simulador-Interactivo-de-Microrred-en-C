#ifndef CONEXIONES_H
#define CONEXIONES_H

#define MAX_CONEXIONES 30

/* Representacion de la conexion entre dos componentes */
typedef struct {
    int origenID;
    int destinoID;
} Conexion;

/* Lista de conexiones */
typedef struct {
    Conexion conexiones[MAX_CONEXIONES];
    int cuenta;
} ListaConexiones;

/* Iniciar la lista de conexiones */
void Iniciar_ListaConexiones(ListaConexiones *lista);

/* Agregar nueva conexion */
int AgregarConexiones(ListaConexiones *lista, int origenID, int destinoID);

/* Verificar si existe la conexion directa */
int ExisteConexion(ListaConexiones *lista, int origenID, int destinoID);

/* Verificar conexion sin importar el sentido */
int ExisteConexionBidireccional(ListaConexiones *lista, int idA, int idB);

#endif

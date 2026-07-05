#include "conexiones.h"

/*
Iniciar la lista de conexiones:
Cuando se inicia el programa no hay conexiones exitentes.
*/

void Iniciar_ListaConexiones(ListaConexiones *lista)
{
    lista->cuenta = 0;   /*Cantidad de conexines igual a cero*/
}

/*
Agregar una conexión entre dos componentes
*/

int AgregarConexiones(ListaConexiones *lista, int origenID, int destinoID)
{
    if (lista->cuenta >= MAX_CONEXIONES){    /*Verifica si hay espacio para nuevas conexiones*/
        return 0;
    }

    /*Guarda las conexiones en la posición disponible*/
    lista->conexiones[lista->cuenta].origenID = origenID;
    lista->conexiones[lista->cuenta].destinoID = destinoID;   
    
    lista->cuenta++; /*Incrementa el contador*/

    return 1;
}

/*Verificar si existen las conexiones*/
int ExisteConexion(ListaConexiones *lista, int origenID, int destinoID)
{
    for (int i = 0; i < lista->cuenta; i++)   /*Ciclo que recorre la lista de conexiones*/
    {
        if (lista->conexiones[i].origenID == origenID &&
            lista->conexiones[i].destinoID == destinoID)     /*Verifica si la conexión existe*/
            {
                return 1;
            }
    }
    
    return 0;
}

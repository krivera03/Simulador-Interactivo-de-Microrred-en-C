#include "conexiones.h"

void Iniciar_ListaConexiones(ListaConexiones *lista)
{
    lista->cuenta = 0;
}

int AgregarConexiones(ListaConexiones *lista, int origenID, int destinoID)
{
    if (lista->cuenta >= MAX_CONEXIONES) {
        return 0;
    }

    lista->conexiones[lista->cuenta].origenID = origenID;
    lista->conexiones[lista->cuenta].destinoID = destinoID;

    lista->cuenta++;

    return 1;
}

int ExisteConexion(ListaConexiones *lista, int origenID, int destinoID)
{
    for (int i = 0; i < lista->cuenta; i++) {
        if (lista->conexiones[i].origenID == origenID &&
            lista->conexiones[i].destinoID == destinoID) {
            return 1;
        }
    }

    return 0;
}

int ExisteConexionBidireccional(ListaConexiones *lista, int idA, int idB)
{
    return ExisteConexion(lista, idA, idB) ||
           ExisteConexion(lista, idB, idA);
}

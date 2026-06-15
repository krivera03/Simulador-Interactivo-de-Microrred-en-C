#include "validation.h"

#include <stdio.h>

/*
 * Funcion: ValidateMicrogrid
 * --------------------------
 * Realiza una primera revision logica de la microrred.
 *
 * En este avance inicial se verifica que:
 *  - La lista de componentes exista.
 *  - La lista de conexiones exista.
 *  - La microrred tenga panel solar.
 *  - La microrred tenga controlador.
 *  - La microrred tenga bateria.
 *  - La microrred tenga carga.
 *
 * Esta funcion se puede ampliar posteriormente para revisar:
 *  - Compatibilidad de tensiones.
 *  - Capacidad de potencia.
 *  - Continuidad electrica entre componentes.
 *  - Conexiones correctas entre panel, controlador, bateria y carga.
 */
ValidationResult ValidateMicrogrid(const ComponentList *components,
                                   const ConnectionList *connections)
{
    ValidationResult result;

    result.is_valid = 0;
    snprintf(result.message,
             VALIDATION_MESSAGE_SIZE,
             "La microrred aun no ha sido validada.");

    if (components == NULL) {
        snprintf(result.message,
                 VALIDATION_MESSAGE_SIZE,
                 "Error: la lista de componentes no existe.");
        return result;
    }

    if (connections == NULL) {
        snprintf(result.message,
                 VALIDATION_MESSAGE_SIZE,
                 "Error: la lista de conexiones no existe.");
        return result;
    }

    const Component *solar =
        ComponentList_FindFirstByTypeConst(components, COMPONENT_SOLAR);

    const Component *controller =
        ComponentList_FindFirstByTypeConst(components, COMPONENT_CONTROLLER);

    const Component *battery =
        ComponentList_FindFirstByTypeConst(components, COMPONENT_BATTERY);

    const Component *load =
        ComponentList_FindFirstByTypeConst(components, COMPONENT_LOAD);

    if (solar == NULL) {
        snprintf(result.message,
                 VALIDATION_MESSAGE_SIZE,
                 "Error: falta el panel solar en la microrred.");
        return result;
    }

    if (controller == NULL) {
        snprintf(result.message,
                 VALIDATION_MESSAGE_SIZE,
                 "Error: falta el controlador en la microrred.");
        return result;
    }

    if (battery == NULL) {
        snprintf(result.message,
                 VALIDATION_MESSAGE_SIZE,
                 "Error: falta la bateria en la microrred.");
        return result;
    }

    if (load == NULL) {
        snprintf(result.message,
                 VALIDATION_MESSAGE_SIZE,
                 "Error: falta la carga en la microrred.");
        return result;
    }

    result.is_valid = 1;
    snprintf(result.message,
             VALIDATION_MESSAGE_SIZE,
             "Sistema valido: la microrred contiene panel solar, controlador, bateria y carga.");

    return result;
}

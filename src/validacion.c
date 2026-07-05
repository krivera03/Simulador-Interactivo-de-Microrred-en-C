#include "validacion.h"

#include <math.h>
#include <stdio.h>

static int TensionesCompatibles(float v1, float v2)
{
    float diferencia;
    float referencia;

    if (v1 <= 0.0f || v2 <= 0.0f) {
        return 0;
    }

    diferencia = fabsf(v1 - v2);
    referencia = fmaxf(v1, v2);

    return (diferencia / referencia) <= 0.05f;
}

static Componente *BuscarComponentePorTipo(ListaComponentes *componentes,
                                           TipoComponente tipo)
{
    for (int i = 0; i < componentes->cuenta; i++) {
        if (componentes->componentes[i].tipo == tipo) {
            return &componentes->componentes[i];
        }
    }

    return 0;
}

static int ExisteConexionEntre(ListaConexiones *conexiones, int idA, int idB)
{
    return ExisteConexion(conexiones, idA, idB) ||
           ExisteConexion(conexiones, idB, idA);
}

ResultadoValidacion ValidarMicrorred(ListaComponentes *componentes,
                                     ListaConexiones *conexiones)
{
    ResultadoValidacion resultado;

    resultado.valido = 0;
    snprintf(resultado.mensaje,
             TAMANO_MENSAJE_VALIDACION,
             "La microrred todavia no ha sido validada.");

    if (componentes == 0) {
        snprintf(resultado.mensaje,
                 TAMANO_MENSAJE_VALIDACION,
                 "Error: la lista de componentes no existe.");
        return resultado;
    }

    if (conexiones == 0) {
        snprintf(resultado.mensaje,
                 TAMANO_MENSAJE_VALIDACION,
                 "Error: la lista de conexiones no existe.");
        return resultado;
    }

    Componente *solar = BuscarComponentePorTipo(componentes, panel_solar);
    Componente *bat = BuscarComponentePorTipo(componentes, bateria);
    Componente *load = BuscarComponentePorTipo(componentes, carga);
    Componente *ctrl = BuscarComponentePorTipo(componentes, controlador);

    if (solar == 0) {
        snprintf(resultado.mensaje,
                 TAMANO_MENSAJE_VALIDACION,
                 "Error: falta el panel solar.");
        return resultado;
    }

    if (ctrl == 0) {
        snprintf(resultado.mensaje,
                 TAMANO_MENSAJE_VALIDACION,
                 "Error: falta el controlador.");
        return resultado;
    }

    if (bat == 0) {
        snprintf(resultado.mensaje,
                 TAMANO_MENSAJE_VALIDACION,
                 "Error: falta la bateria.");
        return resultado;
    }

    if (load == 0) {
        snprintf(resultado.mensaje,
                 TAMANO_MENSAJE_VALIDACION,
                 "Error: falta la carga.");
        return resultado;
    }

    if (!ExisteConexionEntre(conexiones, solar->id, ctrl->id)) {
        snprintf(resultado.mensaje,
                 TAMANO_MENSAJE_VALIDACION,
                 "Error: el panel solar debe estar conectado al controlador.");
        return resultado;
    }

    if (!ExisteConexionEntre(conexiones, ctrl->id, bat->id)) {
        snprintf(resultado.mensaje,
                 TAMANO_MENSAJE_VALIDACION,
                 "Error: la bateria debe estar conectada al controlador.");
        return resultado;
    }

    if (!ExisteConexionEntre(conexiones, ctrl->id, load->id)) {
        snprintf(resultado.mensaje,
                 TAMANO_MENSAJE_VALIDACION,
                 "Error: la carga debe estar conectada al controlador.");
        return resultado;
    }

    if (!TensionesCompatibles(solar->voltajeDC, ctrl->voltajeDC)) {
        snprintf(resultado.mensaje,
                 TAMANO_MENSAJE_VALIDACION,
                 "Error: la tension DC del panel solar no es compatible con el controlador.");
        return resultado;
    }

    if (!TensionesCompatibles(bat->voltajeDC, ctrl->voltajeDC)) {
        snprintf(resultado.mensaje,
                 TAMANO_MENSAJE_VALIDACION,
                 "Error: la tension DC de la bateria no es compatible con el controlador.");
        return resultado;
    }

    if (!TensionesCompatibles(load->voltajeDC, ctrl->voltajeDC)) {
        snprintf(resultado.mensaje,
                 TAMANO_MENSAJE_VALIDACION,
                 "Error: la tension DC de la carga no es compatible con el controlador.");
        return resultado;
    }

    if (ctrl->potencia < load->potencia) {
        snprintf(resultado.mensaje,
                 TAMANO_MENSAJE_VALIDACION,
                 "Error: el controlador no tiene capacidad suficiente para alimentar la carga.");
        return resultado;
    }

    resultado.valido = 1;
    snprintf(resultado.mensaje,
             TAMANO_MENSAJE_VALIDACION,
             "Sistema valido: componentes, conexiones, tension DC y potencia compatibles.");

    return resultado;
}

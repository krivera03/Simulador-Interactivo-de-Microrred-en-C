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

    Componente *solar = Buscar_ComponenteTipo(componentes, panel_solar);
    Componente *bat = Buscar_ComponenteTipo(componentes, bateria);
    Componente *load = Buscar_ComponenteTipo(componentes, carga);
    Componente *ctrl = Buscar_ComponenteTipo(componentes, controlador);

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

    if (!ExisteConexionBidireccional(conexiones, solar->id, ctrl->id)) {
        snprintf(resultado.mensaje,
                 TAMANO_MENSAJE_VALIDACION,
                 "Error: el panel solar debe estar conectado al controlador.");
        return resultado;
    }

    if (!ExisteConexionBidireccional(conexiones, ctrl->id, bat->id)) {
        snprintf(resultado.mensaje,
                 TAMANO_MENSAJE_VALIDACION,
                 "Error: la bateria debe estar conectada al controlador.");
        return resultado;
    }

    if (!ExisteConexionBidireccional(conexiones, ctrl->id, load->id)) {
        snprintf(resultado.mensaje,
                 TAMANO_MENSAJE_VALIDACION,
                 "Error: la carga debe estar conectada al controlador.");
        return resultado;
    }

    if (!TensionesCompatibles(solar->voltaje, ctrl->voltaje)) {
        snprintf(resultado.mensaje,
                 TAMANO_MENSAJE_VALIDACION,
                 "Error: la tension del panel solar no es compatible con el controlador.");
        return resultado;
    }

    if (!TensionesCompatibles(bat->voltaje, ctrl->voltaje)) {
        snprintf(resultado.mensaje,
                 TAMANO_MENSAJE_VALIDACION,
                 "Error: la tension de la bateria no es compatible con el controlador.");
        return resultado;
    }

    if (!TensionesCompatibles(load->voltaje, ctrl->voltaje)) {
        snprintf(resultado.mensaje,
                 TAMANO_MENSAJE_VALIDACION,
                 "Error: la tension de la carga no es compatible con el controlador.");
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
             "Sistema valido: componentes, conexiones, tension y potencia compatibles.");

    return resultado;
}

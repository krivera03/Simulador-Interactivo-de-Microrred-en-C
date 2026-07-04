#include "simulacion.h"
#include "validacion.h"

#include <stdio.h>

static float LimitarValor(float valor, float minimo, float maximo)
{
    if (valor < minimo) {
        return minimo;
    }

    if (valor > maximo) {
        return maximo;
    }

    return valor;
}

ResultadoSimulacion SimularFlujoPotencia(ListaComponentes *componentes,
                                         ListaConexiones *conexiones)
{
    ResultadoSimulacion resultado;

    resultado.exitosa = 0;
    resultado.potencia_solar_W = 0.0f;
    resultado.potencia_carga_W = 0.0f;
    resultado.potencia_bateria_W = 0.0f;
    resultado.excedente_W = 0.0f;
    resultado.deficit_W = 0.0f;
    resultado.estado_carga_inicial = 0.0f;
    resultado.estado_carga_final = 0.0f;

    snprintf(resultado.mensaje,
             TAMANO_MENSAJE_SIMULACION,
             "La simulacion todavia no ha sido ejecutada.");

    ResultadoValidacion validacion = ValidarMicrorred(componentes, conexiones);

    if (!validacion.valido) {
        snprintf(resultado.mensaje,
                 TAMANO_MENSAJE_SIMULACION,
                 "No se puede simular. %s",
                 validacion.mensaje);
        return resultado;
    }

    Componente *solar = Buscar_ComponenteTipo(componentes, panel_solar);
    Componente *bat = Buscar_ComponenteTipo(componentes, bateria);
    Componente *load = Buscar_ComponenteTipo(componentes, carga);

    if (solar == 0 || bat == 0 || load == 0) {
        snprintf(resultado.mensaje,
                 TAMANO_MENSAJE_SIMULACION,
                 "Error interno: faltan componentes para simular.");
        return resultado;
    }

    /*
     * Para este modelo basico se simula un periodo de una hora.
     * Esto permite relacionar potencia en W con energia en Wh.
     */
    float tiempo_horas = 1.0f;

    resultado.potencia_solar_W = solar->potencia;
    resultado.potencia_carga_W = load->potencia;
    resultado.estado_carga_inicial = bat->estado_carga;
    resultado.estado_carga_final = bat->estado_carga;

    if (bat->capacidad_kWh <= 0.0f) {
        snprintf(resultado.mensaje,
                 TAMANO_MENSAJE_SIMULACION,
                 "Error: la bateria no tiene una capacidad valida.");
        return resultado;
    }

    /*
     * Caso 1:
     * La potencia del panel solar es suficiente para alimentar la carga.
     * El excedente se usa para cargar la bateria.
     */
    if (resultado.potencia_solar_W >= resultado.potencia_carga_W) {
        resultado.excedente_W = resultado.potencia_solar_W - resultado.potencia_carga_W;
        resultado.potencia_bateria_W = -resultado.excedente_W;

        float energia_excedente_Wh = resultado.excedente_W * tiempo_horas;
        float porcentaje_carga = (energia_excedente_Wh / (bat->capacidad_kWh * 1000.0f)) * 100.0f;

        resultado.estado_carga_final =
            LimitarValor(resultado.estado_carga_inicial + porcentaje_carga, 0.0f, 100.0f);

        bat->estado_carga = resultado.estado_carga_final;

        resultado.exitosa = 1;

        snprintf(resultado.mensaje,
                 TAMANO_MENSAJE_SIMULACION,
                 "Simulacion exitosa: el panel alimenta la carga. Excedente: %.2f W. La bateria se carga de %.2f%% a %.2f%%.",
                 resultado.excedente_W,
                 resultado.estado_carga_inicial,
                 resultado.estado_carga_final);

        return resultado;
    }

    /*
     * Caso 2:
     * La potencia solar no alcanza.
     * La bateria debe entregar la diferencia.
     */
    float potencia_requerida_bateria =
        resultado.potencia_carga_W - resultado.potencia_solar_W;

    float energia_requerida_Wh = potencia_requerida_bateria * tiempo_horas;
    float energia_disponible_bateria_Wh =
        bat->capacidad_kWh * 1000.0f * (bat->estado_carga / 100.0f);

    if (energia_disponible_bateria_Wh >= energia_requerida_Wh) {
        resultado.potencia_bateria_W = potencia_requerida_bateria;
        resultado.deficit_W = 0.0f;

        float porcentaje_descarga =
            (energia_requerida_Wh / (bat->capacidad_kWh * 1000.0f)) * 100.0f;

        resultado.estado_carga_final =
            LimitarValor(resultado.estado_carga_inicial - porcentaje_descarga, 0.0f, 100.0f);

        bat->estado_carga = resultado.estado_carga_final;

        resultado.exitosa = 1;

        snprintf(resultado.mensaje,
                 TAMANO_MENSAJE_SIMULACION,
                 "Simulacion exitosa: el panel no alcanza y la bateria entrega %.2f W. Estado de carga: %.2f%% a %.2f%%.",
                 resultado.potencia_bateria_W,
                 resultado.estado_carga_inicial,
                 resultado.estado_carga_final);

        return resultado;
    }

    /*
     * Caso 3:
     * Ni el panel ni la bateria pueden alimentar completamente la carga.
     */
    resultado.potencia_bateria_W = energia_disponible_bateria_Wh / tiempo_horas;
    resultado.deficit_W = potencia_requerida_bateria - resultado.potencia_bateria_W;
    resultado.estado_carga_final = 0.0f;

    bat->estado_carga = resultado.estado_carga_final;

    resultado.exitosa = 0;

    snprintf(resultado.mensaje,
             TAMANO_MENSAJE_SIMULACION,
             "Simulacion no exitosa: existe un deficit de %.2f W. La bateria no tiene energia suficiente.",
             resultado.deficit_W);

    return resultado;
}

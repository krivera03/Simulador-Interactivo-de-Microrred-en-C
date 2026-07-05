#include "componentes.h"
#include "conexiones.h"
#include "validacion.h"
#include "simulacion.h"

#include <stdio.h>

int main(void)
{
    ListaComponentes componentes;
    ListaConexiones conexiones;

    Iniciar_ListaComponentes(&componentes);
    Iniciar_ListaConexiones(&conexiones);

    int idSolar = AgregarComponentes(&componentes, panel_solar,
                                     100.0f, 100.0f,
                                     48.0f, 0.0f,
                                     800.0f,
                                     0.0f,
                                     0.0f,
                                     -1.0f, -1.0f);

    int idControlador = AgregarComponentes(&componentes, controlador,
                                           300.0f, 100.0f,
                                           48.0f, 0.0f,
                                           1500.0f,
                                           0.0f,
                                           0.0f,
                                           -1.0f, -1.0f);

    int idBateria = AgregarComponentes(&componentes, bateria,
                                       300.0f, 250.0f,
                                       48.0f, 0.0f,
                                       1000.0f,
                                       100.0f,
                                       80.0f,
                                       -1.0f, -1.0f);

    int idCarga = AgregarComponentes(&componentes, carga,
                                     500.0f, 100.0f,
                                     48.0f, 0.0f,
                                     1000.0f,
                                     0.0f,
                                     0.0f,
                                     -1.0f, -1.0f);

    AgregarConexiones(&conexiones, idSolar, idControlador);
    AgregarConexiones(&conexiones, idControlador, idBateria);
    AgregarConexiones(&conexiones, idControlador, idCarga);

    ResultadoValidacion validacion = ValidarMicrorred(&componentes, &conexiones);

    printf("Resultado de validacion:\n");
    printf("%s\n\n", validacion.mensaje);

    ResultadoSimulacion simulacion = SimularFlujoPotencia(&componentes, &conexiones);

    printf("Resultado de simulacion:\n");
    printf("%s\n\n", simulacion.mensaje);

    printf("Potencia solar: %.2f W\n", simulacion.potencia_solar_W);
    printf("Potencia carga: %.2f W\n", simulacion.potencia_carga_W);
    printf("Potencia bateria: %.2f W\n", simulacion.potencia_bateria_W);
    printf("Deficit: %.2f W\n", simulacion.deficit_W);
    printf("Excedente: %.2f W\n", simulacion.excedente_W);
    printf("Estado de carga inicial: %.2f %%\n", simulacion.estado_carga_inicial);
    printf("Estado de carga final: %.2f %%\n", simulacion.estado_carga_final);

    return 0;
}

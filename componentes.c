
/*Iniciar la lista de componentes*/
void Iniciar_ListaComponentes(ListaComponentes *lista) {
    lista->cuenta = 0;
}

/*Agrega los componentes a la lista*/
int AgregarComponentes(ListaComponentes *lista, TipoComponente tipo, float x, float y, float voltaje, float potencia, float capacidad_kWh,
                        float estado_carga) 
{
    if (lista->cuenta >= MAX_COMPONENTES)
        return -1;
    
    Componente *nuevoComponente = &lista->componentes[lista->cuenta];

    nuevoComponente->id = lista->cuenta;
    nuevoComponente->tipo = tipo;
    nuevoComponente->x = x;
    nuevoComponente->y = y;
    nuevoComponente->voltaje = voltaje;
    nuevoComponente->potencia = potencia;
    nuevoComponente->capacidad_kWh = capacidad_kWh;
    nuevoComponente->estado_carga = estado_carga;

    lista->cuenta++;

    return nuevoComponente->id;
}
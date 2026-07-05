# Simulador Interactivo de Microrred en C

## Descripción del contenido del repositorio

Una microrred es una red eléctrica pequeña que genera y distribuye energía a una zona específica, como una comunidad o un edicio Puede operar conectada a la red principal o de forma independiente, utilizando fuentes como paneles solares y baterías.

El presente proyecto consiste en desarrollar una aplicación interactiva en lenguaje C que permita simular la construcción de una microrred eléctrica aislada mediante una interfaz. El usuario podrá seleccionar y conectar diferentes componentes eléctricos, mientra el sistema verifica si la configuración realizada es válida según criterios básicos de funcionamiento de una microrred. 

## Archivos principales

- **main.c**: Contiene la función principal del programa y el menú de interacción.
- **componentes.c / componentes.h**: Definición de las estructuras de los componentes y generación de la lista de componentes.
- **Makefile**: Archivo que realiza la compilación del proyecto.
- **README.md**: Documentación del proyecto.


## Dependencias e Instalación


## Pasos para compilar

1. Abrir una terminal.
2. Ubicarse en la carpeta del proyecto:

```bash
cd ruta/al/proyecto
```

3. Ejecutar el siguiente comando:

```bash
make run
```

Si la compilación es exitosa, se generará el archivo ejecutable del programa.

4. Para revisión de fugas de memoria ejecutar:
```bash
make valgrind
```

## Pasos para ejecutar

Una vez compilado el proyecto, ejecutar:

```bash
./microrred
```


## Limpieza de archivos compilados

Para eliminar los archivos objeto y el ejecutable generado:

```bash
make clean
```

## Requisitos

- Compilador GCC.
- Utilidad `make`.
- Sistema operativo Linux, macOS o Windows con MinGW/MSYS2 o WSL.

## Autores

- Karen Rivera Angulo 
- Ismael Alvarado Perez
- Jean Carlo Chinchilla Mora



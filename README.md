# Simulador Interactivo de Microrred en C

## Descripción del contenido del repositorio

Una microrred es una red eléctrica pequeña que genera y distribuye energía a una zona específica, como una comunidad o un edicio Puede operar conectada a la red principal o de forma independiente, utilizando fuentes como paneles solares y baterías.

El presente proyecto consiste en desarrollar una aplicación interactiva en lenguaje C que permita simular la construcción de una microrred eléctrica aislada mediante una interfaz. El usuario podrá seleccionar y conectar diferentes componentes eléctricos, mientra el sistema verifica si la configuración realizada es válida según criterios básicos de funcionamiento de una microrred. 


## Dependencias e Instalación
Antes de compilar el proyecto, asegurese de tener instaladas las siguientes dependencias:

- Compilador GCC.
- Raylib (version 6.1 o superior).
- Utilidad `make`.
- Sistema operativo Linux, macOS o Windows con MinGW/MSYS2 o WSL.

## Instalación de Raylib

### Ubuntu/Debian

1. Abrir una terminal.
2. Instalar herramientas requeridas:

```bash
sudo apt install build-essential git
```
3. Instalar librerías:

```bash
sudo apt install libasound2-dev libx11-dev libxrandr-dev libxi-dev libgl1-mesa-dev libglu1-mesa-dev libxcursor-dev libxinerama-dev libwayland-dev libxkbcommon-dev
```

### Windows con MinGW/W64/GCC

1. Abrir en enlace: https://github.com/skeeto/w64devkit/
2. Descargar el archivo w64devkit.zip.
3. Descomprimir el archivo.
4. Correr el archivo W64Devkit.exe

### macOS

1. Tener una Mac con OSX version 10.11.3.
2. Instalar *Apple Developer Tools*.
3. Instalar raylib library.

Para más información sobre la instalación de Raylib, consultar la información oficial.
- [Documentación Raylib](https://www.raylib.com/)
- [Instalación GNU Linux](https://github.com/raysan5/raylib/wiki/Working-on-GNU-Linux)
- [Instalación GNU Windows](https://github.com/raysan5/raylib/wiki/Working-on-Windows)
- [Instalación GNU macOS](https://github.com/raysan5/raylib/wiki/Working-on-macOS)

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


## Autores

- Karen Rivera Angulo 
- Ismael Alvarado Perez
- Jean Carlo Chinchilla Mora



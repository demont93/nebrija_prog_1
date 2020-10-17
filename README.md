# Ejercicios Programación1
Universidad Antonio de Nebrija.

El propósito inicial de este proyecto, además de servir de práctica, era ser una referencia para otros estudiantes. ~~Para este último propósito, he colocado comentarios descriptivos de la sintaxis que no estarían de otra forma en el código fuente.~~ Sin embargo, el proposito del proyecto ha cambiado a ser unicamente producir codigo eficiente y rapido con sintaxis moderna de C++ con el unico objetivo de aprender nuevas construcciones. Es posible que muchos problemas sufran de pre-optimizaciones, dicho esto, todas las sugerencias son bien recibidas.

## Roadmap
- [x] Unificar I/O en todos los ejercicios.
- [x] Terminar Lista 1 de ejercicios.
- [ ] Terminar Lista 2 de ejercicios.
- [ ] Terminar Lista 3 de ejercicios.
- [x] Agregar comentarios de cabecera en todos los archivos.
- [ ] Agregar los tests a un sistema automatizado.
- [ ] Incorporar benchmarks y profiling.

## Como Ejecutar Los Ejercicios
Estos son los pasos básicos para ejecutar los ejercicios:

1. Crear un directorio donde compilar el programa. Ejemplo Linux:
    ```bash
    mkdir build
    cd build/
    ```
2. Debes compilar el programa utilizando [__cmake__](https://cmake.org). Ejemplo Linux:
    ```bash
    cmake /path-to/source-dir/ # configure
    cmake --build . # Compila todos los ejercicios
    # puedes usar --target ejercicioXX para compilar uno especifico
    ```
3. Entra en el directorio bin/ y ejecuta el archivo. Ejemplo linux:
    ```bash
    bin/ejercicio30
    ```
> Nota: El build esta en modo DEBUG para poder correrlo desde entornos de Windows sin que se cierre la ventana. Si el programa no se comporta como esperarías en tu entorno o tu sistema operativo abre un ticket o envíame un correo electrónico a dmontesdeocab@alumnos.nebrija.es

### Para Los Maestros
Por cualquiera de las siguientes razones:

* Algún error en alguno de los ejercicios.
* Una mejor forma de escribir un algoritmo.
* Sugerencia de estilo.
* Traducción a otro idioma.
* Sugerencia para mejorar o expandir el proyecto.

Me pueden contactar a mi correo de la Universidad: dmontesdeocab@alumnos.nebrija.es

~~### Para Los Estudiantes~~
~~Si quieres colaborar, basta con hacer un fork, un nuevo branch y un pull request. Este proyecto esta mas que abierto para colaboración y sugerencias. Si encuentras un error también puedes abrir un issue en la pagina de GitHub: https://github.com/demont93/nebrija_prog_1~~

Gracias.

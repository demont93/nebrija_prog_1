# Ejercicios Programacion1
Universidad Antonio de Nebrija.

El proposito inicial de este proyecto, ademas de servir de practica, era ser una referencia para otros
estudiantes. Para este proposito, he colocado comentarios descriptivos de la sintaxis que no estarian de otra forma
en el codigo fuente. 

## Como Ejecutar Los Ejercicios
Estos son los pasos basicos para ejecutar los ejercicios:

1. Crear un directorio donde compilar el programa. Ejemplo linux:
    ```bash
    mkdir build
    cd build/
    ```
2. Debes compilar el programa utilizando __[cmake]__(cmake.org). Ejemplo linux:
    ```bash
    cmake /path-to/source-dir/ # configure
    cmake --build . # Compila todos los ejercicios, puedes usar --target ejercicio## para compilar uno especifico
    ```
3. Entra en el directorio bin/ y ejecuta el archivo. Ejemplo linux:
    ```bash
    bin/ejercicio30
    ```
> Nota: El build esta en modo DEBUG para poder correrlo desde entornos de windows sin que se cierre la ventana.
>       Si el programa no se comporta como esperarias en tu entorno o tu sistema operativo abre un ticket o enviame
>       un correo electronico a dmontesdeocab@alumnos.nebrija.es

### Para Los Maestros
Por cualquiera de las siguientes razones:

* Algun error en alguno de los ejercicios.
* Una mejor forma de escribir un algoritmo.
* Sugerencia de estilo.
* Traduccion a otro idioma.
* Sugerencia para mejorar o expandir el proyecto.
* Simplificar el codigo.

Me pueden contactar a mi correo de la Universidad: dmontesdeocab@alumnos.nebrija.es

### Para Los Estudiantes
Si quieres colaborar, basta con hacer un fork, un nuevo branch y un pull request. Este proyecto esta mas que abierto
para colaboracion y sugerencias.

Si encuentras un error tambien puedes abrir un issue en la pagina de github: https://github.com/demont93/nebrija_prog_1

Gracias.
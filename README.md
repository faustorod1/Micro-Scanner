# ***SSL Micro Scanner***

Scanner para el lenguaje Micro como está definido en el libro del profesor Muchnik de Sintaxis y Semántica de los Lenguajes

## **Integrantes del grupo**

- Brian Franco Chino Yanarico
- Maximiliano Dante Cimorelli
- Luca Domio
- Ignacio NicolÁs Lapko
- Romina Fabiana Manzaneda Irusta
- JoaquÍn Pella
- Sergio Rodrigo Ramos Quispe
- Fausto Andres RodrÍguez
- Facundo Vilamowski
- Demian Burna

## **Instrucciones para compilar**

1. Descargar Visual Studio Code con MinGW [Link](https://code.visualstudio.com/docs/cpp/config-mingw)
2. Descargar Make [Link](https://gnuwin32.sourceforge.net/packages/make.htm)
3. Una vez instalado, abrir un terminal de windows o dentro de visual y situarse en el directorio de scanner del repositorio.
4. Correr el comando *make all* por consola
- **el programa mcc.exe habra sido compilado**

## **Instrucciones para probar**

### Para probar el programa se puede utilizar make a partir del test programado.

1. Situarse en el directorio de scanner del repositorio
2. Ejecutar el comando *make test1* **(sin errores)** y *make test2* **(con errores)**
- **el programa mcc.exe ejecutara un secuencia de sentencias en cada comando, con y sin errores lexicos, para probar el scanner**

## Diagrama de transición

![tabla de transicion](<TABLA DE TRANSICION.png>)

## **Qué cambios hicimos y por qué**

- Completar y arreglo funcion transicion:

    Se requeria una estructura de datos para permitir la conversion de estados que hace la funcion transicion, 
    se opto por la matriz bidimensional por la simplesa de su uso, luego mediante el uso de la funcion obtenerColumna y la nueva matriz se
    pudo obtener la logica para hacer posible la transicion.
    Tambien se cambio el retorno de la funcion que devolvia una matriz y tiene que devolver un estado que es del tipo int.

- Implementacion de Enum:

    la implementación de un enum para los tokens ayuda a estructurar mejor el código, 
    haciendo que sea más intuitivo, fácil de mantener y menos propenso a errores, especialmente en un proyecto 
    donde la legibilidad es fundamental para un análisis léxico preciso.

- Implementacion de una archivo unificado:

    La implementación de un archivo unificado para el código en esta fase del proyecto 
    permite realizar pruebas de compilación y ejecución de forma más sencilla, ágil y controlada.

- Implementacion de la funcion `EsReservada()` :

    Se completa la funcion `EsReservada()`, que sera llamada cuando la funcion `Scanner()` haya encontrado caracteres que sean simbolos `isalpha(simbolo)` (es decir, letras), al menos un espacio y cualquier otro caracter (caracter centinela). Una vez recibido el lexema (contenido en `Buffer()`) iteraremos la cantidad de palabras reservadas (4) y en cada iteracion se compararpa dicho lexema con la palabra reservada en cuestion. 
    Frente a una coincidencia, se devolverá el token correspondiente (INICIO, FIN, LEER, ESCRIBIR). Si no coincide, estaremos frente a una nueva variable y la funcion devolvera que dicho lexema es un token de tipo ID. 

    Implementamos esta solucion ya que proporciona un código más modular y legible, aumentando la precisión del análisis léxico al diferenciar un identificador de las palabras reservadas.

- Implementacion de `#define CANT_PALABRAS_RESERVADAS 4`:
  
    Implementamos esta solucion ya que permite mayor legibilidad de codigo y, si en un futuro deseamos agregar mas palabras reservadas, tendriamos que modificar unicamente el valor de `CANT_PALABRAS_RESERVADAS`.

- Implementacion de `typedef const char* PalabraReservada;` :
  
    Implementamos, junto a `PalabraReservada palabras_reservadas[CANT_PALABRAS_RESERVADAS] = {"inicio", "fin", "leer", "escribir"}` para definir los lexemas que podemos recibir (de tamaño 4).

- Implementacion de `TOKEN token_palabras_reservadas[CANT_PALABRAS_RESERVADAS] = {INICIO, FIN, LEER, ESCRIBIR}` :
  
    Implementamos esto para definir aquellos tokens que consideraremos palabras reservadas, una vez procesados los lexemas (de tamaño 4 y tipo TOKEN definidos en typedef enum {...} TOKEN)

- Implementacion de `_pos = 0` en funcion `LimpiarBuffer()` :
  
    Inicializamos el contador nuevamente en 0, para que la lectura del buffer comience nuevamente desde posicion 0 del mismo, y que no lo haga desde la posicion en la que habia quedado del contenido del buffer anterior
                                 
- Cambios Makefile:

    Los cambios en el Makefile buscan mejorar la compatibilidad con Windows y optimizar el flujo de 
    trabajo. Se eliminan los archivos objeto (`*.o`) al final de la compilación para mantener limpio el 
    proyecto, y se organizan las pruebas (`test1` y `test2`) en objetivos separados para facilitar el control 
    y la verificación de casos específicos. Además, se adaptan los comandos de limpieza (`clean`) para funcionar 
    en Windows y se agregan instrucciones claras para compilar (`make mmc`), ejecutar pruebas (`make test1` o `make test2`), 
    y limpiar (`make clean`), proporcionando así una estructura clara y portable para desarrollar y probar el código.

- Modificacion en el .gitignore:

    Se añadió la carpeta `.vscode/` para que no se suban configuraciones locales de Visual Studio Code, 
    que suelen ser personales y no relevantes para otros desarrolladores. También se ignoran todos los archivos `.o`,
    generados durante la compilación como archivos intermedios, ya que no son necesarios en el control de 
    versiones y ocupan espacio de forma innecesaria. Se incluyó el archivo `a.out`, un ejecutable generado 
    automáticamente en compilaciones estándar de C en algunos sistemas, y el `mmc.exe`, un ejecutable específico 
    del proyecto en Windows.

- Modificacion del main.c:

    Se añadió un vector de strings (`OUTPUT_TOKEN`) que asocia cada token con una descripción más comprensible 
    (por ejemplo, "INICIO (PR)" en lugar de solo un número), lo que permite que se vea de forma clara en la consola.
#include <stdio.h>
#include <ctype.h>
#include <string.h> // Incluimos la libreria para poder hacer uso de strcmp(/2)
#include "scanner.h"

#define TAMANIO_BUFFER 20
#define CANT_PALABRAS_RESERVADAS 4

typedef const char* PalabraReservada; /* Declaramos que todas las palabras reservadas serán cadenas de caracteres 
                                      (utilizado al declarar todas nuestras posibles palabras reservadas, que seran
                                       usadas en la funcion esReservada())*/

typedef int ESTADO;

char _buffer[TAMANIO_BUFFER+1];

int  _pos = 0;

void LimpiarBuffer(void) {

    //Se agrega un ciclo para poner el buffer en 0 en cada una de sus posiciones

    for (int i = 0; i < TAMANIO_BUFFER + 1 ; i++)
    {
        _buffer[i] = '\0';
    }

    _pos = 0;   /* Inicializamos el contador nuevamente en 0, para que la lectura del buffer comience nuevamente desde
                posicion 0 del mismo, y que no lo haga desde la posicion en la que habia quedado del contenido del 
                buffer anterior */
}

void AgregarCaracter(int caracter) {
    _buffer[_pos++] = caracter;
}

const char *Buffer(void) {
    _buffer[_pos] = '\0';
    return _buffer;
}

PalabraReservada palabras_reservadas[CANT_PALABRAS_RESERVADAS] = { // Definimos los lexemas que podemos recibir y consideraremos
    "inicio", "fin", "leer", "escribir"        // palabras reservadas (de tamaño 4).
};

TOKEN token_palabras_reservadas[CANT_PALABRAS_RESERVADAS] = {      // Definimos los tokens que consideraremos palabras reservadas
    INICIO, FIN, LEER, ESCRIBIR                                    // una vez procesados los lexemas (de tamaño 4 y tipo TOKEN.
};                                                                 // definidos en typedef enum {...} TOKEN)
                                                             
int ObtenerColumna(int simbolo) {
    if (isalpha(simbolo)) {
        return 0;
    } else if (isdigit(simbolo)) {
        return 1;
    } else if (simbolo == '+') {
        return 2;
    } else if (simbolo == '-') {
        return 3;
    } else if (simbolo == '(') {
        return 4;
    } else if (simbolo == ')') {
        return 5;
    } else if (simbolo == ',') {
        return 6;
    } else if (simbolo == ';') {
        return 7;
    } else if (simbolo == ':') {
        return 8;
    } else if (simbolo == '=') {
        return 9;
    } else if (simbolo == EOF) { //se agrega EOF para mejor identificacion en vez de -1
        return 10;
    } else if (isspace(simbolo)) {
        return 11;
    }    
    return 12;
}

ESTADO Transicion(ESTADO estado, int simbolo) {

    static ESTADO TT[15][13] = {      /*cambio el numero de estados a 15 (filas, originalmente estaba en 12) como se menciona en la descripcion 
                                        de la TT del AFD que compone el scanner en la seccion 3.2.4.1 de Muchnik*/
 
        /*los 99 simbolizan los espacios en blanco de TT, si no se rellenan con un entero da error- Ademas simbolizan los 
        errores lexicos (no estoy seguro de que sea la mejor solucion) */

                 /* L |  D |  + |  - |  ( |  ) |  , |   ; |   : |   = | fdt | sp | otro */
        /*  0- */{  1 ,  3 ,  5 ,  6 ,  7 ,  8 ,  9 ,  10 ,  11 ,  14 ,  13 ,  0 , 99  },
        /*  1  */{  1 ,  1 ,  2 ,  2 ,  2 ,  2 ,  2 ,   2 ,   2 ,   2 ,   2 ,  2 ,  2  },
        /*  2+ */{ 99 , 99 , 99 , 99 , 99 , 99 , 99 ,  99 ,  99 ,  99 ,  99 ,  2 , 99  },
        /*  3  */{  4 ,  3 ,  4 ,  4 ,  4 ,  4 ,  4 ,   4 ,   4 ,   4 ,   4 ,  4 ,  4  },
        /*  4+ */{ 99 , 99 , 99 , 99 , 99 , 99 , 99 ,  99 ,  99 ,  99 ,  99 , 99 , 99  },
        /*  5+ */{ 99 , 99 , 99 , 99 , 99 , 99 , 99 ,  99 ,  99 ,  99 ,  99 , 99 , 99  },
        /*  6+ */{ 99 , 99 , 99 , 99 , 99 , 99 , 99 ,  99 ,  99 ,  99 ,  99 , 99 , 99  },
        /*  7+ */{ 99 , 99 , 99 , 99 , 99 , 99 , 99 ,  99 ,  99 ,  99 ,  99 , 99 , 99  },
        /*  8+ */{ 99 , 99 , 99 , 99 , 99 , 99 , 99 ,  99 ,  99 ,  99 ,  99 , 99 , 99  },
        /*  9+ */{ 99 , 99 , 99 , 99 , 99 , 99 , 99 ,  99 ,  99 ,  99 ,  99 , 99 , 99  },
        /* 10+ */{ 99 , 99 , 99 , 99 , 99 , 99 , 99 ,  99 ,  99 ,  99 ,  99 , 99 , 99  },
        /* 11  */{ 99 , 99 , 99 , 99 , 99 , 99 , 99 ,  99 ,  99 ,  12 ,  99 , 99 , 99  },
        /* 12+ */{ 99 , 99 , 99 , 99 , 99 , 99 , 99 ,  99 ,  99 ,  99 ,  99 , 99 , 99  },
        /* 13+ */{ 99 , 99 , 99 , 99 , 99 , 99 , 99 ,  99 ,  99 ,  99 ,  99 , 99 , 99  },
        /* 14  */{ 99 , 99 , 99 , 99 , 99 , 99 , 99 ,  99 ,  99 ,  99 ,  99 , 99 , 99  },
    };
    
    int columna = ObtenerColumna(simbolo); //se obtiene la columna segun el simbolo de tipo char, isdigit y isalpha apesar de que dice que ingresan int se espera un char
    
    ESTADO nuevoEstado = TT[estado][columna]; // hacer la transicion segun la matriz 
    
    return nuevoEstado;

}

TOKEN EsReservada(){    //Se deja el mismo codigo solo que se lo pasa funcion especifica para hacer el codigo mas modular

        for (int i = 0; i < CANT_PALABRAS_RESERVADAS; i++) {                    // Itero la cantidad de palabras reservadas
                    if (strcmp(Buffer(), palabras_reservadas[i]) == 0) {        // Si el lexema contenido en el buffer es igual a alguna de las palabras reservadas,
                        return token_palabras_reservadas[i];                    // devolveremos su token asociado
                    }
                    
                }
        return ID;  //En caso que el en for no se detecte ninguna palabra reservada en el buffer, retorara ID
        
};

TOKEN Scanner(void) {
    TOKEN token = 0;

    int c, //pos = 0; esto estaba declarado mal. el correcto nombre de la varible que da el indice al buffer es _pos y ya estaba declarada fuera de scanner

    _pos = 0;  //ponemos en cero correctamente el buffer

    ESTADO estado = 0;
    LimpiarBuffer();
    while (c=getchar()) {
        estado = Transicion(estado, c);
        switch (estado) {
            case 1:
            case 3:
                AgregarCaracter(c);
                break;
            case 2:
                ungetc(c, stdin);
                return EsReservada(); //Se agrega funcion de identificacion de palabras reservadas
            case 4:
                ungetc(c, stdin);
                return CONSTANTE; 
            case 5:
                AgregarCaracter(c);
                return SUMA; 
            case 6:
                AgregarCaracter(c);
                return RESTA; 
            case 7:
                AgregarCaracter(c);
                return PARENIZQUIERDO;  
            case 8:
                AgregarCaracter(c);
                return PARENDERECHO;  
            case 9:
                AgregarCaracter(c);
                return COMA; 
            case 10:
                AgregarCaracter(c);
                return PUNTOYCOMA;  
            case 11:
                AgregarCaracter(c);
                break;
            case 12:
                AgregarCaracter(c);
                return ASIGNACION; 
            case 13:
                return FDT; 
            case 99:
                AgregarCaracter(c);    //Se agrega caracter no valido al buffer para retornarlo por pantalla
                printf("\nError lexico! entrada no valida: %s\n\n", Buffer());  //Se retorna 99 para que el Scanner vuelva a empezar luego de detectar el error lexico y dar el mensaje por consola
                return 99;
        }
    }
}

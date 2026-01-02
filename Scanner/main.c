#include <stdio.h>
#include "scanner.h"

int main(void) {

    //Se agrega vector de strings para que el output de consola sea mas claro, 

    const char *OUTPUT_TOKEN[] = {"INICIO (PR)", "FIN (PR)", "LEER (PR)", "ESCRIBIR (PR)", "ID", "CONSTANTE", "PARENIZQUIERDO",
    "PARENDERECHO", "PUNTOYCOMA", "COMA", "ASIGNACION", "SUMA", "RESTA", "FDT"};

    TOKEN t;

    while ((t = Scanner()) != 13) {

        //Posible solucion para errores lexicos del tipo: _BB | 1nicio
         
        if(t!=99){      //cuando Scanner devuelve un estado, el output remplaza el digito correspondiente por el nombre de token. Ej: abc -> 4 seria abc -> ID
        
            printf("\t%s\t->\t%s\n", Buffer(),OUTPUT_TOKEN[t] );
        
        };
    }
}

all: mmc

mmc: main.c scanner.h scanner.o
	cc -c main.c
	cc -o mmc main.o scanner.o
	del /Q *.o			

#Se eliminan .o luego de la compilacion al no ser necesarios


#para windows			Se separan los test para una mejor prueba del codigo
test1: mmc
	mmc.exe < test.ok.micro
	
test2: mmc
	mmc.exe < test.error-lex.micro

#para linux
#test1: mmc				Se separan los test para una mejor prueba del codigo
#	./mmc < test.ok.micro

#test2: mmc
#	./mmc < test.error-lex.micro

clean:
	del mmc.exe

#   rm -rf *.o mmc
#se cambio el comando porque el que estaba solo funcionaba para linux y el nuevo es compatible con windows


#parece para compilar y probar el scanner hay que ejecutar
#make mmc
#make test
# y luego un make clean para que elimine los ejecutables y el mmc.exe

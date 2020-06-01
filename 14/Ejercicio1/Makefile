Ejercicio1:  Ejercicio1.o gfx.o
	g++ -std=c++11 Ejercicio1.o gfx.o -o Ejercicio1 -lX11
Ejercicio1.o: Ejercicio1.cpp gfx.o
	g++ -std=c++11 Ejercicio1.cpp -c
gfx.o: gfx.c gfx.h
	gcc gfx.c -c
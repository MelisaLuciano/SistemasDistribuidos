#CFLAGS = -Wall -Werror -g

all: cliente

cliente: cliente.cpp SocketDatagrama.o PaqueteDatagrama.o 
	g++ cliente.cpp SocketDatagrama.o PaqueteDatagrama.o  $(CFLAGS) -lpthread -o cliente.out -O2

PaqueteDatagrama: PaqueteDatagrama.cpp
	g++ PaqueteDatagrama.cpp -c

SocketDatagrama: SocketDatagrama.cpp
	g++ SocketDatagrama.cpp -c
clean:
	rm -f *.out *.o

clang:
	clang-format-3.4 -i -style=Google *.h *.cpp
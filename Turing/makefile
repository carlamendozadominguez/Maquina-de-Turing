CC=g++ 
CXXFLAGS=-g -std=c++11

OBJS = estado.o transicion.o turing.o cinta.o main.o

all: ${OBJS}
	$(CC) $(CXXFLAGS) -o main ${OBJS}

clean: 
	rm -rf *.o main

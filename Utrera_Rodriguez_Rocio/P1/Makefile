


#Compilador
CXX=clang++
#Carpetas donde buscar cabeceras
VPATH = ../Tests-auto:.
#Flags del compilador
CXXFLAGS = -g -Wall -pedantic -std=c++11
#Flags del preprocesador
CPPFLAGS = -I../Tests-auto -I. -DP1
#Código objeto
OBJS = fecha.o cadena.o test-P1-consola.o test-P1-auto.o
###
all: test-P1-consola test-P1-auto
###
test-P1-auto: test-caso0-fecha-auto.o test-caso0-cadena-auto.o test-auto.o fecha.o cadena.o
	$(CXX) $(LDFLAGS) $^ -o $@
test-caso0-fecha-auto.o test-caso0-cadena-auto.o: test-auto.hpp fecha.hpp cadena.hpp fct.h

test-P1-consola:test-P1-consola.o fecha.o cadena.o
	$(CXX) $(LDFLAGS) $^ -o $@

test-P1-consola.o:fecha.hpp cadena.hpp

fecha.o:fecha.cpp fecha.hpp

cadena.o:cadena.cpp cadena.hpp

clean:
	$(RM) all $(OBJS) core *~


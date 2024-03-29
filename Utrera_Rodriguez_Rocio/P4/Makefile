# $Id: Makefile 399 2017-05-17 17:32:04Z gerardo $
# Makefile para el caso 4 de la LIBRERÍA
# ©2010-17 los profesores de POO, para P4
#
## Variables, macros, más macros y más variables, que es lo mismo. ##
# --- Parte configurable ---

# NOMBREALUMNO es el nombre del directorio donde el alumno guarda las
# prácticas de POO (C++). Dentro de ese directorio debe haber uno para
# cada práctica llamado NOMBREPRACTICA, que será de la forma P<n>,
# siendo <n> el número de práctica: P0, P1, P2, P3 y P4. En esta práctica, P4.
# NOMBREALUMNO debe ser de la forma: Apellido1_Apellido2_Nombre_de_pila.
# Ejemplo: Para Pánfilo Pancracio Povedilla Putiérrez sería:
# Povedilla_Putierrez_PanfiloPancracio, y debajo de ese directorio estarían
# P1, P4 y los directorios Tests-auto y dsl-comprobaciones (y P0, P2 y P3).
# Véanse las instrucciones de entrega en el enunciado.
NA = $(shell dirname ${PWD})
NOMBREALUMNO = $(notdir ${NA})

# DIRFECHACADENA es el directorio donde están las cabeceras, fuentes o módulos
# objeto de las clases Cadena y Fecha de P1, y su Makefile.
# NOTA IMPORTANTE: Este Makefile supone que ya Cadena y Fecha están hechos y
# no se modifican. Si se cambiara algo en ellos, habría que recompilar.
DFC = P1
DIRFECHACADENA = ../${DFC}

# Esto debe dejarse así para que funcionen los tests automáticos.
# DIRTESTS es el directorio donde están los ficheros del programa de pruebas
# unitarias automáticas.
DIRTESTS = ../Tests-auto
NOMBREPRACTICA := P4
INCLUDES  = -I${DIRFECHACADENA} -I${DIRTESTS} -I.

# DIRLUHN es el directorio donde está el fichero luhn.cpp con la función luhn
DIRLUHN = ..

# Compilador de C++ preferido: el de LLVM (clang++), el de GNU (g++),
# el de GNU en la versión 5 (g++-5), el de Intel (icpc)...
CXX = clang++

# ¿Qué estándar seguir?
# c++98 o c++03 (-ansi): estándar de 1998, corregido en 2003. NO USAR YA.
# c++0x: borrador del estándar de 2011. Usar si el compilador es antiguo.
# c++11: estándar de 2011 - Versión mínima necesaria.
# c++1y: borrador del est. de 2014. Si su compilador es antiguo pero no mucho.
# c++14: estándar de 2014 - Recomendado si su compilador lo admite.
# c++17: estándar de 2017 - Se puede usar si su compilador lo admite.
# c++2y: estándar previsto para 2020. Experimental, no recomendado.
STD = c++14

# Opciones para el compilador. Añada o quite las que prefiera pero deje
# al menos la primera. Recomendado: no quite ninguna.
# -std=${STD}: el estándar de C++ a utilizar, en $(STD)
# -g         : para poder depurar, si hay que hacerlo
# -pedantic  : para que se ajuste sin desvíos del estándar empleado
# -Wall      : para que dé todo tipo de avisos, no solo los normales
CXXFLAGS = -std=${STD} -g -pedantic -Wall

# Opciones del preprocesador. No las quite.
# -I : directorio donde buscar cabeceras adicionales (#include "...")
# -D : define una macro del preprocesador, como #define
CPPFLAGS = ${INCLUDES} -D${NOMBREPRACTICA}

# --- Fin parte configurable

LOCALLIBS = cadena.o fecha.o luhn.o
EXTLIBS   = -lcrypt
LIBS      = ${LOCALLIBS} ${EXTLIBS}
VPATH     = .:${DIRTESTS}:${DIRFECHACADENA}:${DIRLUHN}

# Estos son los ficheros que tiene que hacer el alumno. El resto se le da.
# NOTA IMPORTANTE: usuario-pedido.cpp no hace falta si se hacen los métodos
# de Usuario_Pedido inline, pero si se definen normales en usuario-pedido.cpp, 
# añádase a OWN_SRCS y quítese usuario-pedido.hpp de OWN_HDRS.

OWN_SRCS  = usuario.cpp tarjeta.cpp articulo.cpp pedido-articulo.cpp \
  pedido.cpp
OWN_HDRS  = $(OWN_SRCS:.cpp=.hpp)

OWN_OBJS  = $(OWN_SRCS:.cpp=.o)

MAIN_SRCS = test-caso4-consola.cpp
MAIN_OBJS = $(MAIN_SRCS:.cpp=.o)
MAIN_EXE  = ${MAIN_SRCS:.cpp=}

TEST_SRCS = test-caso0-cadena-auto.cpp test-caso0-fecha-auto.cpp \
  test-caso1-2-auto.cpp test-caso3-auto.cpp test-caso4-auto.cpp test-auto.cpp
TEST_HDRS = test-auto.hpp fct.h
TEST_OBJS = $(TEST_SRCS:.cpp=.o)
TEST_EXE  = test-P4-auto

CHECK_SRC = catalogo_check.cpp
CHECK_OBJ = ${CHECK_SRC:.cpp=.o}
CHECK_EXE = ${CHECK_SRC:.cpp=}

SRCS      = ${OWN_SRCS} $(MAIN_SRCS) ${TEST_SRCS} $(CHECK_SRC) \
            Makefile Make_check.mk
HDRS      = $(OWN_HDRS) $(TEST_HDRS)

NOMBRETAR = ../../${NOMBREALUMNO}.tar.gz
D = ${NOMBREALUMNO}/${NOMBREPRACTICA}

## OBJETIVOS PRINCIPALES ## 

# Construye los programas de prueba
all: ${MAIN_EXE} ${TEST_EXE}

# Ejecuta los programas de prueba
tests: test-consola test-auto

# Construye el test de consola y lo ejecuta
test-consola: ${MAIN_EXE}
	./$<

# Construye el test automático y lo ejecuta
test-auto: ${TEST_EXE}
	./$<

# Hace comprobaciones en el código fuente
check:  ${OWN_SRCS}
	${MAKE} --file=Make_check.mk $@

# Ejecuta los tests comprobando que no haya fugas de memoria
# - valgrind: http://valgrind.org
valgrind: ${MAIN_EXE} ${TEST_EXE}
	valgrind --quiet ./${TEST_EXE} --logger=minimal
	valgrind --quiet ./${MAIN_EXE}

## Compilación ## 

# Construye el programa de prueba de consola
${MAIN_EXE}: ${MAIN_OBJS} ${OWN_OBJS} ${LOCALLIBS}
	${CXX} -o $@ ${LDFLAGS} $^ ${EXTLIBS}

# Construye el programa de pruebas unitarias automáticas
${TEST_EXE}: ${TEST_OBJS} ${OWN_OBJS} ${LOCALLIBS}
	${CXX} -o $@ ${LDFLAGS} $^ ${EXTLIBS}

# Construye el programa de comprobaciones sobre el código fuente
${CHECK_EXE}: ${CHECK_SRC}
	${MAKE} --file=Make_check.mk $@

# Detección automática de dependencias en código fuente C++ #
%.d: %.cpp
	@$(CXX) -MM -MF $@ ${CPPFLAGS} $(CXXFLAGS) $<
	@sed --regexp-extended --in-place 's,($*)\.o[ :]*,\1.o $@ : ,g' $@

-include $(OWN_SRCS:.cpp=.d) $(MAIN_SRCS:.cpp=.d) $(TEST_SRCS:.cpp=.d)

# Porque Cadena y Fecha aún son susceptibles de cambios...
cadena.o: ${DIRFECHACADENA}/cadena.hpp
fecha.o : ${DIRFECHACADENA}/fecha.hpp

# Por si se cambia algo en los tests automáticos
${TESTS_OBJS}: ${TESTS_SRCS} ${TESTS_HDRS}

## Cobertura / Perfilado 

# Descomentando estas dos líneas de CXXFLAGS y LDFLAGS se activa el soporte 
# para las pruebas de cobertura y el perfilado de los programas. 
# Una vez tenemos esto y recompilamos por completo (generando una serie de 
# ficheros .gcno para gcov), podemos ejecutar el programa de la forma usual, 
# y se generarán gmon.out (para gprof) y un .gcda (para gcov) para cada .cpp 
# y .hpp del programa ejecutado.
#
# Desde el directorio donde está gmon.out, podremos hacer:
#
# gprof ejecutable
#
# para ver en la salida estándar qué funciones han consumido más tiempo. 
# Y podremos usar:
#
# gcov fichero.cpp
#
# para ver qué líneas se han ejecutado y cuáles no en fichero.cpp.gcov.

#CXXFLAGS = -pg -g -fprofile-arcs -ftest-coverage -std=${STD} -pedantic -Wall
#LDFLAGS  = -pg -fprofile-arcs

## Limpieza
#  normal...
clean:
	${RM} ${MAIN_EXE} ${MAIN_OBJS} ${TEST_EXE} ${TEST_OBJS} \
	      ${OWN_OBJS} ${LOCALLIBS} *.d *~ \#* *.{aux,log,dvi,toc} core
	${MAKE} --directory=${DIRFECHACADENA} clean
	${MAKE} --file=Make_check.mk clean

# ... y del archivo a entregar.
distclean: clean
	${RM} ${NOMBRETAR}

## Empaquetado para entrega

# Esto lo debería usar el alumnado a la hora de la entrega:
# crea el archivo .tar.gz en el directorio padre de las prácticas
# tras borrar lo sobrante.
dist: distclean ${NOMBRETAR}

${NOMBRETAR}: ${OWN_SRCS} ${OWN_HDRS}
ifeq ($(strip $(NOMBREALUMNO)),)
	@echo ""
	@echo "ATENCIÓN: En el Makefile debe estar definida la variable"
	@echo " NOMBREALUMNO con el nombre del directorio superior a este."
	@echo "Vea las instrucciones de entrega de las prácticas."
else
	@echo "Creando archivo en ${NOMBRETAR} con el siguiente contenido:"
	@tar --create --verbose --gzip --file=${NOMBRETAR} --directory=../.. \
		$D/usuario.cpp  $D/usuario.hpp  \
		$D/articulo.cpp $D/articulo.hpp \
		$D/tarjeta.cpp  $D/tarjeta.hpp  \
		$D/pedido.hpp   $D/pedido.cpp   \
		$D/pedido-articulo.cpp $D/pedido-articulo.hpp \
		$D/usuario-pedido.cpp  $D/usuario-pedido.hpp  \
		${NOMBREALUMNO}/${DFC}/cadena.hpp \
		${NOMBREALUMNO}/${DFC}/cadena.cpp \
		${NOMBREALUMNO}/${DFC}/fecha.hpp  \
		${NOMBREALUMNO}/${DFC}/fecha.cpp  \
		${NOMBREALUMNO}/${DFC}/Makefile
endif

# Objetivos falsos
.PHONY: all clean tests dist distclean valgrind test-consola test-auto

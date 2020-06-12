EXDEPS  = ${OBJ}
GENDEPS = python analysis
CPP     = ${GENDEPS:=.cpp} main.cpp
OBJ     = ${GENDEPS:=.o} main.o
HEAD    = ${GENDEPS:=.h}
GPP     = g++
FLAG    = -Wall -Wextra -Werror -Wpedantic -Wold-style-cast
#PYFLAG  = pkg-config --cflags --libs python3
EXEC    = stockbot
MESS    = "generic commit"
GIT     = git commit -am
BIN     = ~/.Scripts/

all : ${EXDEPS}
	${GPP} ${FLAG} -o ${EXEC} ${OBJ}

%.o : %.cpp
	${GPP} ${FLAG} -o $@ -c $<

test : ${EXEC}
	./${EXEC}

clean :
	rm ${EXEC}

spotless :
	rm log.txt
	rm ${OBJ} ${EXEC}

edit :
	emacs ${CPP}&

ci :
	${GIT} ${MESS}

deps : ${OBJ}

install : ${EXDEPS}
	${GPP} ${FLAG} -o ${BIN}${EXEC} ${OBJ}

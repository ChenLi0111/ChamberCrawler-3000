CXX = g++
CXXFLAGS = -g -std=c++11 -MMD -Wall
EXEC = cc3k
OBJECT = main.o map.o mapunit.o player.o nonplayer.o items.o observer.o subject.o character.o

DEPEND = ${OBJECT:.o=.d}

${EXEC}: ${OBJECT}
	${CXX} ${CXXFLAGS} ${OBJECT} -o ${EXEC}

-include ${DEPEND}

clean:
	rm ${OBJECT} ${EXEC} ${DEPENDS} *.d
CXX= g++
CXXFLAGS= -g -std=c++11 -MMD -Wall
OBJECT= main.o map.o mapunit.o player.o nonplayer.o items.o observer.o subject.o character.o

DEPEND= ${OBJECT:.o=.d}
EXEC=cc3k

${EXEC}: ${OBJECT}
	${CXX} ${CXXFLAGS} ${OBJECT} -o ${EXEC}

-include ${DEPEND}

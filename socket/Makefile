CXX = g++
INC = common.h
CXXFLAGS = -std=c++11 -Wall -g -o 

all:clean server client

server: ${INC}
	${CXX} ${CXXFLAGS} $@ server.cpp

client: ${INC}
	${CXX} ${CXXFLAGS} $@ client.cpp

.PHONY: all clean

clean:
	rm -rf server client

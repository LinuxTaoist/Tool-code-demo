CXX = g++
CXXFLAGS = -std=c++11 -Wall -g -o 
inc = common.h

all:clean server client

server: ${inc}
	${CXX} ${CXXFLAGS} $@ server.cpp

client: ${inc}
	${CXX} ${CXXFLAGS} $@ client.cpp

.PHONY: all clean

clean:
	rm -rf server client

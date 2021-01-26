CXX = g++
CXXFLAGS = -std=c++11 -g -o 
inc = common.h

all:clean read write

read: ${inc}
	${CXX} ${CXXFLAGS} $@ read.cpp

write: ${inc}
	${CXX} ${CXXFLAGS} $@ write.cpp

.PHONY: all clean

clean:
	rm -rf read write

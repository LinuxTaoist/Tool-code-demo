CXX = g++
CXXFLAGS = -std=c++11 -Wall -g -o 
inc =

all:clean read write

read: ${inc}
	${CXX} ${CXXFLAGS} $@ fifo_read.cpp

write: ${inc}
	${CXX} ${CXXFLAGS} $@ fifo_write.cpp

.PHONY: all clean

clean:
	rm -rf read write

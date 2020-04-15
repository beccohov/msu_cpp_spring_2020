all: test
test: main.o ser.o
	g++ -std=c++11 main.o -o test

ser.o : serializer.cpp
main.o : main.cpp
run:
	./test
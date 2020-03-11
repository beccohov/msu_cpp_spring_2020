#run:	test
#	./start.o
#test:
#	g++ Testing.cpp lstdc++ -o start.o
all: test
test: testing.o allocator.o 
	g++ testing.o allocator.o -o test
allocator.o: Allocator.cpp
	g++ -c Allocator.cpp
testing.o: 
	g++ -c Testing.cpp
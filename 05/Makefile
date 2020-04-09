all:test
test: main.o bigint.o
	g++ main.o BigInt.cpp -o test
main.o: main.cpp
bigint.o: BigInt.cpp
run:
	./test
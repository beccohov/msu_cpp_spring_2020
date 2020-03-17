all: test
test: main.o tokenizer.o
	g++ main.o tokenizer.o -o test
tokenizer.o: tokenizer.cpp
main.o: main.cpp
run:
	./test
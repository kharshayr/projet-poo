CC=g++ ##-g -std=c++11 -Wall -Werror -o main.exe methods.cpp main.cpp

CPPFLAGS=-g -c -std=c++11 -Wall -Werror

all: main.exe

main.exe: main.o methods.o memory.o bus.o display.o cpu.o
	$(CC) $^ -o $@

%.o: %.cpp
	$(CC) $(CPPFLAGS) $< -o $@



.PHONY: clean run
 clean:
	rm *.o
	rm *.exe

run: main.exe
	./main.exe

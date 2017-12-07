all: main.o
	g++ main.o -std=c++11 -O0 -o main
	./main

main.o: main.cpp
	g++ -c -std=c++11 main.cpp

clean:
	rm *.o
	rm main



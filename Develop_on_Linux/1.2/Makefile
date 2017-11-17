all: hello

hello: main.c hello.h lib
	gcc main.c -L. -lHello -o hello

lib: hello.h hello.c
	gcc -o libHello.so -shared -fPIC hello.c

clean:
	-rm hello libHello.so 2>/dev/null


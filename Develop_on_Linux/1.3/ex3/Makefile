all: exe

exe: solution.c
	gcc solution.c -ldl '-Wl,-rpath=.' -o solution

lib: shared.h shared.c
	gcc -shared shared.c -fPIC -o libShared.so

clean:
	-rm solution libShared.so 2>/dev/null



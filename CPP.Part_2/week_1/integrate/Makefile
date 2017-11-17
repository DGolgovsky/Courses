CC=g++

STD=-std=c++17
ERR=-Wall -Wextra -pedantic
CFLAGS=-I.

#SFML Example
LIBS=-pthread
OBJS=integrate.o
EXE=integrate.bin

DEPS=

all: $(EXE)

clean:
	-rm $(EXE)
	-rm *.o

%.o: %.cpp $(DEPS) Makefile
	$(CC) $(STD) -g -O2 -c $(ERR) -o $@ $< $(CFLAGS)

$(EXE): $(OBJS) Makefile
	$(CC) -o $@ $(OBJS) $(LIBS)
	@echo 'Built executable:' $(EXE)


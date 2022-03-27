COMPILER = gcc
FLAGS = -Wall -g

all: ww.out
ww: ww.out

ww.o: ww.c ww.h
	$(COMPILER) $(FLAGS) -c ww.c

ww.out: ww.o
	$(COMPILER) $(FLAGS) -o ww.out ww.o

clean:
	rm -f *.o *.out
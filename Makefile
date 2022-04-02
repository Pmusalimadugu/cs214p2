COMPILER = gcc
FLAGS = -Wall -g

all: ww.out
ww: ww.out


word.o: word.c word.h
	$(COMPILER) $(FLAGS) -c word.c

ww.o: ww.c ww.h word.h
	$(COMPILER) $(FLAGS) -c ww.c

ww.out: ww.o word.o
	$(COMPILER) $(FLAGS) -o ww.out ww.o word.o

clean:
	rm -f *.o *.out
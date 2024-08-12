flags=-O2 -Wall -std=c2x -ggdb
ldflags=

all: clean needle

needle: needle.o
	cc ${flags} $^ -o $@ ${ldflags}

needle.o: needle.c
	cc ${flags} -c $^

clean:
	rm -f *.o needle

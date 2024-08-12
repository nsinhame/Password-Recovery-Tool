flags=-03 -std=c2x -Wall
ldflags=-lcrypt

all: clean pw

pw: pw.o
	cc ${flags} $^ -o $@ ${ldflags}

pw.o: pw.c2
	cc ${flags} -c $^

clean:
	rm -f 8.o pw
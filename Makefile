CC=gcc

main_source := $(wildcard src/*.c)
main_headers := $(wildcard src/*.h)
data := $(wildcard data/*)

.PHONY: all
all: objloader.a

objloader.a: objloader.o
	ar rcs libobjloader.a objloader.o

objloader.o: $(main_source) $(main_headers)
	$(CC) -g -c src/objloader.c -o objloader.o


.PHONY: clean
clean:
	rm -f objloader.o
	rm -f libobjloader.a

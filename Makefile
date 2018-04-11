all:
	gcc -o rw readerwriter.c -w -lpthread
clean:
	rm rw
	
p05: p05.o
	gcc -o p05 p05.o
p05.o: p05.c
	gcc -c p05.c
clean:
	rm p05 p05.o


# todo: make makefile


pre-clean:
	rm main.o mendokusai

post-clean:
	rm main.o

main.o: main.c
	gcc -c main.c

mendokusai: main.o
	gcc main.o -o mendokusai
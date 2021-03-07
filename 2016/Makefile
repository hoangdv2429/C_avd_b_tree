all:	main
main:	main.o directedGraphlib.o
		gcc -g -o main main.o directedGraphlib.o libfdr.a -lm
main.o:	main.c 
	gcc -g -I/ -c main.c 
directedGraphlib.o:	directedGraphlib.c
	gcc -g -I/ -c directedGraphlib.c 
clean:	
	rm -f *.o *~

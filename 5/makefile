Graph: main.o libgraph.a
	gcc -o Graph main.o -L. -lgraph -lreadline -g
main.o: main.c
	gcc -c main.c
libgraph.a: func1.o
	ar r libgraph.a func1.o
func1.o: func1.c
	gcc -c func1.c
clean:
	rm *.o
	rm *.a

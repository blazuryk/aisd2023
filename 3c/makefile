lb3v: main.o libtabl.a
	gcc -o lb3v main.o -L. -ltabl -lreadline
main.o: main.c
	gcc -c main.c
libtabl.a: func.o
	ar r libtabl.a func.o
func.o: func.c
	gcc -c func.c
clean:
	rm *.o
	rm *.a

lb4a: main.o libtree.a
	gcc -o lb4a main.o -L. -ltree -lreadline -g
main.o: main.c
	gcc -c main.c
libtree.a: func.o
	ar r libtree.a func.o
func.o: func.c
	gcc -c func.c 
clean:
	rm *.o
	rm *.a

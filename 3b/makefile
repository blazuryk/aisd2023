lb3b: main1.o libtabl.a
	gcc -o lb3b main1.o -L. -ltabl -lreadline
main1.o: main1.c
	gcc -c main1.c
libtabl.a: func1.o
	ar r libtabl.a func1.o
func.o: func1.c
	gcc -c func1.c
clean:
	rm *.o
	rm *.a

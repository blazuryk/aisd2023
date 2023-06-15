Stackv: main.o libstackv.a libstacks.a
	gcc -o Stackv main.o -L. -lstackv 
	gcc -o Stacks main.o -L. -lstacks
main.o: main.c 
	gcc -c main.c 
libstackv.a: stackv.o
	ar r libstackv.a stackv.o
libstacks.a: stacks.o
	ar r libstacks.a stacks.o
stackv.o: stackv.c
	gcc -c stackv.c
stacks.o:
	gcc -c stacks.c
clean:
	rm *.o
	rm *.a

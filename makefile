JerryBoree: JerryBoreeMain.o Jerry.o HashTable.o LinkedList.o KeyValuePair.o MultiValueHashTable.o
	gcc *.c -o JerryBoree

JerryBoreeMain.o: JerryBoreeMain.c Jerry.h LinkedList.h HashTable.h MultiValueHashTable.h Defs.h
	gcc -c JerryBoreeMain.c HashTable.c Jerry.c LinkedList.c MultiValueHashTable.c

Jerry.o: Jerry.c Jerry.h Defs.h
	gcc -c Jerry.c
	
KeyValuePair.o: KeyValuePair.c KeyValuePair.h Defs.h
	gcc -c KeyValuePair.c

LinkedList.o: LinkedList.c LinkedList.h Defs.h
	gcc -c LinkedList.c

HashTable.o: HashTable.c HashTable.h LinkedList.h KeyValuePair.h Defs.h
	gcc -c HashTable.c KeyValuePair.c LinkedList.c

MultiValueHashTable.o: MultiValueHashTable.c MultiValueHashTable.h HashTable.h LinkedList.h Defs.h
	gcc -c MultiValueHashTable.c HashTable.c LinkedList.c

clean:
	rm -f *.o

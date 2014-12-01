CC=gcc
CCFLAGS=-Wall
CLEAN=rm -f *.o
PROGRAM_NAME=hash

$(PROGRAM_NAME): main.o liblist.a libhash.a 
	$(CC) $(CCFLAGS) $< -o $@ -L. -lhash  -llist -lm
main.o: main.c
	$(CC) $(CCFLAGS) $-c $<
libhash.a: M_hash.o
	ar rcs $@ $< 
liblist.a: M_list.o
	ar rcs $@ $< 
M_list.o: M_list.c
	$(CC) $(CCFLAGS)  -c $<
M_hash.o: M_hash.c
	$(CC) $(CCFLAGS) -c $<
clean:
	$(CLEAN)	
	
	

CC=gcc
CCFLAGS=-m64 -Ofast -flto -march=native -funroll-loops
CLEAN=rm -f *.o
PROGRAM_NAME=hash

$(PROGRAM_NAME): main.o liblist.a libhash.a libhash3.a 
	$(CC) $(CCFLAGS) $< -o $@ -L. -lhash  -llist -lhash3 -lm 
main.o: main.c
	$(CC) $(CCFLAGS) -c $< 
libhash.a: M_hash.o
	ar rcs $@ $< 
libhash3.a: hash3.o
	ar rcs $@ $< 
hash3.o: hash3.asm
	nasm -f elf64 -o $@ $<
liblist.a: M_list.o
	ar rcs $@ $< 
M_list.o: M_list.c
	$(CC) $(CCFLAGS)  -c $< 
M_hash.o: M_hash.c
	$(CC) $(CCFLAGS) -c $< 
clean:
	$(CLEAN)	
	
	

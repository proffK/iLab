CC=gcc
CCFLAGS=-Wall
CLEAN=rm -f *.o 
PROGRAM_NAME=main
$(PROGRAM_NAME): main.o libsyn.a
	$(CC) $(CCFLAGS) $^ -o $@ -L. -lsyn
main.o: main.c 
	$(CC) $(CCFLAGS) -c $^
libsyn.a: M_syn.o
	ar rcs $@ $^
M_syn.o: M_syn.c
	$(CC) $(CCFLAGS) -c $^
clean:
	$(CLEAN)
	rm -f *~
	rm $(PROGRAM_NAME)

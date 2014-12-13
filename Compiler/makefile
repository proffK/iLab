CC=gcc
CCFLAGS=-Wall
CLEAN=rm -f *.o 
PROGRAM_NAME=mylc
$(PROGRAM_NAME): main.o libsyn.a 
	$(CC) $(CCFLAGS) $^  -o $@ -L. -lsyn
main.o: main.c
	$(CC) $(CCFLAGS) -c $< 
libsyn.a: M_lex.o M_tree.o M_syn.o M_sem.o
	ar rcs $@ $^
M_syn.o: M_syn.c 
	$(CC) $(CCFLAGS) -c $< 
M_tree.o: M_tree.c
	$(CC) $(CCFLAGS) -c $<
M_lex.o: M_lex.c
	$(CC) $(CCFLAGS) -c $<
M_sem.o: M_sem.c
	$(CC) $(CCFLAGS) -c $<
clean:
	$(CLEAN)

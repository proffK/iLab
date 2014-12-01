CC=gcc
CCFLAGS=-Wall
CLEAN=rm -f *.o 
PROGRAM_NAME=KKvirtmach
$(PROGRAM_NAME): KKvirtmach.o libstack.a libstk_processors.a 
	$(CC) $(CCFLAGS) $^  -o $@ -L. -lstk_processors -lstack -lm
KKvirtmach.o: KKvirtmach.c
	$(CC) $(CCFLAGS) -c $< 
libstk_processors.a: stk_processors.o
	ar rcs $@ $<
stk_processors.o: stk_processors.c 
	$(CC) $(CCFLAGS) -c $<
libstack.a: m_stack.o
	ar rcs $@ $<
mystack.o: m_stack.c
	$(CC) $(CCFLAGS) -c $<
My_assembler: My_assebmbler.o
	$(CC) $(CCFLAGS) $< -o $@
My_assembler.o: Myassembler.c
	$(CC) $(CCFLAGS) -c $<
My_asm: My_asm.o libstack.a
	$(CC) $(CCFLAGS) $< -o $@ -L. -lstack
My_asm.o: My_asm.c
	$(CC) $(CCFLAGS) -c $<
clean:
	$(CLEAN)

KKvirtmach: KKvirtmach.o libstack.a libstk_processors.a 
	gcc KKvirtmach.o -o $@ -L. -lstk_processors -lstack -lm
KKvirtmach.o: KKvirtmach.c
	gcc -c $< 
libstk_processors.a: stk_processors.o
	ar rcs $@ $<
stk_processors.o: stk_processors.c 
	gcc -Wall -c $<
libstack.a: m_stack.o
	ar rcs $@ $<
mystack.o: m_stack.c
	gcc -Wall -c $<
My_assembler: My_assebmbler.o
	gcc $< -o $@
My_assembler.o: Myassembler.c
	gcc -Wall -c $<
My_asm: My_asm.o libstack.a
	gcc $< -o $@ -L. -lstack
My_asm.o: My_asm.c
	gcc -Wall -c $<
clean:
	rm -f *.o
sort: main.o libM_Sort.a
	gcc $< -o $@ -L. -lM_Sort
main.o: main.c
	gcc -c -Wall $< 
libM_Sort.a: M_Sort.o
	ar rcs $@ $<
M_Sort.o: M_Sort.c
	gcc -Wall -c $<
clean:
	rm -f *.o

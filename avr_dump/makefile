CC=gcc
CCFLAGS=-Wall -c
AR=ar
ARFLAGS=rcs
PROG_NAME=avrdump

$(PROG_NAME): main.o libIntelHex2bin.a
	$(CC) $< -o $@ -L. -lIntelHex2bin
main.o: main.c
	$(CC) $(CCFLAGS) $< 
libIntelHex2bin.a: IntelHex2bin.o
	$(AR) $(ARFLAGS) $@ $<
IntelHex2bin.o: IntelHex2bin.c
	$(CC) $(CCFLAGS) $<




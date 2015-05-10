#ifndef _INTELHEX2DUMP_
#define _INTELHEX2DUMP_
#include <stdio.h>

typedef unsigned char byte;

int intel_hex2bin(char* inp_buf, byte* out_buf, int* inp_buf_size);

byte str_hex2byte(char* cur_num);

byte chk_sum(byte* first_byte, int sum_size);

byte char2hex(char inp);

int bin2intel_hex(byte* inp_buf, char* out_buf, int* inp_buf_size);

int bin_dump(byte* buf, unsigned long size, FILE* out);

#endif

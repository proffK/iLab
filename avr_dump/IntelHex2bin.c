#include "intel_hex2bin.h"
#include <stdio.h>

const char* first_hex_str = ":020000020000FC";

const int first_hex_str_size = 17;

const char* end_hex_str = ":00000001FF";

const int end_hex_str_size = 13;

enum intel_hex2bin_errno {
    CONV_OK,
    WRONG_SUM,
    INCORRECT_FORMAT,
    INCORRECT_CHAR
};

int intel_hex2bin_errno;

#define CONV_ERR(err)  intel_hex2bin_errno = err

int intel_hex2bin(char* inp_buf, byte* out_buf, int* inp_buf_size){
    
    #define ERR_LINE cur_char - inp_buf
    
    char* cur_char = inp_buf;
    byte data_counter = 0;
    byte sum = 0;
    int i = 0;

    cur_char += first_hex_str_size;
    CONV_ERR(CONV_OK);

    while (i < *inp_buf_size){
        int j = 0;
        if (*cur_char != ':'){
            CONV_ERR(INCORRECT_FORMAT);
            return ERR_LINE;
        }
        
        ++cur_char;
        data_counter = str_hex2byte(cur_char);
        //printf("%d\n", data_counter);

        if (data_counter == 0){
            *inp_buf_size = i + 1;
            return 0;
        }
        
        cur_char += 8; /* check !*/ 
        j = data_counter;
        
        while (j--){
            out_buf[i] = str_hex2byte(cur_char);
            ++i;
            cur_char += 2;
        }
       // printf("\n%d\n", out_buf + i - data_counter);
        sum = (byte) ((int) chk_sum(out_buf + i - data_counter, data_counter)
                      + (i - 1) / 256 + i % 256);

            //printf("@%X %d\n", (byte) (sum), i);
        if ((byte) (0 - sum) != str_hex2byte(cur_char)){
            //printf("@%X %d\n", (byte) (0 - sum), i);
            CONV_ERR(WRONG_SUM);   
            return ERR_LINE;
        }

        cur_char += 3;

        if (*cur_char != '\n'){
           // printf("!%d\n", *cur_char);
            CONV_ERR(INCORRECT_FORMAT);
            return ERR_LINE;
        }

        ++cur_char;
    }
    
    CONV_ERR(INCORRECT_FORMAT);

    return ERR_LINE;

    #undef ERR_LINE

}

byte str_hex2byte(char* cur_num){

    return char2hex(cur_num[0]) * 16 + char2hex(cur_num[1]);
    
}

byte char2hex(char inp){

    if ('0' <= inp && inp <= '9') return (inp - '0');

    if ('A' <= inp && inp <= 'F') return (inp - 'A' + 10);
    
    CONV_ERR(INCORRECT_CHAR);

    return 255;

}

byte chk_sum(byte* first_byte, int sum_size){

    byte sum = 0;

    while (sum_size--){
       sum += *(first_byte++);
       //printf("%X ", *first_byte);
    }

    return sum;

}

int bin_dump(byte* buf, unsigned long size, FILE* out){
    
   int i = 0;

   for (i = 0; i < size; ++i){ 
        
        if (i % 10 == 0) fprintf(out, "\n%04d:", i);

        fprintf(out, "%02X ", buf[i]);
        
   }

   return 0;
}
#undef CONV_ERR

int bin2intel_hex(byte* inp_buf, char* out_buf, int* inp_buf_size){

    int i = 0;

#include <stdio.h>
#include <stdlib.h>
#include "intel_hex2bin.h"

int main(int argc, char* argv[]){
    FILE* inp_file;
    char* inp_buf = NULL;
    int inp_buf_size = 0;
    int out_buf_size = 0;
    int Hex_error_line = 0;
    byte* out_buf = NULL;

    if (argc == 0){
        printf("Too few arguments\n");
        return 1;
    }
    
    inp_file = fopen(argv[1], "rb");

    if (inp_file == NULL){
        printf("Can't open file\n");
        return 3;
    }
    fseek(inp_file, 0, SEEK_END);
    inp_buf_size = ftell(inp_file);

    if (inp_buf_size <= 0) {
        printf("Incorrect file\n");
        return 2;
    }

    inp_buf = (char*) calloc (inp_buf_size, sizeof(char));

    if (inp_buf == NULL){
        printf("No memory\n");
        return 4;
    }
    
    rewind(inp_file);

    if (inp_buf_size > fread(inp_buf, sizeof(char), inp_buf_size, inp_file)){
            printf("Incorrect file\n");
            return 2;
    }

    printf("%d\n", inp_buf_size);
    out_buf_size = inp_buf_size;
    out_buf = (unsigned char*) calloc (out_buf_size, sizeof(unsigned char)); 

    if (out_buf == NULL){
        printf("No memory\n");
        return 4;
    }
    
    Hex_error_line = intel_hex2bin(inp_buf, out_buf, &out_buf_size);
    printf("%d\n", out_buf_size);
    bin_dump(out_buf, out_buf_size, stdout);
    
    return 0;
}

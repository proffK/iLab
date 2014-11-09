#include <stdio.h>
#include <stdlib.h>
#include "stk_processors.h"
#include "resourses.h"
#include <assert.h>

int main(int argc, char* argv[]){
	FILE* firmware_file = 0;
	double* firmware = 0;
	long firmware_size = 0;
	char sign[2] ={};
	
	processor* proc = processor_create(PROCESSOR_STACK_SIZE,NUMBER_OF_REGISTORS,\
	PROCESSOR_MEMORY);
	
	assert(proc);
	
	firmware = (double*) calloc (MAX_BYTE_CODE_SIZE, sizeof(double));

	assert(firmware);
	
	firmware_file = fopen(argv[1], "rb");
	
	fread(sign, sizeof(char), 2, firmware_file);
	
	if (sign[0] != 'k' || sign[1] != 'k') {
		processor_delete(proc);
		free(firmware);
		printf("Incorrect firmware sign\n");
		return 0;
	}
	
	firmware_size = fread(firmware, sizeof(double), MAX_BYTE_CODE_SIZE, firmware_file);

	processor_flash(proc, firmware, firmware_size);	

	processor_start(proc, stdin, stdout);

	processor_delete(proc);

	free(firmware);
	return 0;
}
	
	
	
	
 

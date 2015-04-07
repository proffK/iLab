#include <stdio.h>

unsigned int hash3(char* str);
unsigned int old_hash3(char* str);

int main(){
	
	char* str = "hash";
	
	printf("%d\n", hash3(str));
	printf("%d\n", old_hash3(str));
	return 0;
	
}
unsigned int old_hash3(char* str){
	
	register unsigned int rezult = 0;
	
    if (*str == '\0')  return 0;
    
    if (*(str + 1) == '\0') return (unsigned char) *str;
    
    rezult = old_hash3(str + 1);
    
    return ((rezult << 1) | ((rezult & 1) >> (sizeof(rezult) - 1))) ^ 
			(unsigned char)(*str);

}

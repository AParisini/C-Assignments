#include "mstring.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void strrev(char* str){
char temp;
	
	    for(int i = 0; i < strlen(str)/2; i++){
	 
	    temp = str[strlen(str) - 1 - i];
		str[strlen(str) -1 -i] = str[i];
		str[i] = temp;
	    
	    }

}
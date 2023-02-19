/**
 * Andrew Parisini - Principi
 * B00805414
 * CSCI 3120 
 * 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {

    FILE *file;
    char fileName[25]="Output.txt";

    file = fopen(fileName,"w");	
    if(file == NULL){
        printf("Error in opening file!");
        exit(1);
    }

    printf("Please Enter Your Sentence \n"); 
    char string[1000]; 
    char toPrint[1000];
    int i = 0; 

    fgets(string, 1000, stdin);
     
    strncpy(toPrint, string, 1000);  

    while(toPrint[i] != '\0'){ 
        if(toPrint[i] == ' '){ 
            printf("\n");
            fprintf(file,"\n",toPrint[i]);
        }
        else{
            printf("%c",toPrint[i]); 
            fprintf(file,"%c",toPrint[i]);
        }
        i++; 
    }     
    
    fclose(file);
    return 0;
}


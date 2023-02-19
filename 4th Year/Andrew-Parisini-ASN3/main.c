#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

/**
 * Helper function to keep array data (used for main Runner Function)
*/
void *runner(void *param); 
int arrayLength, lengthArray;
int *array;

FILE *fptr;  

/**
 * File Reader - Reads the file and enters the data into a Integer Array
*/
int *fileReader() {

    int bufsize = lengthArray;
    int integer;
    int index = 0;
    int *input = malloc(bufsize*sizeof(int));

    char data[501];
    char c;
    int length = 0;

    fptr = fopen("IntegerList.txt", "r");
    if (fptr == NULL){
        printf("Error!\n");
        return 0;
    }
    // Read file and put data into a char array (To be tokenized)
    int x = 0;
    while((c = getc(fptr)) != EOF){
        data[x] = c;
        x++;               
    }
    
    //Tokenize newly created data - Plug into array as integers
    char *tokenComplete = strtok(data, ",");    
    while( tokenComplete != NULL ) {        
        int value = atoi(tokenComplete);
        input[length] = value;        
        length++;
        arrayLength++;
        tokenComplete = strtok(NULL, ",");
    }   
    fclose(fptr);     
    return input;
}

/**
 * Reads the file and creates a count for parameter thread use
*/
int lengthOfArray() {
    
    fptr = fopen("IntegerList.txt", "r");
    char data[501];
    char c;
    int length = 0;

    if (fptr == NULL){
        printf("Error!\n");
        return 0;
    }
    // Read file and put data into a char array (To be tokenized)
    int x = 0;
    while((c = getc(fptr)) != EOF){
        data[x] = c;
        x++;                
    }

    //Element count
    char *token = strtok(data, ",");
    while( token != NULL ) {        
        int value = atoi(token);              
        length++;        
        token = strtok(NULL, ",");
    }  
    fclose(fptr);  
    return length;
}

/**
 * Merges the array by creating two sub arrays, dividing initial array, then merging while keeping elements in order
 * SanFoundry Method 3
 * URL: https://www.sanfoundry.com/c-program-merge-sorted-array/
 * Data Accessed: 2022-11-16
*/
void Merger(int array[], int left, int middle, int right) {
    
    int i, j, k;
    int leftHalfArray = middle - left + 1;
    int rightHalfArray = right - middle;

    //Temporary Arrays
    int first[leftHalfArray], second[rightHalfArray]; 

    for (i = 0; i < leftHalfArray; i++) {
        first[i] = array[left + i];
    }

    for (j = 0; j < rightHalfArray; j++) {
        second[j] = array[middle + 1 + j];
    }
    
    i = 0;
    j = 0;
    k = left;

    while (i < leftHalfArray && j < rightHalfArray) {        
        if (first[i] <= second[j]) {
            array[k] = first[i];
            i++;
        } else {
            array[k] = second[j];
            j++;
        }
        k++;
    }

    while (i < leftHalfArray) {
        array[k] = first[i];
        i++;
        k++;
    }
    while (j < rightHalfArray) {
        array[k] = second[j];
        j++;
        k++;
    }
}

/**
 * Semi-Recursive approach to Sorting and Merging
*/
void Sorter(int array[], int left, int right) {
    if (left < right) {
        int middle = (left + (right - 1)) / 2;
        Sorter(array, left, middle);
        Sorter(array, middle + 1, right);
        Merger(array, left, middle, right);
    }
}

int main(int argc, char *argv[]){

    //(Storing relevant information) This will save to the global parameters
    lengthArray = lengthOfArray();
    array = fileReader();

    //Create Threads
    pthread_t tid; 
    pthread_attr_t attr; 
    
    pthread_t tid2; 
    pthread_attr_t attr2; 
   
    pthread_t tid3; 
    pthread_attr_t attr3;    

    //Create & Run Threads in order ===========================================

    char *thread_no = "Left Half Sort";    
    pthread_attr_init(&attr); 
    pthread_create(&tid,&attr,runner, thread_no);     
    
    char *thread2 = "Right Half Sort";
    pthread_attr_init(&attr2);
    pthread_create(&tid2,&attr2, runner, thread2);    
    
    char *thread3 = "Merge";
    pthread_attr_init(&attr3);
    pthread_create(&tid3, &attr2, runner, thread3);

    pthread_join(tid, NULL);
    pthread_join(tid2, NULL);
    pthread_join(tid3, NULL); 

    // ========================================================================

    //Print out to SortedIntegerList.txt    

    FILE *fileWrite;
    char fileName[501]="SortedIntegerList.txt";

    fileWrite = fopen(fileName,"w");	
    if(fileWrite == NULL){
        printf("Error in opening file!");
        exit(1);
    }
  
    for (int j = 0; j < arrayLength; j++) {
        if (j == arrayLength - 1) {
            fprintf(fileWrite,"%d",array[j]);
            } 
            else {
            fprintf(fileWrite,"%d,",array[j]);
        }
    } 
    
    fclose(fileWrite);
    pthread_exit(0);    
    
    return 0;
}

/**
 * Runner Function - uses the initial function Runner(At top) to setup parameters used
 * Depending on title of thread (String) - the thread gets sent to the correct function
*/
void *runner(void *param){

    int midpoint = arrayLength/2;
    if (strcmp(param, "Left Half Sort") == 0) {
        Sorter(array, 0, midpoint);
    }
    if (strcmp(param, "Right Half Sort") == 0) {
        Sorter(array, midpoint + 1, arrayLength - 1);
    }
    if (strcmp(param, "Merge") == 0) {
        Merger(array, 0, (arrayLength/2), arrayLength - 1);
    }

    //Exit thread with successful exit code
    pthread_exit(0);
}
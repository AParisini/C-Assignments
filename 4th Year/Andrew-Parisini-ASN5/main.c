#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>


typedef int buffer_item;
#define BUFFER_SIZE 5

buffer_item buffer[BUFFER_SIZE];
pthread_mutex_t mutex;
sem_t full, empty;
int bufferCount, insert, out;

int insert_item(buffer_item item);
int remove_item(buffer_item *item);
void *consumer(void *param);
void *producer(void *param);

int producerID = 0;
int consumerID = 0;

int main(int argc, char **argv){

  // 1. Get command-line arguments argv[1],argv[2],argv[3]

    if (argv[1] == NULL || argv[2] == NULL || argv[3] == NULL) {
        printf("Enter 3 arguments: sleep time, number of producers, number of consumers. Restart Program Manually\n");
        return -1;
    }

  const long int sleepTime = strtol(argv[1], NULL, 0);
  const long int numberOfProducers = strtol(argv[2], NULL, 0);
  const long int numberOfConsumers = strtol(argv[3], NULL, 0);

    // 2. Initialize semaphores and mutex lock
    
    int i;
    srand(time(NULL));
    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty, 0, BUFFER_SIZE); 
    sem_init(&full, 0, 0);
    bufferCount = insert = out = 0;


    // 3. Initialize buffer
    for(int x = 0; x < 5; x++)
        buffer[x] = -1;
    
    pthread_t producerThreads[numberOfProducers];
    pthread_t cosnumerThreads[numberOfConsumers];

    // 4. Create producer thread(s)
    for(i = 0; i < numberOfProducers; i++)
        pthread_create(&producerThreads[i], NULL, producer, NULL);

    // 5. Create consumer thread(s)
    for(i = 0; i < numberOfConsumers; i++)
        pthread_create(&cosnumerThreads[i], NULL, consumer, NULL);

    // 6. Sleep and thereafter terminate the C program    
    sleep(sleepTime);
    return 0;
}

/**
 *Insert Item: Inserts item into buffer - If successful, will return 0 
*/ 
int insert_item(buffer_item item){

    int result;
    sem_wait(&empty);

    pthread_mutex_lock(&mutex);

    if(bufferCount != BUFFER_SIZE){
        buffer[insert] = item;
        insert = (insert + 1) % BUFFER_SIZE;
        bufferCount++;
        result = insert;
    }
    else
        result = -1;

    pthread_mutex_unlock(&mutex);
    sem_post(&full);

    return result;
}

/**
 *Removes Item: Removes item from buffer - If successful, will return 0 
*/ 
int remove_item(buffer_item *item){

    int result;
    sem_wait(&full);

    pthread_mutex_lock(&mutex);

    if( bufferCount != 0){
        *item = buffer[out];
        out = (out + 1) % BUFFER_SIZE;
        bufferCount--;
        buffer[out] = -1;
        result = out;
    }
    else
        result = -1;

    pthread_mutex_unlock(&mutex);
    sem_post(&empty);

    return result;
}

/**
 * Producer sleeps for a random perios of time: 0-4 seconds, Generates a random item, then tries to insert item into buffer through insert_item
*/
void *producer(void *param){
    buffer_item item;
    int index;
    while(1){
        sleep(rand() % 5 + 1); 

    item = rand();

    index = insert_item(item);
    printf("Producer %d produced item %d into buffer[%d]\n", producerID, item, index);
    producerID++;
    }  
}

/**
 * Consumer sleeps for a random perios of time: 0-4 seconds, then tries to remove item from the buffer through remove_item 
*/
void *consumer(void *param){
    buffer_item item;
    int index;
    while(1){
        sleep(rand() % 5 + 1); 

    index = remove_item(&item);
    printf("Consumer %d consumed item %d into buffer[%d]\n", consumerID, item, index);
    consumerID++;
    }  
}
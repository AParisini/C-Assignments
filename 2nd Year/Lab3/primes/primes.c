#include "primes.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "mmath.h"

void primes(long num){

    while(num%2 == 0){

        printf("%d ", 2);
        num = num/2;
    }

    for(int index = 3; index <= sqrt(num); index = index + 2){

        while(num % index == 0){
            printf("%d ", index);
            num = num/index;
        }
    }

    if(num > 2){
        printf("%d", num);
    }

    printf("\n");

}




#include "pascal.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "mmath.h"

void pascal (int num){

    int x  = 1;
    for(int i = 1; i <= num + 1; i++){

        printf("%d ", x);
        x = x * (num + 1 - i)/i;
    }

    printf("\n");

}






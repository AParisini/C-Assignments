#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "power.h"

/*
Description: Methods follow the power rule to print out the appriopate result. 
Author: Andrew Parisini - Principi
Date: 2022-01-18
*/

void powerRule4(int a, int b, int c, int d, int e){

    int firstCoefficent = a *4;
    
    int secondCoefficent = b *3;
    
    int thirdCoefficent = c *2;
    
    int fourthCoefficent = d *1;
    
    printf("%dx^3 + %dx^2 + %dx + %d\n", firstCoefficent, secondCoefficent, thirdCoefficent, fourthCoefficent);

}

void powerRule3(int a, int b, int c, int d){

    int firstCoefficent = a *3;
    
    int secondCoefficent = b *2;
    
    int thirdCoefficent = c *1;  

    printf("%dx^2 + %dx + %d\n", firstCoefficent, secondCoefficent, thirdCoefficent);

}

void powerRule2(int a, int b, int c){

    int firstCoefficent = a *2;
    
    int secondCoefficent = b *1;   
    
    printf("%dx + %d\n", firstCoefficent, secondCoefficent);

}

void powerRule1(int a, int b){

    int firstCoefficent = a ;   
    
    printf("%d\n", firstCoefficent);

}



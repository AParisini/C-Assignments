#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "coins.h"

int main(){

    int amount;
    scanf("%d ", &amount);   

    calculateCoins(1850);

    return 0;
}

void calculateCoins(int amount){

    int dollars = 0;
    int quarters = 0;
    int dimes  = 0;
    int nickels = 0;
    int pennies = 0;


    dollars             = floor(amount/100);
    int reductionDollars    = dollars * 100;
    amount              = amount - reductionDollars;

    quarters            = floor(amount/25);
    int reductionQuarters    = quarters * 25;
    amount              = amount - reductionQuarters;

    dimes             = floor(amount/10);
    int reductionDimes    = dimes * 10;
    amount              = amount - reductionDimes;

    nickels             = floor(amount/5);
    int reductionNickels    = nickels * 5;
    amount              = amount - reductionNickels;

    pennies = amount;

    printf("%d dollars, %d quarters, %d dimes, %d nickels, %d pennies", dollars, quarters, dimes, pennies);

}
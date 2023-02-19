#include "triangle.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
Description: Methods find missing angles - first three methods use Pythagorean Theory, and last three use trigonometry, and showResults prints the dataof all sides and angles. 
Author: Andrew Parisini - Principi
Date: 2022-01-18
*/

void showResults(double a, double b, double c, double x, double y){

    printf("\nopposite = %.2lf\nadjacent = %.2lf\nhypotenuse = %.2lf\nx = %.2lf\ny = %.2lf\n\n", a, b, c, x , y);
}

double findOppositePyth(double b, double c, double x, double y){

    double hyp = pow(c,2);
    double adj = pow(b,2);

    double oppSquare = hyp - adj;
    double a = sqrt(oppSquare);

    showResults(a,b,c,x,y);

    return a;
}

double findAdjacentPyth(double a, double c, double x, double y){

    double hyp = pow(c,2);
    double opp = pow(a,2);

    double adjSquare = hyp - opp;
    double b = sqrt(adjSquare);

    showResults(a,b,c,x,y);

    return b;
}

double findHypotenusePyth(double a, double b, double x, double y){

    double opp = pow(a,2);
    double adj = pow(b,2);

    double hypSquare = opp + adj;
    double c = sqrt(hypSquare);

    showResults(a,b,c,x,y);

    return c;
}

double findOppositeTrig(double b, double c, double x, double y){

    double a = c * cos(y);

    showResults(a,b,c,x,y);

    return a;
}

double findAdjacentTrig(double a, double c, double x, double y){

    double b = c*sin(y);

    showResults(a,b,c,x,y);

    return b;
}

double findHypotenuseTrig(double a, double b, double x, double y){

    double c = a/sin(x);

    showResults(a,b,c,x,y);

    return c;
}


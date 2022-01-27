#include "mmath.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//All functions are pretty trivial, (theres only one fast and efficent way to do them). In accordance with regulation and to avoid 
//an AIO infraction, the functions which I took / followed have been cited

/*
    URL: https://www.javatpoint.com/factorial-program-in-c
    Date Accessed: 2022-01-25
*/
long fact(int num){

    long factorial = 1;

	for(int i = 1; i <=  num; i++){

		factorial = factorial * i;
	} 
	
	return factorial;
}

long nchoosek(int n, int k){

    long nFact = fact(n);
	long kFact = fact(k);

	//  (N! - K!)
	long x = nFact/kFact;
	long y = x / fact(n - k);
		          
		   
	return y;


}

/*
    URL: https://www.programiz.com/c-programming/examples/prime-number
    Date Accessed: 2022-01-25
*/
int prime(long num){

    if(num < 2){
        return 0;
    }

    for (int i = 2; i <= num/2 ; i++){

        if(num % i){
            return 0;
        }
    }
    return 1;  
    
}

/*
    URL: https://www.programiz.com/c-programming/examples/hcf-gcd
    Date Accessed: 2022-01-25
*/
int gcd(int n, int k){

    if(n == 0 || k == 0){
        return 0;
    }

    if(n == k){
        return n;
    }

    if(n > k){
        return gcd(n-k,k);

    }
    else{
        return gcd(n,k-n);
    }
}

/*
    URL: https://www.javatpoint.com/lcm-of-two-numbers-in-c
    Date Accessed: 2022-01-25
*/
int lcm(int n, int k){

    int max = (n > k) ? n : k;

    //boolean int 
    int found = 0;

    while(found == 0){

        if(max % n == 0 && max % k == 0){

            found = 1;
        }

        else{
            max++;
        }
    } 

    return max;
}

char bitrevc(char b) {

    char reversed = 0;

	for (int i = 0; i < sizeof(b) * 8; i++){
		
		if(b & (1 << i)){
			reversed |= (1 << ((sizeof(b)*8) - 1- i));
		}
	 } 

    return b;
}


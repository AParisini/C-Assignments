#include "adjmult.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mmath.h"

int largestProduct(){

	int max = 0;
	int product = 0;
	int matrix[20][20];

	for(int a = 0; a < 20; a++){
		for(int b = 0; b < 20; b++){

			scanf("%d", &matrix[a][b]);
		}
	}

	//Modular Algorithim, checks i and j for direction of product. Checks if resulting product is 
	//greater or equal to max int.
	
	
	for(int i = 0; i < 20; i++){
	        for(int j = 0; j < 20; j++){

			    product  = 0; //Refresh of product after previous loop
	
	            //Vertical (Up) Product
	
	            if(j > 2){

	            	product = matrix[i][j] * matrix[i][j - 1] * matrix[i][j - 2] * matrix[i][j - 3];

	             	if(product >= max){
	            		max = product;
	            	}
	            }
	            //Vertical (Down) Product
	
	            if(j < 17){
	
	                product = matrix[i][j] * matrix[i ][j+ 1] * matrix[i ][ j + 2] * matrix[i][j + 3];

	                if(product >= max ){
	                    max = product;
	            	}
	            }

	            //Horizontal (Left) Product
	
	            if(i > 2 ){

	                product = matrix[i][j] * matrix[i - 1][j ] * matrix[i - 2][j ] * matrix[i - 3][j ];

	                if(product >= max ){
	        	        max = product;
	        	    }    
	            }

	            //Horizontal (Right) Product
	
	            if(i < 17){

                    product = matrix[i][j] * matrix[i + 1][j] * matrix[i + 2][j] * matrix[i + 3][j];

                    if(product >= max ){
	        	        max = product;
	        	    }                
                }

	            //Diagonals
	
	            //Up Right Product
	
	            if(j > 2 && i < 17){

	                product = matrix[i][j] * matrix[i + 1][j - 1] * matrix[i + 2][j -2] * matrix[i + 3][j - 3];

	                if(product >= max ){
		                max = product;
	                }			               
	            }

	            //Up Left Product
	
	
	            if(j > 2 && i > 2){

	               product = matrix[i][j] * matrix[i - 1][j - 1] * matrix[i - 2][j - 2] * matrix[i - 3][j - 3];

	                if(product >= max ){
	                    max = product;
	                }						               
	            }

	            //Down Right Product
	
	
	            if(j < 17 && i < 17){

                        product = matrix[i][j] * matrix[i + 1][j + 1] * matrix[i + 2][j + 2] * matrix[i + 3][j + 3];

	                    if(product >= max ){
	                        max = product;
	                    }						             
	            }

	        //Down Left Product
	
	
	        if(j < 17 && i > 2){

	            product = matrix[i][j] * matrix[i - 1][j + 1] * matrix[i - 2][j + 2] * matrix[i - 3][j + 3];

	            if(product >= max ){
	                max = product;
	            }
					              
            }
		}
	}
	return max;
}

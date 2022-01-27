#include "codes.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "mstring.h"

/*
1. Reverse the character’s binary representation.
2. Convert the reversed character to an integer.
3. Left shift the integer an amount equal to the start value.
4. Right shift the integer an amount equal to the offset value.
5. Return the resultant integer.
*/

int encrypt(int startLocation, int offset, char toBeEncrypt){

    char encrypted = bitrevc(toBeEncrypt);

    int encryptedInt = (int) encrypted;

    int encryptedIntLeftShifted = encryptedInt << startLocation;

    int encryptedIntRightShifted = encryptedIntLeftShifted >> offset;

    return encryptedIntRightShifted;
}

char decrypt(int startLocation, int offset,int toDecrypt){

    int decryptedLeftShifted = toDecrypt << offset;

    int decryptedRightShifted = decryptedLeftShifted >> startLocation;

    char decrypted = (char)decryptedRightShifted;

    decrypted = bitrevc(decrypted);

    return decrypted;
}
// file is simulator_helper_functions.c
// purpose: implementation of helper function for simulator_main.c
// revision:
// Initial code - Boris Zugic
/***************************************************/

// INCLUDE FILES
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "simulator_helper_functions.h"

/***************************************************/

// DEFINE / MACROS

/***************************************************/
/* setSensorFunctionBits(int sensorFunction, unsigned short* heartRate)

    purpose: set bits 0-1 of heartRate based on sensorFunction value

    parameters:
        int sensorFunction - indicates whether the heart rate device is functioning properly
        unsigned short* heartRate - output variable

    output: 
        unsigned short* heartRate with bits 0-1 set accordingly

    return:
        0 if sensorFunction is 0
        1 if sensorFunction is 1

*/
int setSensorFunctionBitsHR(int sensorFunction, unsigned short* heartRate){

    if (sensorFunction == 1)
    {
		*(heartRate) |= (1 << 1);
        return 1;
    }
    
    return 0;

}

int setHeartRateBits(int heartrate, unsigned short* heartRate){

    *(heartRate) |= (heartrate << 3);


    return 0;
}

/************* int computeParityBitShort(unsigned short* num) ************
 * 
 * purpose: computes parity bit of 16-bit int
 * 
 * input: 
 * num - number to compute parity bit of
 * 
 * output: 
 * num with correct parity bit
 * 
 * return: 
 * 0 if parity bit = 0
 * 1 if parity bit = 1
*/
int computeParityBitShort(unsigned short* heartRate){

    unsigned char numOfSetBits = 0;
    // iterate through first 14 bits (16th bit is parity bit, 14th and 15th are 0's)
    for (int i = 0 ; i < 14 ; i++)
    {
        if (1 << i & *(heartRate))
        {
            numOfSetBits++;
        }
    }

    // if numOfSetBits is odd, set MSB to 1
    if (numOfSetBits % 2)
    {
        *(heartRate) |= (1 << 15);
        return 1;
    }

    return 0;
}

int setBitShort(unsigned short* inputNum, int bitNum){

    *(inputNum) |= (1 << bitNum);

    return 0;
}

int setBitInt(unsigned int* inputNum, int bitNum){

    *(inputNum) |= (1 << bitNum);

    return 0;
}

/* setHighLowBits(int heartrate, unsigned short* heartRate)

    purpose: sets bits 11 and 12 if heartrate is high, sets bit 12 if heartrate is low 

    parameters:
        int heartrate
        unsigned short* heartRate - output variable

    output: 
        unsigned short* heartRate with bits 11-12 set accordingly

    return:
        0 if heartrate is normal
        2 if heartrate is low
        3 if heartrate is high

*/
int setHighLowBitsHR(int heartrate, unsigned short* heartRate){

    if (heartrate > 165)
    {
        setBitShort(heartRate, 12);

        return 2;
    }
    else
    {
        if (heartrate < 50)
        {
            setBitShort(heartRate, 11);
            setBitShort(heartRate, 12);

            return 3;
        }
    }

    return 0;
}


int setDiastolicPressureBits(int diastolicPressure, unsigned int* bloodPressure)
{
   
     *(bloodPressure) |= (diastolicPressure << 3);

     return 0;

}

int setSystolicPressureBits(int systolicPressure, unsigned int* bloodPressure)
{

    *(bloodPressure) |= (systolicPressure << 11);

    return 0;

}

/*setHighLowBitsBP

purpose: helper function used to set bits 19-20 of bloodPressure indicating whether the blood pressure is low, high, normal or abnormal

output: bloodPressure with bits 19-20 set accordingly, unless abnormal blood pressure

return:

- 0 if successful
- 1 if abnormal blood pressure
- 2 if low blood pressure
- 3 if high blood pressure

*/
int setHighLowBitsBP(int diastolicPressure, int systolicPressure, unsigned int* bloodPressure)
{

    // case 1: abnormal blood pressure
    // set bit values to 3
    if (diastolicPressure < 55 || systolicPressure >= 170)
    {
        // set bit values to 3
        setBitInt(bloodPressure, 20);
        setBitInt(bloodPressure, 19);

        return 3;
    }


    // case 2: low blood pressure
    // set bit values to 1
     if (diastolicPressure <= 75 || systolicPressure <= 100)
    {
        
        setBitInt(bloodPressure, 19);
        
        return 1;
    }
    
    // case 3: high blood pressure
    // set bit values to 2
    else
    {
        if(diastolicPressure >= 100 || systolicPressure >= 130)
        {
          
            setBitInt(bloodPressure, 20);

            return 2;
        }
    }

    return 0;
}

int setSensorFunctionBitsBP(int sensorFunction, unsigned int* bloodPressure){
 
    if (sensorFunction == 1)
    {
		*(bloodPressure) |= (1 << 1);
        return 1;
    }
   
    return 0; 
}


/************* int computeParityBitInt(unsigned int* num) ************
 * 
 * purpose: computes parity bit of 32-bit int
 * 
 * input: 
 * num - number to compute parity bit of
 * 
 * output: 
 * num with correct parity bit
 * 
 * return: 
 * 0 if parity bit = 0
 * 1 if parity bit = 1
*/
int computeParityBitInt(unsigned int* num){
    
    unsigned char numOfSetBits = 0;
    
    // iterate through first 21 bits and count 1's
    for (int i = 0 ; i < 22 ; i++)
    {
        if (1 << i & *(num))
        {
            numOfSetBits++;
        }
    }

    // if num of 1's is odd, set MSB to 1
    if (numOfSetBits % 2)
    {
        *(num) |= (1 << 31);
        return 1;
    }

    return 0;
}


int readHeartRate(unsigned short heartRate)
{
    return ((1 << 8) - 1) & (heartRate >> (4 - 1));
}


int checkParityBitHR(unsigned short heartRate)
{
    unsigned char numBits = 0;

    for (int i = 0 ; i < 14 ; i++)
    {

       if (1 << i & heartRate)
        {
            numBits++;
        }

    }

    if (((numBits % 2) && ((1 << 15 & heartRate) == 0)) || ((numBits % 2 == 0) && (1 << 15 & heartRate)))
    {
        if (1 << 15 & heartRate)
        {
            printf("Error in data - parity bit. Parity bit = 1\n");
        }
        else
        {
            printf("Error in data - parity bit. Parity bit = 0\n");
        }

        return 1;
    }

     if (1 << 15 & heartRate)
        {
            printf("Parity bit is correct. Parity bit = 1\n");
        }
        else
        {
            printf("Parity bit is correct. Parity bit = 0\n");
        }

    return 0;
}

int checkParityBitBP(unsigned int bloodPressure)
{
    unsigned char numBits = 0;

    for (int i = 0 ; i < 21 ; i++)
    {

       if (1 << i & bloodPressure)
        {
            numBits++;
        }

    }

    if (((numBits % 2) && ((1 << 31 & bloodPressure) == 0)) || ((numBits % 2 == 0) && (1 << 31 & bloodPressure)))
    {
        if (1 << 31 & bloodPressure)
        {
            printf("Error in data - parity bit. Parity bit = 1\n");
        }
        else
        {
            printf("Error in data - parity bit. Parity bit = 0\n");
        }

        return 1;
    }

     if (1 << 31 & bloodPressure)
        {
            printf("Parity bit is correct. Parity bit = 1\n");
        }
        else
        {
            printf("Parity bit is correct. Parity bit = 0\n");
        }

    return 0;
}

int readDiastolicPressure(unsigned int bloodPressure)
{
    return ((1 << 8) - 1) & (bloodPressure >> (4 - 1));
}

int readSystolicPressure(unsigned int bloodPressure)
{
    return ((1 << 8) - 1) & (bloodPressure >> (12 - 1));
}


/****************computeFloatValue(unsigned short num)****************
 * purpose: computes decimal value of an 8 bit floating point representation
 * 
 * input: num whose first 8 bits are in floating point representation (1-3-4)
 * 
 * output: none
 * 
 * return: decimal value of num floating point representation
 * 
*/
float computeFloatValue(unsigned short num)
{

    unsigned char sign, mantissa;
    signed char exponent; 
    float result = 0;
    
    // extract MSB (sign)
    sign = (char)(1 << 7 & num);
    

    // extract bits 4-6
    exponent = ((1 << 3) - 1) & (num >> (5 - 1));
    
    // compute exponent 
    exponent -= 3;
    
    // extract mantissa (bits 0-3)
    mantissa = ((1 << 4) - 1) & (num >> (0));
    
    /******* CASE 1: NEGATIVE EXPONENT *******/
    if (exponent < 0)
    {
        // add assumed one
        mantissa |= 1 << 4;
    
        // iterate through len of mantissa + 1 number of bits (this num is always going to be 5)
        // starting from the rightmost bit
        for (int i = 0; i < 5 ; i++)
        {
            
            // if bit is set to 1
            if (1 << i & mantissa)
            {
                // add 2^-(index after dot starting at 1) to result
                // e.g. in 0.10001 index of rightmost bit is 5 so add to result 2^-(5) 
                result += pow(2, - 1 * ((4 - exponent) - i));
           
            }
        }
    }
    
    
     /******* CASE 2: NON-NEGATIVE EXPONENT *******/
    // in this case, we have to consider left and right side of dot 

    else 
    {
        // add assumed 1 in front of every number 
        // in this case, indexing starts at 0 from rightmost value before dot
        // index of MSB is always going to be value of exponent
        result += pow(2, exponent);
   
        int index = 3;
        // iterate through left side of dot excluding assumed 1 at front (first exponent number of bits of mantissa)
        for (int i = exponent - 1 ; i > -1 ; i--)
        {
            // if bit is 1, add 2^index to result
            if (1 << index-- & mantissa)
            {
                result += pow(2, i);
            }
        }

        // iterate through right side of dot (4 - exponent number of bits of mantissa)
        // indexing here follows same rules as in case 1
        index = -1;
        for (int i = 4 - exponent - 1 ; i > -1 ; i--)
        {
        
            // if bit is 1
            if (1 << i & mantissa)
            {
                // add bit * 2^index to result
                result += pow(2, index--);
            }
        
        
        }
    }


    // if MSB of mantissa is 1
    if (sign)
        // make result negative
        result *= -1;

    return result;

}


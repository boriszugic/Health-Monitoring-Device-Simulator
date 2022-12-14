/* file test.c

purpose: program for testing functions from files : simulator_prep_functions.c, simulator_helper_functions.c, simulator_presentation_functions.c

revision:
a. Boris Zugic - Initial code

*/

/***************************************************/

// INCLUDE FILES

#include <stdio.h>
#include <stdlib.h>
#include "simulator_prep_functions.h"
#include "simulator_presentation_functions.h"
#include "simulator_helper_functions.h"

/***************************************************/

// DEFINE / MACROS

/***************************************************/


int main(){

    unsigned short heartRate = 0;
    unsigned int bloodPressure = 0;
    // testing prepareHeartRate()
    // case 1: failure (return 1) and print error message
    printf("*****************************************************\nTesting prepareHeartRate\n\n");


    printf("1. prepareHeartRate(256, 0, )\nExpected return value: 1\nActual returned value: %d\n\n", prepareHeartRate(256, 0, &heartRate));
    // case 2: success (return 0)
    printf("\n2. prepareHeartRate(255, 0, )\nExpected return value: 0\nActual returned value: %d\n\n", prepareHeartRate(255, 0, &heartRate));
    printf("Value of heartRate should be (0)00(1 0)(111 1111 1)(100) = 6140 \nActual value: %d\n\n", heartRate);
    
    heartRate = 0;

    printf("\n3. prepareHeartRate(25, 1, )\nExpected return value: 0\nActual returned value: %d\n\n", prepareHeartRate(25, 1, &heartRate));
    printf("Value of heartRate should be (1)00(1 1)(000 1100 1)(110) = 39118 \nActual value: %d\n\n", heartRate);

    heartRate = 0;

    printf("\n4. prepareHeartRate(150, 1, )\nExpected return value: 0\nActual returned value: %d\n\n", prepareHeartRate(150, 1, &heartRate));
    printf("Value of heartRate should be (1)00(0 0)(100 1011 0)(010) = 33970 \nActual value: %d\n\n", heartRate);


    printf("*****************************************************\nTesting prepareBloodPressure\n\n");

    printf("1. prepareBloodPressure(0, 130, 150,  )\n");
    prepareBloodPressure(0, 130, 150, &bloodPressure);
    printf("Value of bloodPressure should be (0)000 0000 000(1 0)(100 0001 0)(100 1011 0)(100) = 1316020\nActual value: %u\n\n", bloodPressure);

    bloodPressure= 0;

    printf("2. prepareBloodPressure(0, 20, 100,  )\n");
    prepareBloodPressure(0, 20, 100, &bloodPressure);
    printf("Value of bloodPressure should be (1)000 0000 000(0 1)(000 1010 0)(011 0010 0)(100) = 2148049700\nActual value: %u\n\n", bloodPressure);

    bloodPressure = 0;

    printf("3. prepareBloodPressure(1, 20, 100,  )\n");
    prepareBloodPressure(1, 20, 100, &bloodPressure);
    printf("Value of bloodPressure should be (0)000 0000 000(0 1)(000 1010 0)(011 0010 0)(110) = 566054\nActual value: %u\n\n", bloodPressure);


    printf("*****************************************************\nTesting presentHeartRate\n\n");

    printf("1. presentHeartRate(56) expected output\nPresenting the heart rate data...\nInput is 0x38\n\nError in data - parity bit. Parity bit = 0\n"
            "\nActual output\n");
    presentHeartRate(56);
    //printf("Return value should be 1\nActual return value: %d\n\n", presentHeartRate(56));



    printf("\n2. presentHeartRate(150) expected output\nPresenting the heart rate data...\nInput is 0x96\n\nParity bit is correct. Parity bit = 0\n"
            "Heart rate sensor must be reset.\nHeart rate is 18 bpm\nBlood pressure is abnormal, but no indication of whether it is high or low. Please test blood pressure again.\n\nActual output\n");
    //printf("Return value should be 2\nActual return value: %d\n", presentHeartRate(150));
    presentHeartRate(150);

    printf("*******************************************************\nTesting presentBloodPressure\n\n");

    printf("1. presentBloodPressure(214550584) = (1)000 0000 000(0 0)(100 0001 0)(010 1011 1)(000)\n\n");
    presentBloodPressure(2147750584);

    printf("\n2. presentBloodPressure(1839268) = (0)000 0000 000(1 1)(100 0001 0)(000 1010 0)(100) \n\n");
    presentBloodPressure(1839268);
    
    printf("\n3. presentBloodPressure(1839270) = (0)000 0000 000(1 1)(100 0001 0)(000 1010 0)(110) \n\n");
    presentBloodPressure(1839270);

    printf("*******************************************************\nTesting presentTemperature\n\n");

    presentTemperature(34176);

    return 0;
}
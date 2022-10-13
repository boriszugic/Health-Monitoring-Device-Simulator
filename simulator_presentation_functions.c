/*

File simulator_presentation_functions.c


Purpose: contains functions that present the device data to the user.



Revision:
a. Initial code - Boris Zugic
b. Commit 1 - Implemented presentHeartRate, presentBloodPressure, presentTemperature - Boris Zugic

*/


/************************************************************************/

// INCLUDE FILES

#include "stdio.h"
#include "stdlib.h"
#include "simulator_presentation_functions.h"
#include "simulator_helper_functions.h"


/************************************************************************/
//MACROS  / DEFINES

#define SENSOR_RESET_HR "Heart rate sensor must be reset"
#define SENSOR_RESET_BP "Blood pressure sensor must be reset"
#define HIGH_HR "Heart rate is high"
#define LOW_HR "Heart rate is low"
#define HIGH_BP "Blood pressure is high"
#define LOW_BP "Blood pressure is low"
#define ABNORMAL_HIGH_BP "Abnormal high blood pressure - head to emergency"


/************************************************************************/
// FUNCTION PROTOTYPES



/************************int presentHeartRate(unsigned short heartRate)**********************************/
/* purpose: presents the heart rate data

input:
heartRate - contains the heart rate data

output:
none

return:
0 - request was completed correctly
1 - an error has occurred (e.g., incorrect parity bit)
2 - sensor needs to be reset


*/
int presentHeartRate(unsigned short heartRate)
{
	// return value indicating whether device needs reset
	int needsReset = 0;
	
	printf("Presenting the heart rate data...\n");
	
	// display bit pattern in hex
	printf("Input is 0x%X\n\n", heartRate);
	
	
	// return 1 if parity bit is incorrect
	if (checkParityBitHR(heartRate))
	{
		return 1;
	}
	
	// check status bits and display error message if needed
	if (1 << 1 & heartRate)
	{
		printf("%s\n", SENSOR_RESET_HR);
		needsReset += 2;
	}
	
	// display heart rate
	printf("Heart rate is %d bpm\n\n", readHeartRate(heartRate));

	// display abnormality if applicable
	if ((1 << 11 & heartRate) && (1 << 12 & heartRate))
		printf("%s", LOW_HR);
	
	else
	{
		if ((1 << 12 & heartRate))
			printf("%s", HIGH_HR);
	}

	return(needsReset);
}


/*************************************************************************************/
/* purpose: presents the blood pressure data

input:
bloodPressure - contains the blood pressure data

output:
none

return: 
0 - request was completed correctly
1 - an error has occurred (e.g., incorrect parity bit)
2 - sensor needs to be reset



*/
int presentBloodPressure(unsigned int bloodPressure)
{
	// return value
	int needsReset = 0;
	
	printf("Presenting the blood pressure data...\n");
	// display bit pattern in hex
	printf("Input is 0x%X\n\n", bloodPressure);
	
	// return 1 if incorrect parity bit
	if(checkParityBitBP(bloodPressure))
	{
		return 1;
	}
	
	// check status bits and display error message if needed
	if (1 << 1 & bloodPressure)
	{
		printf("%s\n", SENSOR_RESET_BP);
		needsReset += 2;
	}

	// display diastolic and systolic blood pressure
	printf("Diastolic blood pressure is %d\nSystolic blood pressure is %d\n\n", readDiastolicPressure(bloodPressure), readSystolicPressure(bloodPressure));

	/* display abnormality if applicable*/
	
	// case 1: abnormally high blood pressure (bits 19 && 20 = 3)
	if ((1 << 19 & bloodPressure) && (1 << 20 & bloodPressure))
	{
		printf("%s\n", ABNORMAL_HIGH_BP);
	}
	else
	{
		// case 2: low blood presure (bits 19 && 20 = 1)
		if ((1 << 19 & bloodPressure))
			printf("%s\n", LOW_BP);
		else
		{	
			// case 3: high blood pressure (bits 19 && 20 = 2)
			if ((1 << 20 & bloodPressure))
				printf("%s\n", HIGH_BP);
			else
		{
				// default: normal blood pressure (bits 19 && 20 = 0)
				printf("Blood pressure is normal.\n");
		}
		}
	}

	return(needsReset);
}


/*************************************************************************************/
/* purpose: presents the temperature data

input: 
temperature - contains the temperature data

output: none

return:
0 - sucessful completion
1 - an error has occured (e.g., incorrect parity bit)
2 - needs reset


*/
int presentTemperature(unsigned short temperature)
{
	// return value indicating whether device needs reset
	int needsReset = 0;

	
	printf("Presenting the temperature data...\n");

	// display the sensor data in hex
	printf("Input is 0x%X\n", temperature);

	// return 1 if incorrect parity bit
	if (checkParityBitHR(temperature))
	{
		return 1;
	}

	// check status bits and display error message if needed
	if (1 << 1 & temperature)
	{
		printf("%s\n", SENSOR_RESET_HR);
		needsReset += 2;
	}

	// output temperature, pass bits 3-10 to computeFloatValue(), round to 3 decimal places
	printf("Body temperature is %.3f\n", computeFloatValue(((1 << 8) - 1) & (temperature >> (4 - 1) )) + 37);
	
	// if the blood pressure is abnormal then inform the user about it (don't know what this means)

	return(needsReset);
}







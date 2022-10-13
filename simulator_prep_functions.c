
/*

File simulator_main.c


Purpose: contains functions for preparing the output of the temperature and blood pressure sensors



Revision:
a. Initial code - Boris Zugic
b. Commit 1 - Boris Zugic, implemented functions prepareHeartRate() && prepareBloodPressure(), 2022-10-08

*/


/************************************************************************/

// INCLUDE FILES
#include <stdio.h>
#include "simulator_prep_functions.h"
#include "simulator_helper_functions.h"

/************************************************************************/
//MACROS  / DEFINES

#define ILLEGAL_INPUT_HR "PrepareHeartRate - illegal input"
#define ILLEGAL_INPUT_BP "PrepareBloodPressure - illegal input"



/************************************************************************/
// FUNCTION PROTOTYPES





/***********************************************************************************/
/* 	function name: prepareHeartRate
	
	purpose: stores heart rate information in 16-bit integer

	parameters: 
		int heartrate - heartrate of person (expected value <= 255 and >= 0).
		int sensorFunction - indicates whether the heart rate sensor functions properly or not (0 if yes, 1 if not)
		unsigned short* heartRate - output variable derived from heartrate and sensorFunction

	output: 
		unsigned short* heartRate

	return: 
		0 - successful completion	
		1 - illegal input 

*/
int prepareHeartRate(int heartrate, int sensorFunction, unsigned short* heartRate)

{	
	// display error message and return 1 if heartrate is NOT within valid range (0 - 255)
	if (heartrate > 255 || heartrate < 0) {

		printf("%s\n", ILLEGAL_INPUT_HR);

		return 1;
	}

	// set bits 0-1
	setSensorFunctionBitsHR(sensorFunction, heartRate);
	
	// set bit 2 if heartrate is abnormal
	if (heartrate < 50 || heartrate > 165)
	setBitShort(heartRate, 2);
	
	// set bits 3-10 
	setHeartRateBits(heartrate, heartRate);
	
	// set bits 11-12
	setHighLowBitsHR(heartrate, heartRate);

	// set bit 15
	computeParityBitShort(heartRate);


	return(0);
}



/***********************************************************************************/
/* 	function name: prepareBloodPressure
	
	purpose: stores blood pressure information in 32-bit integer

	parameters: 
		int systolicPressure
		int diastolicPressure
		int sensorFunction - indicates whether the heart rate sensor functions properly or not (0 if yes, 1 if not)
		unsigned short* bloodPressure - output variable

	output: 
		unsigned short* bloodPressure

	return: 
		0 - successful completion	
		1 - illegal input 

*/
int prepareBloodPressure(int sensorFunction, int systolicPressure, int diastolicPressure, unsigned int* bloodPressure)
{
	// display error message and return 1 if diastolicPressure OR systolicPressure is NOT within valid range (0 - 255)
	if (systolicPressure > 255 || systolicPressure < 0 || diastolicPressure > 255 || diastolicPressure < 0 ) {

		printf("%s\n", ILLEGAL_INPUT_BP);

		return 1;
	}

	// set bits 0-1
	setSensorFunctionBitsBP(sensorFunction, bloodPressure);
	
	// set bit 2 if heartrate is abnormal
	if (setHighLowBitsBP(diastolicPressure, systolicPressure, bloodPressure) != 0)
		setBitInt(bloodPressure, 2);
	
	// set bits 3-10 
	setDiastolicPressureBits(diastolicPressure, bloodPressure);
	
	// set bits 11-18
	setSystolicPressureBits(systolicPressure, bloodPressure);

	// set bits 19-20
	setHighLowBitsBP(diastolicPressure, systolicPressure, bloodPressure);

	// set bit 31
	computeParityBitInt(bloodPressure);

	return(0);
}




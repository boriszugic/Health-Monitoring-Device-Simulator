
/*

File simulator_main.c


Purpose: contains functions prototypes of prep functions for heart rate and blood pressure sensors



Revision:
a. Initial code - Boris Zugic


*/


/************************************************************************/

// INCLUDE FILES


/************************************************************************/
//MACROS  / DEFINES






/************************************************************************/
// FUNCTION PROTOTYPES


int prepareHeartRate(int heartBPM, int sensorFunction, unsigned short* heartRate);
int prepareBloodPressure(int sensorFunction, int systolicPressure, int diastolicPressure, unsigned int* bloodPressure);




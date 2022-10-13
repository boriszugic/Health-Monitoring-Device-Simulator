// file is simulator_helper_functions.h
// 
// purpose: function prototypes for helper functions
//
// revision: 
//  a. Boris Zugic - Initial code

/*************************HEART RATE HELPER FUNCTIONS************************/

int setHeartRateBits(int heartrate, unsigned short* heartRate);
int setSensorFunctionBitsHR(int sensorFunction, unsigned short* heartRate);
int computeParityBitShort(unsigned short* heartRate);
int setHighLowBitsHR(int heartrate, unsigned short* heartRate);
int setBitShort(unsigned short* inputNum, int bitNum);
int readHeartRate(unsigned short heartRate);
int checkParityBitHR(unsigned short heartRate);

/*************************BLOOD PRESSURE HELPER FUNCTIONS************************/

int setDiastolicPressureBits(int diastolicPressure, unsigned int* bloodPressure);
int setSystolicPressureBits(int systolicPressure, unsigned int* bloodPressure);
int setSensorFunctionBitsBP(int sensorFunction, unsigned int* bloodPressure);
int computeParityBitInt(unsigned int* bloodPressure);
int setHighLowBitsBP(int diastolicPressure, int systolicPressure, unsigned int* bloodPressure);
int setBitInt(unsigned int* inputNum, int bitNum);
int checkParityBitBP(unsigned int bloodPressure);
int readSystolicPressure(unsigned int bloodPressure);
int readDiastolicPressure(unsigned int bloodPressure);

/**************************TEMPERATURE HELPER FUNCTIONS**************************/

float computeFloatValue(unsigned short num);


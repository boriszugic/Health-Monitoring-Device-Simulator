[comment]: <> (Please note: This is a Markdown file. In order to preview the output, simply paste this text into an online Markdown editor. ) 

# **Health Monitoring Device Simulator**
*Project Status*: Development slowed-down

### Description
File name is test.c. This program servers two purposes: efficiently stores heart rate, blood pressure and temperature data given by the device, then reads the stored data and outputs corresponding information to the user.
1. *Heart rate*: data is stored in a 16-bit integer, where bits 
    * 0 indicates correct reading if 0
    * 1 needs to be reset if 1
    * 2 is set to 1 if heart rate is abnormal
    * 3-10 store the heart rate
    * 11-12 indicate the abnormality of heart rate. 10 for high heart rate, 01 for low, 00 is normal
    * 13-14 not used
    * 15 even parity bit

2. *Blood pressure*: data is stored in a 32-bit integer, where bits
    * 0 indicates correct reading if 0
    * 1 needs to be reset if 1
    * 2 is set to 1 if blood pressure abnormal
    * 3-10 store diastolic blood pressure
    * 11-18 store systolic blood pressure
    * 19-20 indicate the abnormality of blood pressure. 10 for high, 01 for low, 11 if blood pressure is extremely low or high, 00 is normal
    * 21-30 not used* 32 even parity bit

3. *Temperature*: data is stored in a 16-bit integer, where bits
    * 0 indicates correct reading if 0
    * 1 needs to be reset if 1
    * 2 not used
    * 3-10 store the temperature in floating point representation as per IEEE754
    * 11-14 not used
    * even parity bit


### How to Compile
Please refer to Makefile in current repository.  

### Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

Please make sure to update tests as appropriate.

### Authors and Acknowledgement
Start-up: Boris Zugic, boriszugic123@gmail.com
Other (full name, contribution):
1. Boris Zugic, entirety of project.

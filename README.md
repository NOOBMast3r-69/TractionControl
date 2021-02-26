# TractionControl

Traction Control Firmware testing Part I - (According to firmware linked at here)


Step 1.
Get the Hardware details correct
Count the number of slits in the disc
Attach the ABS IR sensor firmly near the disc
Connect the Output pin of IR sensor to digital Input 1 of traction control board which is marked as DI1 on board for front wheel and DI2 for rear wheel
Connect VCC GND of IR sensor to 12V and GND 

Step 2.
Enter the hardware description in code which is present in initial lines of code

// code initialisation and settings
#define NUMBER_OF_SLITS 10 // change it to actual number of slits in setup
#define FRONT_SENS_PIN  PB3  //DIN1
#define REAR_SENS_PIN   PB4  //DIN2
#define RPM_UPDATE_FREQUENCY 10 //Hz 
#define TRACTION_DIFF_THRESHOLD 2 


Suppose you have number of slits = 35 in actual hardware setup then edit this line “#define NUMBER_OF_SLITS 10” to “#define NUMBER_OF_SLITS 35”
RPM Update frequency is the number of times RPM is updated per second. Higher number of slits in the disc will help in accurate rpm measurement in less amount of time, also if the RPM update frequency is high then you will not be able to measure lower RPM’s properly, If frequency is low then the overall system response time will increase.
Calculating the sweet spot for RPM measurement
Use this equation for minimum rpm measurement 

RPM(min) = NUMBER_OF_SLITS * RPM_UPDATE_FREQUENCY/60

NUMBER_OF_SLITS 60
RPM_UPDATE_FREQUENCY 5 

Gives => (60*5)/60 = 5 RPM 




NOTE* - Upload the code then connect the bluetooth module 
Connect the Bluetooth module to PROG 1 Header as per table 
	1 - GND
	2 -  NC
	3 - VCC
	4 - BLuetooth TX
	5 - bluetooth RX
	6 - NC
Fin1 PROG1 header  and pin 1 is towards the edge of board

Download Serial terminal app  and connect , You will automatically get live readings on your phone

You can also open serial port of arduino for fixed setup

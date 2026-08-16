/*
This program will tell you the direction, or heading, the robot it pointing.
Before you can use it you must run the program Xmid_Ymid and find the middle values 
of the compass data.
These value must be copied into lines 9 and 10 of this program.
*/

#include <Wire.h>
#include <LIS3MDL.h>
double xmid = 2885;     //Put your value for Xmid in here
double ymid = -3552;         //Put your value for Ymid in here
double x = 0;
double y = 0 ;

LIS3MDL mag;

char report[80];

void setup()
{
  Serial.begin(9600);
  Wire.begin();

  if (!mag.init())
  {
    Serial.println("Failed to detect and initialize magnetometer!");
    while (1);
  }

  mag.enableDefault();
}//

void loop()
{
 Serial.println(heading());
}




/****************************
 *    Heading function
 *****************************/
double heading()
{
   mag.read();
  
x = mag.m.x - xmid;
y = mag.m.y - ymid;
  
double direction = atan2(y , x)*57;  //the 57 converts the angle from radians to degrees
  return direction;
}

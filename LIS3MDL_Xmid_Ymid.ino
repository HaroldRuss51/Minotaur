#include <Wire.h>
#include <LIS3MDL.h>

LIS3MDL mag;
LIS3MDL::vector<int16_t> running_min = {32767, 32767, 32767}, running_max = {-32768, -32768, -32768};

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
}

void loop()
{
  mag.read();

  running_min.x = min(running_min.x, mag.m.x);
  running_min.y = min(running_min.y, mag.m.y);
  running_min.z = min(running_min.z, mag.m.z);

  running_max.x = max(running_max.x, mag.m.x);
  running_max.y = max(running_max.y, mag.m.y);
  running_max.z = max(running_max.z, mag.m.z);

  snprintf(report, sizeof(report), "min: {%+6d, %+6d, %+6d}   max: {%+6d, %+6d, %+6d}",
    running_min.x, running_min.y, running_min.z,
    running_max.x, running_max.y, running_max.z);
  Serial.println(report);
  Serial.println();
  Serial.print("Xmax");
  Serial.print("\t");
   Serial.print(running_max.x);
     Serial.print("\t");
  Serial.print("Xmin");
  Serial.print("\t");
  Serial.print(running_min.x);
   Serial.print("\t");
  Serial.print("Ymax");
  Serial.print("\t");
  Serial.print(running_max.y);
  Serial.print("\t");
  Serial.print("Ymin");
  Serial.print("\t");
  Serial.println(running_min.y); 

/************************************************
Find the middle values
*************************************************/
  Serial.print("Xmid");
  Serial.print((running_max.x + running_min.x)/2);
  Serial.print("\t");
  Serial.print("Ymid");
  Serial.print("\t");
  Serial.println((running_max.y + running_min.y)/2);
  
  delay(100);
  
}

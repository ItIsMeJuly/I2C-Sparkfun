#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>

#include "SparkFun_Qwiic_Joystick_Arduino_Library.h"
#include "SFE_MicroOLED.h"

int x = 1;
int count = 0;

JOYSTICK joystick;
MicroOLED oled(9, 1);


void receiveEvent(int bytes) {
  count = 0;
  x = Wire.read();    // read one character from the I2C
}

void setup() {

  Wire.begin(9); 
  Serial.begin(9600);

  joystick.begin(Wire, 0x20);

  if(!oled.begin()){
        Serial.println("Device failed to initialize");
        while(1);  
    }
  delay(1000);   //Give display time to power on

  oled.clear(ALL);
  oled.clear(PAGE);
  oled.display();

  Wire.onReceive(receiveEvent);
}

void loop() {
  switch (x)
  {
  case 0:
    break;
  case 1:

    int val = joystick.getButton();
    int Y = joystick.getVertical();
    delay(150);

    if  (Y > 575)
    {
        count--;
    }
    else if (Y < 450)
    {
        count++;
    }

    oled.clear(PAGE);
    oled.setCursor(28, 20);
    oled.print(count);
    oled.display();

    if(val == LOW)
    {
      x = 0;
      Wire.beginTransmission(10);
      Wire.write(1);
      Wire.endTransmission();
    }
    break;

  default:
    break;
  }
}
#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include "SparkFun_Qwiic_Joystick_Arduino_Library.h"
#include "SFE_MicroOLED.h"

int LED = 13;
int x = 0;

int ver;
int hor;

JOYSTICK joystick;
MicroOLED oled (9, 1);

void receiveEvent(int bytes) {
  hor = 30;
  ver = 30;
  x = Wire.read();    // read one character from the I2C
}

void setup() {
  // Define the LED pin as Output
  pinMode (LED, OUTPUT);
  // Start the I2C Bus as Slave on address 9
  Wire.begin(10); 
  Serial.begin(9600);

  
  if(!oled.begin()){
        Serial.println("Device failed to initialize");
        while(1);  // halt execution
    }
  delay(1000);   //Give display time to power on

  oled.clear(ALL);
  oled.clear(PAGE);
  oled.display();
  
  joystick.begin(Wire, 0x20);
  // Attach a function to trigger when something is received.
  Wire.onReceive(receiveEvent);
}

void loop() {

  switch (x)
  {
  case 0:
    break;
  
  case 1:
    oled.clear(PAGE);
    oled.setCursor(hor, ver);
    oled.print('x');
    oled.display();

    int val = joystick.getButton();
    int X = joystick.getHorizontal();
    int Y = joystick.getVertical();
    delay(120);
    if  (X > 575)
    {
        hor += 3;
        hor > 59 ? hor = 59:0;
    }
    else if (X < 450)
    {
        hor -= 3;
        hor < 0 ? hor = 0:0;
    }
    if  (Y > 575)
    {
        ver += 3;
        ver > 40 ? ver = 40:0;
    }
    else if (Y < 450)
    {
        ver -= 3;
        ver < 0 ? ver = 0:0;
    }

    if(val == LOW)
    {
      x = 0;
      Wire.beginTransmission(9);
      Wire.write(1);
      Wire.endTransmission();

    }
    break;

  default:
    break;
  }
}
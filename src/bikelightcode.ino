#include <Wire.h>
#include <Adafruit_MMA8451.h>
#include <Adafruit_Sensor.h>
#include <math.h>

#define MMA8451_DEFAULT_ADDRESS (0x1C)
const int LED_PIN = 9;
const int photoresistorPin = A0;
Adafruit_MMA8451 mma = Adafruit_MMA8451();
int counter = 255;
bool lightOn = true;

void setup() {
  // put your setup code here, to run once:
    Serial.begin(9600);
    if (! mma.begin()) {
      Serial.println("Couldnt start");
    while (1);
  } 
  
  mma.setRange(MMA8451_RANGE_2_G);
  Serial.print("Range = "); Serial.print(2 << mma.getRange());  
  Serial.println("G");
  
}

void loop() {
  int intensity = 0;
  
  intensity = analogRead(photoresistorPin);
  Serial.println("Intensity: ");
  Serial.println(intensity);
  if(intensity > 175) {
    lightOn = false;
  }
  else {
    lightOn = true;
  }
  mma.read();
  sensors_event_t event; 
  mma.getEvent(&event);
  double xAccel = abs(event.acceleration.y); 
  Serial.println(xAccel);
  
  if(lightOn) {
    if(xAccel > 10) {
      analogWrite(LED_PIN, 75);
    }
    else if(xAccel > 5) {
      // while(counter != 180) {
      //   if(counter > 180) {
      //     counter--;
      //   }
      //   else {
      //     counter++;
      //   }
      //   analogWrite(LED_PIN, counter);
      //   delay(5);
      // }
      analogWrite(LED_PIN, 60);
    }
    else if(xAccel > 2) {
      // while(counter > 100) {
      //   if(counter > 100) {
      //     counter--;
      //   }
      //   else {
      //     counter++;
      //   }
      //   analogWrite(LED_PIN, counter);
      //   delay(5);
      // }
      analogWrite(LED_PIN, 40);
    }
    else {
      // while(counter > 70) {
      //   if(counter > 70) {
      //     counter--;
      //   }
      //   else {
      //     counter++;
      //   }
      //   analogWrite(LED_PIN, counter);
      //   delay(5);
      // }
      analogWrite(LED_PIN, 30);
    }
  }
  else {
    analogWrite(LED_PIN, 0);
  }
  delay(100);
  
  
}

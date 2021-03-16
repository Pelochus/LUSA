/* 
 * LUSA - DIY proximity sensor for cars going backwards
 * Made by: Pelochus
 * 
 * Uses an ultrasonic sensor to change 
 * frequency of LEDs depending on the 
 * distance. Also controls buzzer's frequency, 
 * faster being closer to an obstacle
 * 
 * Centimeters ared use throughout the whole code
 * 1 cm = 0.3937 inches
 */

#include "SR04.h" // Sensor library

// Constant Values
const int redPin = 3;
const int yellowPin = 4;
const int whitePin = 5;
const int greenPin = 6;
const int bluePin = 7;
const int buzzerPin = 2;
const int echoPin = 11;
const int trigPin = 12;

// Variables
int sound_delay = 25;
int std_delay = 80; // standard delay, made for turning on and off once
int current_led; // choses LED depending on distance
unsigned int distance; // distance cant be negative, hence unsigned int
SR04 sr04 = SR04(echoPin, trigPin); // creates SR04 object

void setup() {
   pinMode(buzzerPin, OUTPUT);
   pinMode(redPin, OUTPUT);
   pinMode(yellowPin, OUTPUT);
   pinMode(whitePin, OUTPUT);
   pinMode(greenPin, OUTPUT);
   pinMode(bluePin, OUTPUT);
   Serial.begin(9600); // not necessary in final project, used for debugging
}

void loop() {
   distance = sr04.Distance(); // measures distance to the nearest object

   // this if statement can be removed if you want always buzzer and LED giving information
   if (distance > 200) {
     Serial.print(distance);
     Serial.println(" cm");
     delay(250);
   }
   else {     
      sound_delay = sound_delay + (distance * 2); // higher distance, less delay between sounds
      Serial.print(distance);
      Serial.println(" cm");
      Serial.print(sound_delay);
      Serial.println(" ms");

      // sets which pin will be used depending on distance
      // Scale: RED - VERY CLOSE
      //        YELLOW - CLOSE
      //        WHITE - AVERAGE DISTANCE
      //        GREEN - SLIGHTLY FAR
      //        BLUE - FAR
      // change values inside if statements to vary the scale
      if (distance < 35) {
        current_led = redPin;
      }
      else if (distance < 70) {
        current_led = yellowPin;
      }
      else if (distance < 105) {
        current_led = whitePin;
      }
      else if (distance < 140) {
        current_led = greenPin;
      }
      else {
        current_led = bluePin;
      }

      // LEDs and Buzzer controlling 
      digitalWrite(buzzerPin, HIGH);
      digitalWrite(current_led, HIGH);
      delay(std_delay);
      digitalWrite(buzzerPin, LOW);
      
      delay(sound_delay); // higher refresh if distance is too low
      sound_delay = 25; // makes it the original value again (to avoid getting infinetely bigger)
      digitalWrite(current_led, LOW); // turns off led
      
      digitalWrite(buzzerPin, HIGH);
      delay(std_delay);
      digitalWrite(buzzerPin, LOW);
   }
}

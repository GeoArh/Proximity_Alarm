#include <Arduino.h>
#include <Ultrasonic.h>

const int button = 13; //Set Pin 13 as button input
const int buzzer = 9; //Set Pin 9 as buzzer output
const int freq = 2170; //Set frequency value

const int LED1 = 3; //Set Pin 3 as LED1 output
const int LED2 = 4; //Set Pin 4 as LED2 output
const int LED3 = 5; //Set Pin 5 as LED3 output

bool buttonState = LOW; //Current button state
bool SystemState = LOW; //System is off
bool lastButtonState = LOW; //Last button state
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time;

int distance = 0; //Variable used by the ultrasonic sensor to store the distance
uint16_t mediumLight = 50; //Set medium light value

//Define pins ultrasonic(trig,echo)
Ultrasonic ultrasonic(53,52);

void setup()
{   
  pinMode(button, INPUT); //Set Pin as INPUT
  pinMode(buzzer, OUTPUT); //Set Pin as OUTPUT

  pinMode(LED1, OUTPUT); //Set Pin as OUTPUT
  pinMode(LED2, OUTPUT); //Set Pin as OUTPUT
  pinMode(LED3, OUTPUT); //Set Pin as OUTPUT

  digitalWrite(LED1, LOW); //Set LED1 OFF
  digitalWrite(LED2, LOW); //Set LED2 OFF
  digitalWrite(LED3, LOW); //Set LED3 OFF
}

void actuateBuzzer()
{
  tone(buzzer, freq, 150); //Set output active
  digitalWrite(LED1, HIGH); //Set LED1 ON
  digitalWrite(LED2, HIGH); //Set LED2 ON
  digitalWrite(LED3, HIGH); //Set LED3 ON
  delay(150);
  analogWrite(LED1, mediumLight); //Set LED1 ON
  analogWrite(LED2, mediumLight); //Set LED2 ON
  analogWrite(LED3, mediumLight); //Set LED3 ON
  delay(100);

  tone(buzzer, freq, 200); //Set output active
  digitalWrite(LED1, HIGH); //Set LED1 ON
  digitalWrite(LED2, HIGH); //Set LED2 ON
  digitalWrite(LED3, HIGH); //Set LED3 ON
  delay(200);
  analogWrite(LED1, mediumLight); //Set LED1 ON
  analogWrite(LED2, mediumLight); //Set LED2 ON
  analogWrite(LED3, mediumLight); //Set LED3 ON
  delay(150);

  tone(buzzer, freq, 300); //Set output active
  digitalWrite(LED1, HIGH); //Set LED1 ON
  digitalWrite(LED2, HIGH); //Set LED2 ON
  digitalWrite(LED3, HIGH); //Set LED3 ON
  delay(350);
  analogWrite(LED1, mediumLight); //Set LED1 ON
  analogWrite(LED2, mediumLight); //Set LED2 ON
  analogWrite(LED3, mediumLight); //Set LED3 ON
  
}

void DetectDistance()
{
  distance = ultrasonic.read(); //Use 'CM' for centimeters or 'INC' for inches
  if(distance < 200) //Check if the distance is less than 200cm
  {
    actuateBuzzer(); //Activate buzzer
  }
  //every 0.5 sec. 
  delay(500);
}

void powerUpSequence()
{
  digitalWrite(LED1, HIGH); //Set LED1 ON
  delay(400);
  digitalWrite(LED1, LOW); //Set LED1 OFF

  digitalWrite(LED2, HIGH); //Set LED2 ON
  delay(400);
  digitalWrite(LED2, LOW); //Set LED2 OFF

  digitalWrite(LED3, HIGH); //Set LED3 ON
  delay(400);
  digitalWrite(LED3, LOW); //Set LED3 OFF
  delay(100);

  for(int i = mediumLight; i < 255; i+=2)
  {
    analogWrite(LED1, i); //Set LED1 ON
    analogWrite(LED2, i); //Set LED2 ON
    analogWrite(LED3, i); //Set LED3 ON
    delay(15);
  }

  for(int i = 255; i >= 0; i-=2)
  {
    analogWrite(LED1, i); //Set LED1 ON
    analogWrite(LED2, i); //Set LED2 ON
    analogWrite(LED3, i); //Set LED3 ON
    delay(15);
  }

  delay(150);
  analogWrite(LED1, mediumLight); //Set LED1 ON
  analogWrite(LED2, mediumLight); //Set LED2 ON
  analogWrite(LED3, mediumLight); //Set LED3 ON
}

void powerDownSequence()
{
  for(int i = mediumLight; i < 255; i+=2)
  {
    analogWrite(LED1, i); //Set LED1 ON
    analogWrite(LED2, i); //Set LED2 ON
    analogWrite(LED3, i); //Set LED3 ON
    delay(15);
  }

  for(int i = 255; i >= 0; i-=2)
  {
    analogWrite(LED1, i); //Set LED1 ON
    analogWrite(LED2, i); //Set LED2 ON
    analogWrite(LED3, i); //Set LED3 ON
    delay(15);
  }

  digitalWrite(LED1, LOW); //Set LED1 OFF
  digitalWrite(LED2, LOW); //Set LED2 OFF
  digitalWrite(LED3, LOW); //Set LED3 OFF

}

void loop()
{   /* Function to be redisigned for On/Off functionality */

  buttonState = digitalRead(button); //Read button state

  // If the switch changed, due to noise or pressing:
  if (buttonState != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) 
  {
  // whatever the reading is at, it's been there for longer than the debounce
  // delay, so take it as the actual current state:

    // only toggle the system state flag if the new button state is HIGH
    if (buttonState == HIGH) 
    {
      SystemState = !SystemState; //Toggle system state
      if(SystemState == HIGH) //Check if system should be on
      {
        powerUpSequence(); //Trigger the Power up sequence
      }
      else
      {
        powerDownSequence(); //Trigger the Power down sequence
      }
    }
  }

  lastButtonState = buttonState; //Save last button state

  if(SystemState == HIGH) //Check if system is on
  {
    DetectDistance(); //Detect distance
  }
  else
  {
    delay(500); //Small delay
  }
}
#include "Arduino.h"

const int button = 2; //Set Pin 2 as button input
const int buzzer = 9; //Set Pin 9 as buzzer output
const int freq = 2170; //Set frequency value

bool buttonState = LOW; //Current button state
bool lastButtonState = LOW; //Last button state

void setup()
{   
    pinMode(button, INPUT); //Set Pin as INPUT
    pinMode(buzzer, OUTPUT); //Set Pin as OUTPUT
}

void actuateBuzzer()
{
    tone(buzzer, freq, 150); //Set output active
    delay(250);
    tone(buzzer, freq, 200); //Set output active
    delay(350);
    tone(buzzer, freq, 300); //Set output active
}

void loop()
{
    buttonState = digitalRead(button); //Read button state

    if (buttonState == HIGH && lastButtonState == LOW) //Check if button is pressed
    {
        actuateBuzzer(); //Activate buzzer
    }

    lastButtonState = buttonState; //Save last button state
    delay(50); //Small delay to debounce the button
}
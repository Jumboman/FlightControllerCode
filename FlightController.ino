/*
  Code for custom flight sim controller

  The circuit:
  - for every button: wire from 5v to button, then from other side of button: one wire to input 2-13, and one 10k resistor to ground.

  Created by TheJumboman

  code is free to use and share.
*/

#include "Keyboard.h"

bool prevStates[14]; // array to store the button states as they were when we last checked them

void setup() {
  // setup all digital pins to be input
  for (int i = 2; i <= 13; i++) {
    pinMode(i, INPUT);
  }
  // initialize control over the keyboard:
  Keyboard.begin();
}

void loop() {
  // in this loop we check every pin for changes
  // ACT: edit this loop to only check the pins you are using! i.e. if you are using 5 buttons, only use pins 2,3,4,5,6, and change loop to i=2; i<=6
  for (int i = 2; i <= 13; i++) {
    int state = digitalRead(i); // read the current state
    if (state != prevStates[i]) { // if the state has changed (i.e. a button has been pressed or unpressed)
      if (state == HIGH) { // if pressed:
      // here I do a little trick: I convert the pin number to an ASCII character. the letter 'a' starts at ASCII value of 97, so this gets you the alphabet
      // if you would rather use other characters (say, !@#$%^&*) you could start at 33. you would change the 93 below to 29, so that 2*2 + 29 starts you at 33.
      // note that I'm using i*2 to leave room for the 'unpressed' key, i.e. pressing buttons gives a,c,e,g while unpressing gives b,d,f,h
        Keyboard.write((char) (i*2 + 93)); 
          if (i == 12) {Keyboard.write((char) (i*2 + 93));Keyboard.write((char) (i*2 + 93));} // this is my eject button, so i'm writing the character 3 times for instant takeoff :D
      } else { // if unpressed:
        // if you have a push button (not self-locking) you might not want to send any character at all. in that case, you could write:
        // if (i == <yourButtonNumber>) {continue;}
        // I don't have those buttons so I don't use it.
        Keyboard.write((char) (i*2 + 94));
      }
    }
    prevStates[i] = state; // important: the current state now becomes the previous state, so we can keep track of changes.
  }
  delay(5); // I add a short delay for stability.
}

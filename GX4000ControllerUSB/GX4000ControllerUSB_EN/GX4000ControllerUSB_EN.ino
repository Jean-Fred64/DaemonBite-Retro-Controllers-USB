/* Amstrad GX4000 USB Adapter (Optimized and Commented)
 * Based on the work of Mikael Norrgård (DaemonBite)
 *
 * This program is free software under the GNU GPL v3 license.
 */

#include "Gamepad.h"

// ATT: 20 chars max.
const char *gp_serial = "Amstrad GX4000 USB";

// Arduino pins definition (based on Amstrad GX4000 wiring)
#define PIN_UP      A0
#define PIN_DOWN    A1
#define PIN_LEFT    A2
#define PIN_RIGHT   A3
#define PIN_B1      14 // Button 1 (Fire 1)
#define PIN_B2      6  // Button 2 (Fire 2)

// Set up the USB gamepad
Gamepad_ Gamepad;


// -- MODIFICATION (OPTIMIZATION 1: Memory) --
// The 'long' type (32 bits) has been replaced with 'uint8_t' (8 bits),
// which is more efficient and sufficient for storing 6 button states.
//
// -- Optimized version (current):
uint8_t currentState = 0;
uint8_t lastState = 0;
//
// -- Old version (non-optimized):
// long currentState = 0;
// long lastState = 0;


void setup()
{
  // Initialize pins as INPUT_PULLUP.
  // This activates an internal resistor to +5V.
  // When a button is pressed, it connects the pin to GND (Ground),
  // and the Arduino reads a "LOW" signal.
  pinMode(PIN_UP,     INPUT_PULLUP);
  pinMode(PIN_DOWN,   INPUT_PULLUP);
  pinMode(PIN_LEFT,   INPUT_PULLUP);
  pinMode(PIN_RIGHT,  INPUT_PULLUP);
  pinMode(PIN_B1,     INPUT_PULLUP);
  pinMode(PIN_B2,     INPUT_PULLUP);
}

void loop()
{
  // Read the state of each button
  // (digitalRead(...) == LOW) is TRUE if the button is pressed.
  bool up     = (digitalRead(PIN_UP)    == LOW);
  bool down   = (digitalRead(PIN_DOWN)  == LOW);
  bool left   = (digitalRead(PIN_LEFT)  == LOW);
  bool right  = (digitalRead(PIN_RIGHT) == LOW);
  bool b1     = (digitalRead(PIN_B1)    == LOW);
  bool b2     = (digitalRead(PIN_B2)    == LOW);
  
  // Store the current state in a single number for easy comparison
  currentState = up | (down << 1) | (left << 2) | (right << 3) | (b1 << 4) | (b2 << 5);

  // Only send a USB update if the state has changed
  if (currentState != lastState)
  {
    // 1. Update axes (D-Pad)
    int axeX = 0;
    int axeY = 0;

    if (left) axeX = -1;
    else if (right) axeX = 1;

    if (up) axeY = -1;
    else if (down) axeY = 1;
    
    Gamepad._GamepadReport.X = axeX;
    Gamepad._GamepadReport.Y = axeY;

    // 2. Update buttons
    uint16_t buttons = 0;
    if (b1) buttons |= (1 << 0); // Button 0
    if (b2) buttons |= (1 << 1); // Button 1

    Gamepad._GamepadReport.buttons = buttons;
    
    // 3. Send the new state to the computer
    Gamepad.send();

    // Store the current state for the next loop
    lastState = currentState;
  }
  
  // -- MODIFICATION (OPTIMIZATION 2: Latency) --
  // The 'delay(5);' has been removed to minimize latency.
  // The loop now runs at full speed.
  //
  // -- Optimized version (current):
  // (No code, the delay is removed)
  //
  // -- Old version (non-optimized, 5ms latency):
  // delay(5); 
}
# Sound Range LED

Firmware for a Particle Photon 2 that turns on an LED when sound is detected, built as a simple visual loudness cue for music production and mixing.

## Hardware
- Particle Photon 2
- DIYables Sound Sensor (3-pin, digital output) on pin A0
- DIYables Analog Sound Sensor (4-pin, analog and digital outputs) on pin A1
- LED on pin A2
- Breadboard and jumper wires, powered from the 3V3 and GND rails

## How it works
The Photon 2 checks both sensors every 10 ms. When a sensor detects sound above the threshold set by its potentiometer, the LED turns on and stays on for 1 second after the last detection. The readings are published as the cloud variables `s1_reading`, `s2_reading`, and `LED_state`, so you can monitor them in the Particle Console.

## Usage
1. Wire the components as listed above.
2. Flash `sound_range_led.ino` to the Photon 2 using the Particle Web IDE or Workbench.
3. Adjust each sensor's potentiometer until normal speech near the mic triggers the LED.

## Brief Demo
https://www.youtube.com/watch?v=tm-CUXR8eCM

## Author
Andrew Addo

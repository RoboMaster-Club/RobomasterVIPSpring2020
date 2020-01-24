# Software Documentation

## Contributers
* Kurtis Dressel

## Updates

### Week 1 (1/17 - 1/24)

#### Goals
* Develop a prototype for the dart aiming algorithm. To start simple, the algorithm can be run on an Arduino. It will use a PixyCam to locate green light. Depending on where the green light is located in the PixyCam image, the algorithm will move two servos in certain ways to simulate the dart aiming towars the target.
* Get started with embedded programming and the STM32 microcontroller by getting a test program to run on a STM32.

For the Arduino dart aiming algorithm, the following needs to be installed
* The Arduino IDE: https://www.arduino.cc/en/main/software
* The Pixy library: https://docs.pixycam.com/wiki/doku.php?id=wiki:v1:Hooking_up_Pixy_to_a_Microcontroller_-28like_an_arduino-29

Currently, the [dart aiming algorithm](pixy_test.ino), arbitrarily moves two servos depending on whether the light found was in the top, bottom, right, or left side of the image. The servos arbitarily move because they are not actually aiming the dart at this stage. Improvements to the algorithm will include excluding certain blocks (grouped pixels of a certain color) depending on their shape and size. This will need to be tested and tweeked in the future. To make the aiming smoother, a PID controller could be added. In fact, there is an example of a PD controller that can be found in the Arduino IDE in File -> Examples -> Pixy -> pantilt.

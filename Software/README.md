# Software Documentation

## Contributers
* Kurtis Dressel
* Jeff Chen

## Updates

### Week 1 (1/17 - 1/24)

#### Goals
* Develop a prototype for the dart aiming algorithm. To start simple, the algorithm can be run on an Arduino. It will use a PixyCam to locate green light. Depending on where the green light is located in the PixyCam image, the algorithm will move two servos in certain ways to simulate the dart aiming towars the target.
* Get started with embedded programming and the STM32 microcontroller by getting a test program to run on a STM32.

For the Arduino dart aiming algorithm, the following needs to be installed
* The Arduino IDE: https://www.arduino.cc/en/main/software
* The Pixy library: https://docs.pixycam.com/wiki/doku.php?id=wiki:v1:Hooking_up_Pixy_to_a_Microcontroller_-28like_an_arduino-29

Currently, the [dart aiming algorithm](pixy_test.ino), arbitrarily moves two servos depending on whether the light found was in the top, bottom, right, or left side of the image. The servos arbitarily move because they are not actually aiming the dart at this stage. Improvements to the algorithm will include excluding certain blocks (grouped pixels of a certain color) depending on their shape and size. This will need to be tested and tweeked in the future. To make the aiming smoother, a PID controller could be added. In fact, there is an example of a PD controller that can be found in the Arduino IDE in File -> Examples -> Pixy -> pantilt.

### Week 1 (1/24 - 1/31)

#### Goals
* Receive STM32F407VET6 hardware and beginning working on prototype for the in-flight dart aiming algorithm
* Research what computer vision or machine learning libraries or algorithms to use

Given the meeting we had on Friday (1/24), I wanted to reconsider our options for software to aim the dart.

I talked to Williams, the CV team lead, for advice and he suggested reinforment learning. This would help us tune the different parameters used in launch like the pitch and yaw angle. The caveat of this would be that the dart would have to be precise for the reinforment learning model to work. In other words, if we launch our dart the same way multiple times, the dart would need to roughly hit the same spot each launch. 

Here is some of the possible options for the object detection part of the algorithm:
* CNN: The use Convolution Neural Networks and deep learning to detect objects definetly leads to good results. However, as we are only detecting a green circle in our case instead of say a car, this option would be a bit excessive. Also, we wouldn't be able to run it fast enough on a microcontroller or similar hardware due to the number of computations that need to be done.
* [SVM with HOG](https://towardsdatascience.com/vehicle-detection-using-support-vector-machine-svm-19e073b61d16): for a machine learning approach, I would say this is a good option. I have heard that other robomaster teams use this option for their object detection algorithm. Overall, its not too computationally expensive and the core algorithm is not too complex.
* Find Contours: This would be a non machine learning approach that is used to find any spots in the image that have the same color (e.g. the green light that we are looking for). This approach uses a border following algorithm. Examples of this algorithm would be OpenCV's findContours method or the pixy cam's getBlocks method. Personally I think this would be the best choice given that we are only looking for a green circle, but there could be complications such as blur, other lights, the size of the light being too small, etc that cause this method to not be workable.
* Cascade Classifer: This is one of the algorithms we use on the computer vision team. It was originally used to detect faces and uses features to detect dark and light parts of object in question. It is also color blind. Given these things, I don't think this would be a good option to find a solid green circle.

As a side note, how each option performs is mostly just a good guess based on my knowledge of the algorithm. Its hard to say how fast we will be able to run these algorithms without actually testing them on the hardware that we will end up using.

We may also need to consider what hardware and software we need to run our computer vision algorithms. Like Jeff mentioned in Slack, we may not have enough processing power on the STM32F407VET6 as according to [this site](http://shervinemami.info/embeddedVision.html) the STM32F407 "might handle some extremely basic camera applications". Other options for hardware would include the [Pixy Cam](https://pixycam.com/pixy2/), the [Kendryte K210](https://github.com/kendryte), and [OpenMV](https://openmv.io/).

As for the computer vision libraries, most people say that it is not possible to run OpenCV on a STM32. There was one [source](https://medium.com/@deryugin.denis/how-to-run-opencv-on-stm32-mcu-b581f42b0766) that managed to do it, but it looks like it is too slow. The other software that I found was [OpenVX](https://www.khronos.org/openvx/), which looks to be a vision software aimed at embedded systems. This sounds like a promising solution if we decide to continue using a microcontroller for computer vision. 

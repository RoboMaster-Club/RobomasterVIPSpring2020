# Dart Detection Module
## Contributors
* Dansen Wang

## Development Log 
## **Week One (1/17 - 1/24)**

I was given the task to create an exact replica of the dart detection module with a working replica of the dart guiding light. [The Robomaster
Competition Rules Manual](http://rm-static.djicdn.com/documents/13194/9f9ee6499b6d81577802626475484930.pdf) listed the 3 key parts that makes up the dart detection module: A standard small armor module, a pair of dart detection sensor, and a dart guiding light. With the goals of creating exact replicas, I looked for the functions and dimensions of the three components.

![dart detection module overview](https://github.com/RoboMaster-Club/spring-2020-vip-course/blob/master/Target%20Dummy/Picture4.png)

1. Standard Small Armor Module 

      The standard small armor module is the same module that's used on our robots. Its goal is to serve as an impact detection system and it's the one of the two target that our dart need to registered by in order for it to be considered a hit. Since our resources are scarce, I decided the best course of action is to CAD and fabricate a replica of an armor detection module until a more functional target dummy is needed.  
      
![Standard small armor module dimension](https://github.com/RoboMaster-Club/spring-2020-vip-course/blob/master/Target%20Dummy/Small_Armor_Module_Dimensions.PNG)

1. Dart Detection Sensor

   The dart detection Sensor is a pair of IR sensors that's installed to the left and right of the armor module. It's primary function is to serve as the second target that needs to register our dart. The IR sensor must detect the IR light from our dart alongside a hit detection from the armor module in order to register a dart hit. Robomaster have not disclosed the dimensions of IR sensors, so the plan is to estimate the dimensions until further improvements are needed. **Pictures tbd**

1. Dart Guiding Light

   The dart guiding light is installed right below the standard small armor module. It's primary function is to serve as a guiding light for our dart's guidance system. The exact dimension and placement is not disclosed by Robomaster, but the dimension can be estimated using the picture of the base provided by Robomaster. With the bottom of the guiding light at 750 mm above ground and the middle of the guiding light at 791 mm above ground, it is reasonable to install an 80 mm halo light right below the armor detection module.

![Dart Guiding Light Base dimensions](https://github.com/RoboMaster-Club/spring-2020-vip-course/blob/master/Target%20Dummy/Picture3.png)

Following the 520 nm intensity and 80 mm diameter, a proper LED was purchased from superbrightled.com 

![superbrightled.com picture](https://github.com/RoboMaster-Club/spring-2020-vip-course/blob/master/Target%20Dummy/Picture5.png)

## **Week Two (1/24 - 1/31)**


# Dart Detection Module
## Contributors
* Dansen Wang

## Development Log 
## **Week One (1/17 - 1/24)**

I was given the task to create an exact replica of the dart detection module with a working replica of the dart guiding light. [The Robomaster Competition Rules Manual](http://rm-static.djicdn.com/documents/13194/9f9ee6499b6d81577802626475484930.pdf) listed the 3 key parts that makes up the dart detection module: A standard small armor module, a pair of dart detection sensor, and a dart guiding light. With the goals of creating exact replicas, I looked for the functions and dimensions of the three components.

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

With the proper dimensions in place, I am now able to CAD out an exact replica in SolidWorks. Week two was used to assemble a rough replica of the dart detection module based on the image provided in week one.

1. Standard Small Armor Module

   With the proper dimension provided in week one, a rough replica was CADDed in solidworks, foregoing the LED on the sides of the plate. Four counterbore hole is placed on the surface of the armor module so that the surface of the module doesn't have any screws sticking out of it. The four holes are for four m3 screws, binding it to the frame and achieving the proper angle.
   ![small_armor_module](https://github.com/RoboMaster-Club/spring-2020-vip-course/blob/master/Target%20Dummy/CAD_screenshot/sensor_plate.PNG)

1. Dart detection sensor

   The dart detection sensor lacks documented dimensions or IR sensor specifications. Thus a rough estimate was used to create a dumb down replica.
   ![IR_sensor](https://github.com/RoboMaster-Club/spring-2020-vip-course/blob/master/Target%20Dummy/CAD_screenshot/IR_sensor_picture.PNG)

1. Dart Guiding Light 

   The dart guiding light was roughly estimated to be 80 mm in diameter (estimated in week one). A led with similar diameter and intensity (520 nm) was purchased from [superbrightled.com](https://www.superbrightleds.com/cat/led-halo-rings/) and a housing unit was CADDed around the purchased LED.
   ![dart_led](https://github.com/RoboMaster-Club/spring-2020-vip-course/blob/master/Target%20Dummy/CAD_screenshot/Guiding_light_picture.PNG)

1. Frame

   Since the dart guiding light, the dart detection sensor, and the dart guiding light are all angled from ground level, a frame was necessary in order to place the three components in proper orientation.
![frame](https://github.com/RoboMaster-Club/spring-2020-vip-course/blob/master/Target%20Dummy/CAD_screenshot/Frame_picture.PNG)

With all the part in place, all parts are first assembled in SolidWorks.
![assembly_cad](https://github.com/RoboMaster-Club/spring-2020-vip-course/blob/master/Target%20Dummy/CAD_screenshot/Assembly_picture.PNG)

Then, each part is printed using PLA and assembled using m3 screws.


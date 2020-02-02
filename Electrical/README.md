# Dart Electrical Subsystem

## Contributers
* Henry Silva

## Updates

### Week 2 (1/26 - 2/2)

This week I was tasked with creating a schematic for the electrical system that we have been decided on thus far. I decided that the stm32f4 I found from my research last week would be used in the schematic. I first consulted the [stm32f4 datasheet](https://www.st.com/content/ccc/resource/technical/document/reference_manual/3d/6d/5a/66/b4/99/40/d4/DM00031020.pdf/files/DM00031020.pdf/jcr:content/translations/en.DM00031020.pdf) to see how it is powered. I could not find what I was looking for, but after some more research I found the [stm32f4 application note](https://www.st.com/content/ccc/resource/technical/document/application_note/76/f9/c8/10/8a/33/4b/f0/DM00115714.pdf/files/DM00115714.pdf/jcr:content/translations/en.DM00115714.pdf) which includes a sample schematic and an in depth description on the hardware needed for power (such as decoupling capacitors) and other functions. 

After placing the appropriate power hardware in the schematic, I then had to search for how to connect the [OV7670](https://www.arducam.com/wp-content/uploads/2019/11/Arducam_ov7670_cmos_camera_module_revc_ds.pdf) camera to the stm32f4. I found a github [repository](https://github.com/iwatake2222/DigitalCamera_STM32) that included the port assignment of the stm32f4 which helped me figure out which pins to connect the camera to. Since the camera uses I2C, pullup resistors were required on the schematic. I used the STM32CubeMX software to keep track of the pin functions and find pins that I could use for PWM and the IMU. I found that PWM just uses a pin with GPIO output that is turned on and off based on a timer, so I assigned two pins for the two servos.

The next part was to find a suitable IMU for acceleration and gyro measurements. I first went to adafruit and sparkfun to find what breakout boards they had for IMUs. I wanted to find an IMU that only had the measurements that I needed and nothing else to keep it simple and cheap. I found the [LSM6DS3](https://www.st.com/content/ccc/resource/technical/document/datasheet/group0/2e/84/27/34/60/8d/49/f2/DM00237513/files/DM00237513.pdf/jcr:content/translations/en.DM00237513.pdf) which provides 3D digital accelerometer and a 3D digital gyroscope. Using sparkfun's eagle files found on their [product page](https://www.sparkfun.com/products/13339), I was able to add the sensor to my schemtic with the appropirate components to power it.

The last 

Schematic
![Schematic](./src/update2/schematic.PNG)

### Week 1 (1/19 - 1/26)

I was tasked with researching the microcontroller and any other electrical components that might be used to control the dart or dart launcher. In the previous meeting, it was decided that the stm32 would be the best choice for the microcontroller. 
Since a camera will be needed for vision targeting, I searched for a stm32 cameras. This lead me to the [DCMI](https://www.st.com/content/ccc/resource/technical/document/application_note/group0/c0/ef/15/38/d1/d6/49/88/DM00373474/files/DM00373474.pdf/jcr:content/translations/en.DM00373474.pdf) (Digital Camera Interface) for stm32. The DCMI allows for the easy connection of a camera to the stm32. The document also lists stm32 models that have DCMI included.

![DCMI Compatible](./src/update1/dcmi.PNG)

This narrowed down the search for which stm32 to decide on. I looked on digikey for the compatible stm32s and settled on the stm32f4 series because they had the most options and were the cheapest. I decided on the [STM32F407VET6](https://www.digikey.com/product-detail/en/stmicroelectronics/STM32F407VET6/497-12075-ND/2793093) because it seemed to have everything that was required so far for the cheapest price.

In terms of camera modules, the [OV7670](https://www.arducam.com/wp-content/uploads/2019/11/Arducam_ov7670_cmos_camera_module_revc_ds.pdf) seemed to be the most popular one used with the stm32. All image processing functions are fully customizable to customize the camera to what is needed. The resolution of the camera is 640x480, I do not know if that is a good enough resolution given the distance from the target, but if the target gives off enough light it should not be a problem. Although I have found multiple projects that use the camera, I have not found good recent documentation about how to use the camera ([good one but from 2012](https://www.element14.com/community/groups/development-tools/blog/2012/06/11/connecting-an-ov7670-camera-to-the-stm32f4-discovery-board)). More research will be needed if we go along with this choice.

I also did some research into rtos (Real time operating system). From what I understand, it will help the scheduling of tasks so that there is a predictable execution pattern. This also ensures that real time requirements are met (such as a change in the postition of the target relative to the dart, that change being detected, and an appropriate control response that happens in a certain amount of time). I am not sure if a rtos is necessary since the amount of processes running at once will probably not be high, but it also allows programs to pass information to each other and be modular. The information I stated above and more can be found [here](https://www.freertos.org/about-RTOS.html). 

# Dart Electrical Subsystem

## Contributers
* Henry Silva

## Updates

### Week 1 (1/17 - 1/24)

I was tasked with researching the microcontroller and any other electrical components that might be used to control the dart or dart launcher. In the previous meeting, it was decided that the stm32 would be the best choice for the microcontroller. 
Since a camera will be needed for vision targeting, I searched for a stm32 cameras. This lead me to the [DCMI](https://www.st.com/content/ccc/resource/technical/document/application_note/group0/c0/ef/15/38/d1/d6/49/88/DM00373474/files/DM00373474.pdf/jcr:content/translations/en.DM00373474.pdf) (Digital Camera Interface) for stm32. The DCMI allows for the easy connection of a camera to the stm32. The document also lists stm32 models that have DCMI included.

![DCMI Compatible](./src/update1/dcmi.PNG)

This narrowed down the search for which stm32 to decide on. I looked on digikey for the compatible stm32s and settled on the stm32f4 series because they had the most options and were the cheapest.

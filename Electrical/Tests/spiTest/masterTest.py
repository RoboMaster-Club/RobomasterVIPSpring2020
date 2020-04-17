# This code uses spi on the raspberry pi to send data to the stm32 running the slaveTest code
import RPi.GPIO as GPIO # To use gpio on the pi
import spidev # to use spi on the pi
import time

# set up spi with chip enable 0 (we will do chip enable manually) on spi channel 0
spi = spidev.SpiDev()
spi.open(0, 0)

# set pinout to BCM pinout (what you see when you look up raspberry pi pinout)
GPIO.setmode(GPIO.BCM)

# set up pin 4 for slave select as output (very similar to arduino) and pull high
GPIO.setup(4, GPIO.OUT)
GPIO.output(4, GPIO.HIGH)

# create variables that hold the messages to be sent (msg1 will turn the light on the stm32 on and msg will turn it off)
msg1 = 0b10101
msg2 = 0b01010

# This loop will turn the light on the stm32 on and off ten times
for i in range(10):
    # select stm32 by pulling pin 4 low, wait to make sure stm32 is listening and send data and then pull high to deselect
    GPIO.output(4, GPIO.LOW)
    time.sleep(0.01)
    spi.xfer([msg1]) # xfer requires a list to send the data
    GPIO.output(4, GPIO.HIGH)

    time.sleep(0.05)

    # do the same as before but send 0
    GPIO.output(4, GPIO.LOW)
    time.sleep(0.01)
    spi.xfer([msg2])
    GPIO.output(4, GPIO.HIGH)

    time.sleep(0.05)

# clean up GPIO
GPIO.cleanup()

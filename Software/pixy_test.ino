#include <SPI.h>
#include <Pixy.h>

#define SERVO1_PIN 1;
#define SERVO2_PIN 2;

#define X_CENTER ((PIXY_MAX_X-PIXY_MIN_X)/2)       
#define Y_CENTER ((PIXY_MAX_Y-PIXY_MIN_Y)/2)

Pixy pixy;
Servo servo1;
Servo servo2;

int i;
uint16_t numBlocks, x, y;
Block block;

//get the value of the x coordinate if (0, 0) was in the center of the image
uint16_t getZeroCenterX(uint16_t x) {
  return x - X_CENTER
}

//get the value of the y coordinate if (0, 0) was in the center of the image
uint16_t getZeroCenterY(uint16_t y) {
  return y - Y_CENTER
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.print("Starting...\n");

  pixy.init()

  servo1.attch(SERVO1_PIN);
  servo1.attch(SERVO2_PIN);

  i = 0;
}

void loop() {
  // put your main code here, to run repeatedly:
  if (i++ % 50) { //run every 50 frames to not bog down arduino
    numBlocks pixy.getBlocks();

    if (numBlocks > 0) {
      block = pixy.blocks[0]; //assume the largest block is the correct one (for now)
      x = getZeroCenterX(block.x);
      y = getZeroCenterY(block.y);

      if (y > x && y > -x) {
        analogWrite(SERVO1_PIN, 255); //aim upwards
      }
      else if (y > x && y < -x) {
        analogWrite(SERVO2_PIN, 255); //aim left
      }
      else if (y < x && y > -x) {
        analogWrite(SERVO2_PIN, 0); //aim right
      }
      else if (y < x && y < -x) {
        analogWrite(SERVO1_PIN, 0); //aim down
      }
    }
  }
}

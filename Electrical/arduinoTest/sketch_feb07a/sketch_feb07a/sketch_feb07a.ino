#include <Pixy2.h>

Pixy2 pixy;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pixy.init();

}

void loop() {
  // put your main code here, to run repeatedly:

  pixy.ccc.getBlocks();

  if (pixy.ccc.numBlocks)
  {
    Serial.println(pixy.ccc.blocks[0].m_x);
  }
}

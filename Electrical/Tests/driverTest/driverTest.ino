int enableA = 5;
int enableB = 6;
int phaseA = 8;
int phaseB = 7;
int modePin = 4;

int testMode = 2; // what test to run, 1: duty cycle from 100% to 0%, 2: change phase at 100% duty cycle

void setup()
{
    pinMode(enableA, OUTPUT);
    pinMode(enableB, OUTPUT);
    pinMode(phaseA, OUTPUT);
    pinMode(phaseB, OUTPUT);

    digitalWrite(phaseA, HIGH);
    digitalWrite(phaseB, HIGH);
    analogWrite(enableA, 255);
    analogWrite(enableB, 255);
}

void loop()
{
    if (testMode == 1)
    {
        analogWrite(enableA, 255);
        analogWrite(enableB, 255);

        delay(1000);

        analogWrite(enableA, 0);
        analogWrite(enableB, 0);

        delay(1000);
    }

    else if (testMode == 2)
    {
        digitalWrite(phaseA, 0);
        digitalWrite(phaseB, 0);

        delay(100);

        digitalWrite(phaseA, 1);
        digitalWrite(phaseB, 1);

        delay(100);
    }

    else if (testMode == 3)
    {
      digitalWrite(phaseA, 0);
      digitalWrite(phaseB, 0);
      for (int i = 255; i >= 0; i--)
      {
        analogWrite(enableA, i);
        analogWrite(enableB, i);
        delay(10); 
      }
      
      digitalWrite(phaseA, 1);
      digitalWrite(phaseB, 1);
      for (int i = 0; i <= 255; i++)
      {
        analogWrite(enableA, i);
        analogWrite(enableB, i);
        delay(10);
      }
    }

    else if (testMode == 4)
    {
      digitalWrite(phaseA, 1);
      digitalWrite(phaseB, 1);
      analogWrite(enableA, 255);
      analogWrite(enableB, 255);

      delay(1000);

      digitalWrite(phaseA, 0);
      digitalWrite(phaseB, 0);
      analogWrite(enableA, 255);
      analogWrite(enableB, 255);

      delay(1000);

      digitalWrite(phaseA, 1);
      digitalWrite(phaseB, 1);
      analogWrite(enableA, 127);
      analogWrite(enableB, 127);

      delay(1000);

      digitalWrite(phaseA, 0);
      digitalWrite(phaseB, 0);
      analogWrite(enableA, 127);
      analogWrite(enableB, 127);

      delay(1000);

      digitalWrite(phaseA, 1);
      digitalWrite(phaseB, 1);
      analogWrite(enableA, 0);
      analogWrite(enableB, 0);

      delay(1000);
    }
    
}

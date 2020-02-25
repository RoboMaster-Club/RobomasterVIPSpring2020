int enableA = 5;
int enableB = 6;
int phaseA = 8;
int phaseB = 7;
int modePin = 4;

int testMode = 1; // what test to run, 1: duty cycle from 100% to 0%, 2: change phase at 100% duty cycle

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
        digitalWrite(enableA, 0);
        digitalWrite(enableB, 0);

        delay(1000);

        digitalWrite(enableA, 1);
        digitalWrite(enableB, 1);

        delay(1000);
    }
}
/*
 * Motor1 pins
 */
int In1 = 8; 
int In2 = 9;
int EnA = 10;

/*
 * Motor2 pins
 */
int In3 = 11;
int In4 = 12;
int EnB = 13;

void setup()
{
    pinMode(In1,OUTPUT);
    pinMode(In2,OUTPUT);
    pinMode(EnA,OUTPUT);
    pinMode(In3,OUTPUT);
    pinMode(In4,OUTPUT);
    pinMode(EnB,OUTPUT);
}

void loop()
{
    int speed;

    /* Set motor1 direction clockwise */
    digitalWrite(In1, HIGH);
    digitalWrite(In2, LOW);

    /* Set motor1 direction anticlockwise */
    digitalWrite(In3, LOW);
    digitalWrite(In4, HIGH);

    /* Start */
    analogWrite(EnA, 50);
    analogWrite(EnB, 50);
    delay(2000);

    /* Speed up */
    for (speed = 50; speed <= 255; speed += 5)
    {
        analogWrite(EnA, speed);
        analogWrite(EnB, speed);
        delay(100);
    }

    /* Speed keeping */
    analogWrite(EnA, 255);
    analogWrite(EnB, 255);
    delay(3000);

    /* Speed down */
    for (speed = 255; speed >= 0; speed -= 5)
    {
        analogWrite(EnA, speed);
        analogWrite(EnB, speed);
        delay(100);
    }

    /* Stop */
    analogWrite(EnA, 0);
    analogWrite(EnB, 0);
    delay(2000);        
}


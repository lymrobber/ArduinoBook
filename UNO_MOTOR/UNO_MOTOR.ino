int In1 = 8;
int In2 = 9;
int EnA = 10;
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
    digitalWrite(In1,HIGH);
    digitalWrite(In2,LOW);
    analogWrite(EnA, 127);

    digitalWrite(In3,HIGH);
    digitalWrite(In4,LOW);
    analogWrite(EnB, 127);

    delay(5000);
    
    analogWrite(EnA, 255);
    analogWrite(EnB, 255);

    delay(5000);

    digitalWrite(In1,LOW);
    digitalWrite(In2,LOW);
    digitalWrite(In3,LOW);
    digitalWrite(In4,LOW);
    
    delay(2000);

    digitalWrite(In2,HIGH);
    digitalWrite(In1,LOW);
    analogWrite(EnA, 127);

    digitalWrite(In4,HIGH);
    digitalWrite(In3,LOW);
    analogWrite(EnB, 127);

    delay(5000);
    
    analogWrite(EnA, 255);
    analogWrite(EnB, 255);

    delay(5000);

    digitalWrite(In1,LOW);
    digitalWrite(In2,LOW);
    digitalWrite(In3,LOW);
    digitalWrite(In4,LOW);
    
    delay(2000);
}


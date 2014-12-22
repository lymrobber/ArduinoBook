int relay_pin = 2;
char cmd[10];
bool valid_cmd = false;

void setup()
{
    pinMode(relay_pin, OUTPUT);
    Serial.begin(9600);
}

void loop()
{
    int i;
    
    if (Serial.available() > 0)
    { 
        for (i = 0; i < 10; i++)
        {
            cmd[i] = '\0';
        }   
        
        for (i = 0; i < 9; i++)
        {   
            if (Serial.available() > 0)
            {
                cmd[i] = Serial.read();
                delay(1);
            }
            else
            {
                break;
            }
        }
        valid_cmd = true;
    }
    
    if (valid_cmd)
    {
        if (0 == strncmp(cmd, "on", 2))
        {
            digitalWrite(relay_pin, HIGH);
            Serial.println("O");
        }
        else if (0 == strncmp(cmd, "off", 3))
        {
            digitalWrite(relay_pin, LOW);
            Serial.println("O");
        }
        else
        { 
            Serial.println("X");
        }
        valid_cmd = false;
    }
    delay(10);
}

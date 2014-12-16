int relay_pin = 2;
char cmd[10];
bool valid_cmd = false;

void setup()
{
    pinMode(relay_pin, OUTPUT);
    Serial.begin(9600);
    Serial.println("I'am ready");
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
                //Serial.write(cmd[i]);
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
        valid_cmd = false;
        if (0 == strncmp(cmd, "on", 2))
        {
            digitalWrite(relay_pin, HIGH);
            Serial.println("commmand:on");
        }
        else if (0 == strncmp(cmd, "off", 3))
        {
            digitalWrite(relay_pin, LOW);
            Serial.println("commmand:off");
        }
        else
        { 
        }
    }
    delay(10);
}

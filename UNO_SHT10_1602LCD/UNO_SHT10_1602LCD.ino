#include <SHT1x.h>

float temp_c;
float temp_f;
float humidity;

SHT1x sht1x(A4, A5);

void setup() 
{ 
    Serial.begin(9600); 
}

void loop() 
{ 
    temp_c      = sht1x.readTemperatureC();
    temp_f      = sht1x.readTemperatureF();
    humidity    = sht1x.readHumidity();
    
    Serial.println("sc;");

    Serial.println("sd0,0;");
    Serial.println("ssSHT10 Hum:;");
    
    Serial.println("sd0,10;");
    Serial.print("ss");
    Serial.print(int(humidity));
    Serial.println("(%);");
    
    Serial.println("sd1,0;");
    Serial.println("ssT:;");
    Serial.println("sd1,2;");
    Serial.print("ss");
    Serial.print(int(temp_c));
    Serial.println("(C);");
    
    Serial.println("sd1,10;");
    Serial.print("ss");
    Serial.print(int(temp_f));
    Serial.println("(F);");
    
    delay(1000);
}

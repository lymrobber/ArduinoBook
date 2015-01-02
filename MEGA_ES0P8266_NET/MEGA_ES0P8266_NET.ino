/*
ESP8266 library

When you use it with MEGA board, the connection should be like these:
ESP8266_TX->RX1(D19)
ESP8266_RX->TX1(D18)
ESP8266_CH_PD->3.3V
ESP8266_VCC->3.3V
ESP8266_GND->GND

*/


#include "uartWIFI.h"
#include <SoftwareSerial.h>

#define SSID       "ITEAD"
#define PASSWORD   "12345678"
#define server      "www.baidu.com"    

WIFI wifi;


void setup()
{
    static bool ret = false;
    
    DebugSerial.begin(9600);
    DebugSerial.println("Serial begin...");
    
    wifi.begin();
    bool tem = wifi.Initialize(STA, SSID, PASSWORD);
    if(!tem)
    {
        DebugSerial.println("Init error");
    }
    
    delay(8000);  
    
    String ipstring  = wifi.showIP();
    DebugSerial.println(ipstring);

    if(wifi.ipConfig(TCP,server, 80))
    {
        DebugSerial.println("connecting...");

        while(!ret)
        {
            // send the HTTP PUT request:
            ret = wifi.Send("GET / HTTP/1.0\r\n\r\n");
           
            //DebugSerial.println("Send error!");
        }
        DebugSerial.println("Be able to recv data.");

    }
    
    pinMode(13,OUTPUT);
}


void loop()
{
    char message[320];


    if(wifi.ReceiveMessage(message)) 
    {
        DebugSerial.println(message);
        memset(message, 0, 320);
    }

    //delay(10);
  
}




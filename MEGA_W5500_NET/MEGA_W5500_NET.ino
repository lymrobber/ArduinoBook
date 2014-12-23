#include <SPI.h>
#include <Ethernet.h>


byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
char server[] = "www.baidu.com";


EthernetClient client;

void setup()
{
    int ret = 0;
    //config UART
    Serial.begin(9600);
    Serial.println("UART has initial....");


    /*Config ip address*/
    ret = Ethernet.begin(mac);
    delay(1000);

    /* Connect server,and Get server data */
    if(client.connect(server, 80))
    {
        Serial.println("Net connected ok!");
        
        client.println("GET /s?wd=arduino HTTP/1.1");
        client.println("Host: www.baidu.com");
        client.println("Connection: close");
        client.println();
    }
    else
    {
        //Connect failed
        Serial.println("Net connect error!");
    }
    
}


/* Print the data of recv at the UART */
void loop()
{
    char c;
    if(client.available())
    {
        c = client.read();
        Serial.print(c);
    }

}


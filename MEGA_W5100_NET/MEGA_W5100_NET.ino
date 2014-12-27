
#include <SPI.h>
#include <Ethernet.h>

#define RST_pin     25

uint8_t mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xBE};
char server[] = "www.baidu.com";    


EthernetClient client;

void setup() 
{
    // Open serial communications and wait for port to open:
    Serial.begin(9600);
    Serial.println("UART has passed!");
    while (!Serial) 
    {
        ; // wait for serial port to connect. Needed for Leonardo only
    }
    Serial.println("Hello, Boy!");
    delay(2000);

#if 1
    pinMode(RST_pin, OUTPUT);
    digitalWrite(RST_pin, LOW);
    delay(1000);
    digitalWrite(RST_pin, HIGH);
    delay(1000);
#endif

    Serial.println("Reset the w5100!");

    Ethernet.begin(mac);

    delay(1000);
    Serial.println("connecting...");

    // if you get a connection, report back via serial:
    // Make a HTTP request:
    if (client.connect(server, 80)) 
    {
        Serial.println("connected");

        client.println("GET /s?wd=arduino HTTP/1.1");
        client.println("Host: www.baidu.com");
        client.println("Connection: close");
        client.println();
    }
    else 
    {
        Serial.println("connection failed");
    }

}

void loop()
{
    // if there are incoming bytes available
    // from the server, read them and print them:
    if (client.available()) 
    {
        char c = client.read();
        Serial.print(c);
    }

    // if the server's disconnected, stop the client:
    if (!client.connected())
    {
        Serial.println();
        Serial.println("disconnecting.");
        client.stop();

        // do nothing forevermore:
        while (true);
    }


}


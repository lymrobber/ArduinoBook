/* UNO Recv Demo */
#include <SPI.h>
#include <NRF24L01P.h>
#include <Servo.h> 

#define SERVO_PIN 2

Servo myservo; 
NRF24L01P rf24l01p;
uint8_t buffer[24]; /* Must be 24 Byte */
uint8_t from[5] = {0}; 
uint8_t addr[5] = {0x11, 0x22, 0x33, 0x44, 0x02};

void setup()
{
    Serial.begin(9600);
    myservo.attach(SERVO_PIN);
    rf24l01p.begin(9, 10, PWR_0dBm, AIR_RATE_2Mbps, 50, addr);
}

void loop()
{
    rf24l01p.recv_packet(from, buffer);
    if (buffer[0] >= 0 && buffer[0] <= 179)
    {
        myservo.write(buffer[0]); 
        delay(15);
    }
}


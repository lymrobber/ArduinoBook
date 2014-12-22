/* MEGA Send Demo */
#include <SPI.h>
#include <NRF24L01P.h>

#define ROCKER_PIN A0

NRF24L01P rf24l01p;
uint8_t buffer[24];
uint8_t to[5] = {0x11, 0x22, 0x33, 0x44, 0x02}; /* Must be 5 Byte */
uint8_t addr[5] = {0x11, 0x22, 0x33, 0x44, 0x01}; /* Must be 24 Byte */
int8_t ret;
int val;
int pos;

void setup()
{
    Serial.begin(9600);
    rf24l01p.begin(27, 53, PWR_0dBm, AIR_RATE_2Mbps, 50, addr);
}

void loop()
{
    val = analogRead(ROCKER_PIN);
    pos = map(val, 0, 1023, 0, 179);
    buffer[0] = pos;
    rf24l01p.send_packet(to,buffer);
    delay(100);
}

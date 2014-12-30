#include <IoTgo_device.h>
#include <SoftwareSerial.h>
#include <SPI.h>


#define SWITCH_APIKEY        "d8742379-9aca-45d9-8ff4-f4caf68156fa"
#define SWITCH_ID            "0100000006"
#define SWITCH_CHECK_CODE    ""


/* 
 * The SSID (more generally, WiFi's name) for accessing to internet.
 * Maybe you need to replace "ITEAD" with yours. 
 */
#define WIFI_SSID           "ITEAD"

/* 
 * The SSID's password
 * Is it the same to yours? if not, change it.
 */
#define WIFI_PASS           "12345678"
static ESP8266 eth;

/*
 * IP address or domain name of IoTgo platform servers. 
 * Maybe you need to change it.
 */
#define IOT_SERVER          "iotgo.iteadstudio.com"
#define IOT_DOMAIN_NAME     "iotgo.iteadstudio.com"

#define SWITCH_PIN           (23)

/* 
 * The control button of switch
 */
#define BUTTON_PIN               (3)

static Switch sw(&eth, SWITCH_PIN);
static int interrupt_ret = 0;
static int32_t state;

void interrupt_Parse()
{
    Serial.println("Go interrupt!");
    noInterrupts();
    delay(100);
    if (digitalRead(BUTTON_PIN) == HIGH)
        interrupt_ret = 1;
    else
        interrupt_ret = 0;
    interrupts();
}

void setup()
{
    const char *apikey;
        
    Serial.begin(9600);
    Serial.println("Serial begin");

    pinMode(25, OUTPUT);
    digitalWrite(25, LOW);
    delay(1000);
    digitalWrite(25, HIGH);
    delay(2000);
    
    /* Config the Net */
    if (!eth.connectWiFi(WIFI_SSID, WIFI_PASS))
    {
        Serial.println("Connect WiFI error and halt...");
        while(1);
    }
    
    sw.setHost(IOT_SERVER, IOT_DOMAIN_NAME);

    Serial.println("Connecting device to server...");
    apikey = sw.init(SWITCH_ID, SWITCH_APIKEY);
    //apikey = sw.init(SWITCH_ID, SWITCH_CHECK_CODE, DEVICE_PRODUCT);
    Serial.print("apikey = ");
    Serial.println(apikey);

    /* Get the state of switch */
    if(sw.getState(&state))
    {
        Serial.println("GetState err! halt now...");
        while(1); 
    }

    /* Synchronize the state of light */
    if(SWITCH_STATE_ON == state)
    {
        sw.on();
    }
    else
    {
        sw.off();
    }

    attachInterrupt(1, interrupt_Parse, RISING);

    Serial.println("Setup done.");
    
}

void loop()
{
    int32_t ret;

    noInterrupts();
    if(interrupt_ret == 1)
    {
        interrupt_ret = 0;
        interrupts();
                
        if(state == SWITCH_STATE_ON)
        {
            sw.off();
            state = SWITCH_STATE_OFF;
        }
        else if(state == SWITCH_STATE_OFF)
        {
            sw.on();
            state = SWITCH_STATE_ON;
        }
    }
    else
    {
        interrupts();
    }

    /* Synchronize the state of light */
    ret = sw.sync();
    if(!ret)
    {
        Serial.println("Sync okay");
    }
    else
    {
        Serial.print("sync() err! ret = ");
        Serial.println(ret);
    }
}



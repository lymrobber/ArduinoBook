#include <IoTgo_device.h>
#include <SoftwareSerial.h>
#include <SPI.h>



#define THSENSOR_ID             "030000000a"
//#define THSENSOR_CHECK_CODE     ""
#define THSENSOR_APIKEY         "d8742379-9aca-45d9-8ff4-f4caf68156fa"

#define IOT_SERVER          "iotgo.iteadstudio.com"
#define IOT_DOMAIN_NAME     "iotgo.iteadstudio.com"

//The Reset pin about w5100
#define reset_pin               (25)

//The pin of SHT1x 
#define THSENSOR_DATA_PIN       (23)
#define THSENSOR_CLOCK_PIN      (24)


static EthW5X00 eth;
uint8_t mac[] = {0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff};


SHT1x sht1x(THSENSOR_DATA_PIN, THSENSOR_CLOCK_PIN);
THSensor th(&eth, &sht1x);


void setup()
{
    const char *api_key;
    Serial.begin(9600);

    //Reset w5100
    pinMode(reset_pin, OUTPUT);
    digitalWrite(reset_pin, LOW);
    delay(1000);
    digitalWrite(reset_pin, HIGH);
    delay(2000);

    //Initial the network and connect TCP
    if(!eth.configW5X00(mac))
    {
        Serial.println("Intialize w5x00 failed!");
    }
    delay(1000);

    //Initial the SHT1x device
    th.begin();
    th.setHost(IOT_SERVER, IOT_DOMAIN_NAME);

    Serial.println("Connecting device to server..");

    //Request response of IoTgo platform
    api_key = th.init(THSENSOR_ID, THSENSOR_APIKEY);
    //api_key = th.init(THSENSOR_ID, THSENSOR_CHECK_CODE, DEVICE_PRODUCT);
    Serial.print("api_key = ");
    Serial.println(api_key);    
    
    Serial.println("setup done.");
    
}


void loop()
{
    static int32_t ret;
    static int32_t counter = 0;
    
    Serial.print("\ncounter = ");
    Serial.println(++counter);

    //Synchronize state on the IoTgo
    ret = th.sync();
    if (ret)
    {
        Serial.print("ERROR: sync() = ");
        Serial.println(ret);
    }
    else
    {
        Serial.println("sync successfully!");
    }

    delay(1000);
    
}


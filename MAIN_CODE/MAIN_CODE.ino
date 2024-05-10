#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>
#include <DHT.h>
#include <MQUnifiedsensor.h>

#define REMOTEXY_MODE__SOFTSERIAL // To Define RemoteXY (Must Be Before Including Library)
#include <RemoteXY.h>


SoftwareSerial BT(A5, A4); // TX ==> A5  RX ==> A4

/*
#define RST_PIN 9 // RFID Module
#define SDA_PIN 10 // RFID Module
#define BUZZER_REDLED A2
#define RELAY_GREENLED A3
*/

#define PIN_GREENLED 9
#define PIN_REDLED 10 
#define PIN_WHITELED 11 
#define PIN_BUZZER 13
#define PIN_BUZZER_ALERT 12
#define PIN_LOCK A2
#define PIN_SERVO 6
#define DHTPIN A1     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11   // DHT 11
#define MQ5PIN A0    // Analog pin connected to the MQ-5 sensor
#define REMOTEXY_SERIAL_RX A4
#define REMOTEXY_SERIAL_TX A5
#define REMOTEXY_SERIAL_SPEED 9600
#define REMOTEXY_ACCESS_PASSWORD "1234"

#pragma pack(push, 1)  
uint8_t RemoteXY_CONF[] =   // 290 bytes
  { 255,6,0,33,0,27,1,17,0,0,0,69,1,106,200,2,1,0,8,0,
  67,59,14,40,10,5,31,59,11,67,58,54,40,10,5,31,59,11,129,7,
  15,40,7,59,84,101,109,112,101,114,97,116,117,114,101,0,129,8,54,32,
  8,59,72,117,109,105,100,105,116,121,0,2,33,89,44,22,1,44,59,31,
  31,79,78,0,79,70,70,0,131,86,182,14,14,1,57,2,31,80,97,103,
  101,0,6,129,28,117,51,12,59,68,111,111,114,32,108,111,99,107,0,67,
  34,146,40,10,1,8,69,11,11,0,2,59,54,36,12,0,45,59,31,31,
  79,78,0,79,70,70,0,129,5,37,34,9,8,82,101,100,32,76,69,68,
  0,129,4,16,41,9,8,87,104,105,116,101,32,76,69,68,0,129,5,56,
  42,9,8,71,114,101,101,110,32,76,69,68,0,4,85,79,14,48,0,73,
  26,1,42,135,24,24,0,73,31,0,129,8,100,61,10,8,68,111,111,114,
  32,80,111,115,105,116,105,111,110,0,129,44,165,20,12,8,66,101,108,108,
  0,131,7,181,14,14,1,57,2,31,80,97,103,101,0,9,2,59,34,36,
  12,0,45,59,31,31,79,78,0,79,70,70,0,2,59,14,36,12,0,45,
  59,31,31,79,78,0,79,70,70,0 };
  
// this structure defines all the variables and events of your control interface 
struct {

    // input variables
  uint8_t Lock; // =1 if switch ON and =0 if OFF
  uint8_t GREEN_LED; // =1 if switch ON and =0 if OFF
  int8_t POS; // from 0 to 100
  uint8_t BUZZER; // =1 if button pressed, else =0
  uint8_t RED_LED; // =1 if switch ON and =0 if OFF
  uint8_t WHITE_LED; // =1 if switch ON and =0 if OFF

    // output variables
  char temp[11]; // string UTF8 end zero
  char hum[11]; // string UTF8 end zero
  char Alert[11]; // string UTF8 end zero

    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0

} RemoteXY;   
#pragma pack(pop)

DHT dht(DHTPIN, DHTTYPE); // Difine DHT Sensor Type

/*
MFRC522 rfid(SDA_PIN, RST_PIN); // Instance of the class
byte NUID_PICC[4]; // Initiate Array To Store New NUID
byte BlueID[4] = {0x45, 0xAD, 0x81, 0xEF}; // Blue Card UID
byte WhiteID[4] = {0xA6, 0xAC, 0xE1, 0xEF}; // White Card UID
*/

Servo myservo;  // create servo object to control a servo
// short pos; // servo position 

const char rs = 7, en = 8, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7); // Initialize the library with the numbers of the interface pins

float T; // Temperature In celsius
float H; // Humidity
float F; // Temperature In Fahrenheit

long time1, time2, time3, time4;

void setup() {
  Serial.begin(9600); // Sets the data rate in bits per second (baud) for serial data transmission. For communicating with Serial Monitor 

  BT.begin(9600); // Bluetooth Data Transfer Rate 
  RemoteXY_Init(); // Initiate RemoteXY Application

  myservo.attach(PIN_SERVO);
  RemoteXY.POS = 0; // Start Position Of Slider 
  pinMode(MQ5PIN, INPUT);

  pinMode(PIN_LOCK, OUTPUT);
  pinMode(PIN_BUZZER, OUTPUT);
  pinMode(PIN_WHITELED, OUTPUT);
  pinMode(PIN_REDLED, OUTPUT);
  pinMode(PIN_GREENLED, OUTPUT);
  pinMode(PIN_BUZZER_ALERT, OUTPUT);
  
  /*
  pinMode(BUZZER_REDLED, OUTPUT); 
  pinMode(RELAY_GREENLED, OUTPUT); 
  digitalWrite(RELAY_GREENLED, LOW);
  */

  dht.begin(); // Initiate DHT11 Sensor
  
  /*
  SPI.begin(); // intitiate SPI bus
  rfid.PCD_Init(); // initiate RFID-RC522
  */

  lcd.begin(16, 2);
  lcd.print("     WELCOME    ");
  delay(1000);

  time1 = millis();
}

void loop() {
  H = dht.readHumidity(); // Read humidity
  T = dht.readTemperature(); // Read Temperature In Celsius
  F = dht.readTemperature(true); // Read Tempreture In Fahrenheit 

  if(millis() - time1 >= 100){
    // RFID();
    time1 = millis();
  } else if (millis() - time2 >= 500){
    temp_hum();
    time2 = millis();
  } else if (millis() - time3 >= 5){
    gas_sensor();
    time3 = millis();
  } else if (millis() - time4 >= 5){
    remoteControl();
    time4 = millis();
  }
}

void LcdInitialization()
{
  lcd.clear();
  lcd.print("     WELCOME    ");
  delay(10);
}

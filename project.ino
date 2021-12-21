//PLEASE INCLUDE LIBRARIES FOR DHT11,LCD,SOFTWARE SERIAL,AND RTC BEFORE RUNNING THIS CODE

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include "RTClib.h"
RTC_DS1307 rtc;  
SoftwareSerial xbee(0,1);                   // connect Xbee to pin D0 and D1
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);   //lcd(RS,E,D4,D5,D6,D7)
#define DHTTYPE DHT11                     // #define DHTTYPE DHT22  //for DHT22 Sensor
int DHTPIN = A1;                         // connect DTH11 to pin A1
int SensorMost = A0;                    // connect Soil moisture Sensor to A0
int fan = 6;                           // connect Relay Connected Fan to pin D6
int motor = 7;                        // connect Relay Connected Motor pump to pin D7
DHT dht(DHTPIN, DHTTYPE);
int Pastmotor,Presentmotor,Presentfan,Pastfan,SensorValue,PastValue,Temp,PTemp,Hum;
String FanState,MotorState;


void setup() {
  pinMode(motor, OUTPUT);
  pinMode(fan, OUTPUT);
  lcd.begin(20, 4);
  dht.begin();
  xbee.begin(9600);             //Baud rate set to 9600
  lcd.setCursor(7,1);
  lcd.print("WELCOME");

  rtc.adjust(DateTime(2020, 1, 21, 3, 0, 0));     //user specific date and time
//rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); //present date and time

  xbee.println("                   IOT IRRIGATION");
  xbee.println();
  delay(1000);
}

void loop() {

  PastValue = SensorValue;
  PTemp = Temp;
  SensorValue = analogRead(SensorMost)*0.1;   //converting the sensor value to the sacle of 0 to 100 
  Hum = dht.readHumidity();
  Temp = dht.readTemperature();
  DateTime now = rtc.now();

  //Displaying all values in LCD
  lcd.setCursor(0,0);
  lcd.print("Moisture: ");
  lcd.setCursor(10, 0);  
  lcd.print(SensorValue);
  lcd.setCursor(13, 0);
  lcd.print("%");     
  lcd.setCursor(0, 1);  
  lcd.print("Temperature: ");
  lcd.setCursor(13, 1);
  lcd.print(Temp);
  lcd.setCursor(16, 1);
  lcd.print("*C");
  lcd.setCursor(0, 2);
  lcd.print("Humidity: ");
  lcd.setCursor(10, 2);
  lcd.print(Hum);
  lcd.setCursor(1, 3);
  
  //Algorithm for soil moisture
  if(SensorValue < 30) {
  digitalWrite(motor, HIGH);
  lcd.print("MOTOR  ON");
  MotorState = "MOTOR ON";
  Presentmotor = 1; }
  else if(SensorValue > 50 && Hum>60){
  digitalWrite(motor, LOW);
  lcd.print("HUMID CON");
  MotorState = "MOTOR OFF";
  Presentmotor = 0;  }
  else if(SensorValue > 70){
  digitalWrite(motor, LOW);
  lcd.print("MOTOR OFF");
  MotorState = "MOTOR OFF";
  Presentmotor = 0; 
  }
  //Algorithm for Humidity
  if(PastValue < 30) {
    Pastmotor = 1; }
  else if (PastValue > 50 && Hum>60) {
    Pastmotor = 0; }
  else if (PastValue > 70){
    Pastmotor = 0; }

  lcd.setCursor(12, 3);
  
  //Algorithm for Temperature
  if(Temp > 30) {
  digitalWrite(fan, HIGH);
  lcd.print("FAN  ON");
  FanState = "FAN ON";
  Presentfan = 1; }
  else if(Temp < 20){
  digitalWrite(fan, LOW);
  lcd.print("FAN OFF");
  FanState = "FAN OFF";
  Presentfan = 0;
  }

  if(PTemp > 30) {
    Pastfan = 1; }
  else if (PTemp < 20) {
    Pastfan = 0; }
    
  //Sending values through Xbee only if there is any change in the Fan or Motorpump State
  if(Pastmotor>Presentmotor || Presentmotor>Pastmotor || Pastfan>Presentfan || Presentfan>Pastfan){
  xbee.print("Moisture: ");
  xbee.print(SensorValue);
  xbee.println(" %");
  xbee.print("Temperature: ");
  xbee.print(Temp);
  xbee.println(" F");
  xbee.print("Humidity: ");
  xbee.println(Hum);
  xbee.println(MotorState);
  xbee.println(FanState);
  xbee.print("Time: ");
  xbee.print(now.hour(), DEC);
  xbee.print("HR : ");
  xbee.print(now.minute(), DEC);  //Time will also be updated simultaneously
  xbee.print("MIN : ");
  xbee.print(now.second(), DEC);
  xbee.println("SEC");
  xbee.println();
  }
  delay(10);
}

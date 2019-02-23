/*#include <RH_ASK.h>
#include <SPI.h> // Not actually used but needed to compile

RH_ASK driver;

void setup()
{
    Serial.begin(9600); // Debugging only
    pinMode(2, INPUT_PULLUP);
    pinMode(13,OUTPUT);
    if (!driver.init())
         Serial.println("init failed");
}

void loop()
{
    int s = digitalRead(2);
    Serial.println(s);
    if(s==HIGH){
      digitalWrite(13,LOW);
      const char *msg = "00";
      Serial.println("Sending 00.");
      driver.send((uint8_t *)msg, strlen(msg));
      driver.waitPacketSent();
    }
    else{
      digitalWrite(13,HIGH);
      const char *msg = "11";
      Serial.println("Sending 11.");
      driver.send((uint8_t *)msg, strlen(msg));
      driver.waitPacketSent();
    }
      delay(1000);
}*/
/*
Sending random remote commands 
ESP   433(TX)
GND - GND
D8 - DATA
VCC -  5V
*/

#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();

void setup() {

  Serial.begin(9600);
  pinMode(2,INPUT_PULLUP);
  // Transmitter is connected to nodeMCU pin D8
  mySwitch.enableTransmit(10);
  /*
  //Setting pins for plugnplay
  
  pinMode(10,OUTPUT);
  digitalWrite(10,HIGH);
  pinMode(9,OUTPUT);
  digitalWrite(9,LOW);*/
  // Optional set pulse length.
  // mySwitch.setPulseLength(320);
  
  // Optional set protocol (default is 1, will work for most outlets)
  // mySwitch.setProtocol(2);
  
  // Optional set number of transmission repetitions.
  // mySwitch.setRepeatTransmit(15);
  
}

void loop() {
  int s = digitalRead(2);
  Serial.println(s);
  if(s==HIGH){
  mySwitch.send(10, 24);
  delay(1000);
  }
  else{  
  mySwitch.send(20, 24);
  delay(1000);
}
}

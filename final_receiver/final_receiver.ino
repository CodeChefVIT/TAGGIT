#include <Firebase.h>
#include <FirebaseArduino.h>
#include <FirebaseCloudMessaging.h>
#include <FirebaseError.h>
#include <FirebaseHttpClient.h>
#include <FirebaseObject.h>

#include <ESP8266WiFi.h>
#include <RCSwitch.h>


// Set these to run example.
#define WIFI_SSID "abc"
#define WIFI_PASSWORD "abcd1234"

#define FIREBASE_HOST "taggit-f34cc.firebaseio.com"
#define FIREBASE_AUTH "qb1qEjvE0gkaOhiTobtWTxGLjBxkzAtuNTrBL9Lu"

RCSwitch mySwitch = RCSwitch();


void setup() {
  Serial.begin(9600);

  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  mySwitch.enableReceive(D4);  //D4 pin on the nodeMCU is pin D4, in AVR Arduino's you should fill in the interrupt pin (0,1)

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop() {
if (mySwitch.available()) {
  int val  = mySwitch.getReceivedValue(); 
    if (val==0) {
      Serial.print("Unknown encoding");
    } 
    else {
      Serial.print("Received ");
      if(mySwitch.getReceivedValue()==20){

        Firebase.setFloat("number", 1);
        // handle error
        if (Firebase.failed()) {
        Serial.print("setting /number failed:");
        Serial.println(Firebase.error());  
        return;
        }
        delay(1000);
        // get value 
        Serial.print("number: ");
        Serial.println(Firebase.getFloat("number"));
        delay(1000);
      }

    }
    
    mySwitch.resetAvailable();  

}
}

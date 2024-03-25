#include "ThingSpeak.h"
#include <SPI.h>
#include <WiFiNINA.h>

//Temperature
const int temp = A1;
int baselineTamp = 40;
int celsuis = 0;
int fahrenheit = 0;

char ssid[] = ""; // my network SSID 
char pass[] = ""; // my network password
int status = WL_IDLE_STATUS; // wifi radio's status

unsigned long myChannelNumber = ; // your channel from thingspeak
const char * myWriteAPIKey = ""; // your API from thingspeak

WiFiClient client;

void setup() {
  //initi the temp sensor
  pinMode(temp, INPUT);

  Serial.begin(9600); // initialize the serial monitor
  //while(!Serial);
  Serial.println("Attempting to connect to WPA network..."); // WPA2 attempt
  status = WiFi.begin(ssid,pass); // connect to the wifi and gets its status
  if(status != WL_CONNECTED){ // check if the wifi is not connected
    Serial.println("Couldn't get a wifi connection");//if not connected print message
    while(true);//keeps looping until it connects
  }
  else{
    Serial.print("Connected to network: ");//if connected print the message
    Serial.println(ssid);
  }
  //thingspeak stuff
  ThingSpeak.begin(client);//connecting to the thingspeak channel
  Serial.println("\nWaiting for first update...");
  delay(1000); //wait for 1 sec


}

void loop() {
  baselineTamp = 40;
  celsuis = map(((analogRead(temp) - 20) * 3.04), 0, 1023, -40, 125);
  fahrenheit = ((celsuis * 9) / 5 + 32); // convert the celsuis to fahrenheit
  //send reading to thingspeak
  ThingSpeak.setField(1,fahrenheit); //set what field to write the value
  ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey); // write the value to the channel
  Serial.println("message sent to cloud"); // print message
  delay(1000);//wait for 1 sec

}

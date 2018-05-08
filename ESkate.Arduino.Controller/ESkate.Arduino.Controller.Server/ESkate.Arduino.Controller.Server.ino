/*
* Arduino Wireless Communication Tutorial
*     Example 1 - Transmitter Code
*                
* by Dejan Nedelkovski, www.HowToMechatronics.com
* 
* Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
*/

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

int messageId = 0;

RF24 radio(9, 10); // CE, CSN

const byte address[6] = "00001";

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}

void loop() {  
  messageId++;  
  char text[50];
  sprintf(text,"Controller heartbeat, id %d",messageId); 
  int res = radio.write(&text, sizeof(text));
  Serial.print("send status ");
  Serial.println(res);
  Serial.print("heartbeat sent ");
  Serial.println(messageId);
  delay(50);
}

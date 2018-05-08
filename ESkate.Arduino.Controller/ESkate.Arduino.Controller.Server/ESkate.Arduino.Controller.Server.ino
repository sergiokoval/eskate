#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

int heartBeatMessageId = 0;

RF24 radio(9, 10); // CE, CSN

const byte addresses[][6] = { "00001", "00002" };

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(addresses[1]);
  radio.openReadingPipe(1,addresses[0]);
  radio.setPALevel(RF24_PA_MIN);  
}

void loop() {  
  heartBeatMessageId++;  
  char text[50];
  sprintf(text,"server heartbeat, id %d",heartBeatMessageId); 
  radio.stopListening();
  int res = radio.write(&text, sizeof(text));
  Serial.print("send status ");
  Serial.println(res);
  Serial.print("heartbeat sent ");
  Serial.println(heartBeatMessageId);

  delay(5);
  radio.startListening();  
  if(radio.available()){
  char text2[50]; 
  radio.read(&text2, sizeof(text2));
  Serial.print("client data - ");
  Serial.println(text2);
  }
  delay(500);
}

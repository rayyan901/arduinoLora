#include <SoftwareSerial.h>

SoftwareSerial mySerial(6, 7); // RX, TX



const int LED =  13;   
const int Enable =  2;
const int retry=5;
char mystr[20]; 
void setup() 
{ 
  mySerial.begin(9600);
  Serial.begin(9600);
  Serial.setTimeout(300);
  mySerial.setTimeout(250);

  Serial.println("initializing...");

  pinMode(LED, OUTPUT);
  pinMode(Enable, OUTPUT);
  
  digitalWrite(LED, LOW); 
  
  digitalWrite(Enable, HIGH);


}
 char data;
 int count=0,c1=0;
 int slaveNumber=1,retSlave;
void loop() 
{ 
  for(int j=1;j<6;j++){
  for(int i=0; i<retry; i++){
  slaveNumber=j;
  retSlave=getData(slaveNumber);
  if (retSlave==slaveNumber){
    i=retry;
  }
  delay(300);
  }
  }

//===========

//==      
      Serial.println();
      Serial.println(count);
      Serial.println();
     // delay(500);
      count++;
      if(count>100)
        count=0;
}

int getData(int slaveNumber) {
  bool noR=0;
  int count=0,slave=0;
  digitalWrite(Enable, HIGH);
  delay(5);
  mySerial.print('I');
  mySerial.print(slaveNumber);
  mySerial.print('L');
  mySerial.print('F');
  mySerial.print('F');
  mySerial.flush();
  delay(2);
  digitalWrite(Enable, LOW);
  
  //------------------------
  delay(5);
   while(Serial.available()== 0 && count<30000){
   //noR=0;
   count++;
   delayMicroseconds(1);
   }
   //Serial.println(count);
   if(count>29000){
    
    noR=1;
}
if(Serial.available()){
  delay(100);
 // Serial.println(Serial.available());
 // Serial.readBytesUntil('f',mystr,20);
 // Serial.println(mystr);
//}
   //===
   //while(Serial.available()== 0);
   if (Serial.find('i'))
  {

     slave = Serial.parseInt();
      
    
    float anglex = Serial.parseFloat();
    
    float angley = Serial.parseFloat();
    
   // Serial.readBytesUntil('f',mystr,20);
    Serial.print(slave);
    Serial.print(':');
    Serial.print(anglex);
    Serial.print(',');
    Serial.println(angley);
    Serial.println();
    //Serial.print(mystr);
    while(Serial.available()){
      Serial.read();
    }
    
  } else {
    Serial.print("timeout s:");
    Serial.println(slaveNumber);
    while(Serial.available()){
      Serial.read();
    }
    if(!noR){
     // Serial.readBytesUntil('f',mystr,16);
     // Serial.println(mystr);
    }
  }
}
if(noR){
  //delay(100);
  Serial.print("no Resp:");
  Serial.println(slaveNumber);
}
return(slave);
}

#include <SoftwareSerial.h>

SoftwareSerial mySerial(6, 7); // RX, TX


const int Enable =  2; 
const int SlaveNumber = 1;

void setup() 
{ 
  mySerial.begin(9600);
  Serial.begin(9600);  
  Serial.setTimeout(250);
  pinMode(Enable, OUTPUT);
  digitalWrite(Enable, LOW);
  pinMode(13, OUTPUT);
   digitalWrite(13, LOW);
  Serial.println("init...");
} 
char inc;
int count=0;
float anglex=12.67, angley=-9.83;
void loop() 
{ 
  if(Serial.available())
  //if (mySerial.available())
  {


if(Serial.read()=='I')
    {   
      Serial.println('I');
      int Slave = Serial.parseInt();
      Serial.println(Slave);
        if(Slave == SlaveNumber)
        {   
            //char command = Serial.read();       
             Serial.print(Slave);
             if(Serial.read()=='L')
             {
              Serial.print('L');
              char command = Serial.read();
                if(command =='F')
                 {
                   Serial.print('F');
                    delay(5);    
                   digitalWrite(Enable, HIGH);
                   
                   mySerial.print("$U$i");
                   mySerial.print(SlaveNumber);
                   mySerial.print(',');   
                   mySerial.print(anglex,2);
                   mySerial.print(',');   
                   mySerial.print(angley,2);
                   mySerial.print("f");
                   mySerial.flush();
                   
                   digitalWrite(Enable, LOW); 
                   Serial.println("N");  
                   anglex+=0.01;        
                 } else {
                  Serial.print(command);
                 }
             }
             
        }else {
          while(Serial.available()){
                Serial.read();
           }
        }
    }else {
          while(Serial.available()){
                Serial.read();
           }
        }

  }
  
  delay(10);
}

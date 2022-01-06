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
  pinMode(A0, INPUT);
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
      //Serial.println("m");
      int Slave = Serial.parseInt();
        if(Slave == SlaveNumber)
        {   
            char command = Serial.read();       
             
             if(command == 'L')
             {
                if(Serial.read()=='F')
                 {
                   
                        
                   digitalWrite(Enable, HIGH);
                   
                   mySerial.print("$U$i");
                   mySerial.print(SlaveNumber);
                   mySerial.print(',');   
                   mySerial.print(anglex,2);
                   mySerial.print(',');   
                   mySerial.print(angley,2);
                   mySerial.print("f");
                   mySerial.flush();
                   Serial.println("N");
                   digitalWrite(Enable, LOW);   
                   anglex+=0.01;        
                 }
             }
             
        }
    }

  }
  
  delay(10);
}

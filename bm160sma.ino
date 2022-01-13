#include <BMI160Gen.h>

const int select_pin = 10;
const int i2c_addr = 0x68;

const float xcal = -0.8;
const float ycal = 5.3;

#define ACC_LSB_2_G        16384.0  // [bit/gravity]
#define RAD_2_DEG          57.29578 // [°/rad]
float temp, accX, accY, accZ;
float angleX,angleY,avgX,agX=0,avX[10],avX2[10],cax,cax2,cax3,n0;
float prevY=0,prevX=0;
int i=0,j=0;
 int ax,ay,az;
int count=0;
//=======
String koma=",";
String mystring,string1,string2;
//====
float movingAvg(float *x_anglePtr, float *ptrSum, int pos, int len, float nextAngle)
{
  //Subtract the oldest number from the prev sum, add the new number
  *ptrSum = *ptrSum - x_anglePtr[pos] + nextAngle;
  //Assign the nextNum to the position in the array
  x_anglePtr[pos] = nextAngle;
  //return the average
  return *ptrSum / len;
}


//===
  //int j=0;
  int len = 20;
  float x_angle[20] = {0};
  float y_angle[20] = {0};
  int pos = 0;

  float newAvgx = 0;
  float newAvgy = 0;
  float sumx = 0;
  float sumy = 0;
  

void setup() {
  Serial.begin(9600); // initialize Serial communication
  while (!Serial);    // wait for the serial port to open

  // initialize device
 // BMI160.begin(BMI160GenClass::SPI_MODE, select_pin);
  BMI160.begin(BMI160GenClass::I2C_MODE, i2c_addr);
 delay(50);

for(i=0;i<len;i++){
BMI160.readAccelerometer(ax,ay,az);
  accX = ((float)ax) / ACC_LSB_2_G;
  accY = ((float)ay) / ACC_LSB_2_G;
  accZ = ((float)az) / ACC_LSB_2_G;

  angleX = asin(accX) * RAD_2_DEG;
  //Serial.println(angleX);
  angleY = asin(accY) * RAD_2_DEG;

  

  x_angle[i]=angleX;
  y_angle[i]=angleY;

  sumx=sumx+x_angle[i];
  sumy=sumy+y_angle[i];

  delay(50);
}

 
}

void loop() {
  int gx, gy, gz;         // raw gyro values
 
  
  // read raw gyro measurements from device
  BMI160.readGyro(gx, gy, gz);
  BMI160.readAccelerometer(ax,ay,az);

  accX = ((float)ax) / ACC_LSB_2_G;
  accY = ((float)ay) / ACC_LSB_2_G;
  accZ = ((float)az) / ACC_LSB_2_G;

  angleX = asin(accX) * RAD_2_DEG;
  angleY = asin(accY) * RAD_2_DEG;

    if (angleX!=angleX){
    angleX=prevX;
  }

  if (angleY!=angleY){
    angleY=prevY;
  }

  //avX[i]=angleX;
  //==============

 
    newAvgx = movingAvg(x_angle, &sumx, pos, len, angleX);
    newAvgy = movingAvg(y_angle, &sumy, pos, len, angleY);
    
    pos++;
    if (pos >= len){
      pos = 0;
    }
prevX=angleX; 
prevY=angleY;



  newAvgx=newAvgx + xcal;
  Serial.print(newAvgx);
  Serial.print("\t");
//
  newAvgy=newAvgy + ycal;
  Serial.println(newAvgy);
//  Serial.print("\t");

  //Serial.println();
//====send to net===========================================

 
////Serial.write(mystr,5);
//if(count>15){
//
//   string1= String(newAvg,2);
// string2= String(newAvgy,2);
// mystring = string1 + koma + string2;
//Serial.print('$'); 
//Serial.println(mystring);
//count=0;
//}
//delay(100);
//count++;

//============================
  delay(200);
}

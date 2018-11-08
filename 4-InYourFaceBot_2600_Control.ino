/*Based on movement control sketch from Elegoo that comes with kit or at
 * www.elegoo.com. This was modified to add a software serial port to
 * send numbers received from the remote control (bluetooth mobile app)
 * to the other Arduino that controls the sound so it knows what to play.
*/

#include <Servo.h> //servo library
#include <SoftwareSerial.h> //this is to use two pins as a software serial port

Servo myservo; // create servo object to control servo
SoftwareSerial mySerial(2, 4); // RX, TX pins

int LED=13;
volatile int state = LOW;
char getstr;
int in1=6;
int in2=7;
int in3=8;
int in4=9;
int ENA=5;
int ENB=11;
int ABS=150;
int servoPos=90; //servo position, initially set to 90 degrees

void _mForward()
{ 
  digitalWrite(ENA,HIGH);
  digitalWrite(ENB,HIGH);
  digitalWrite(in1,HIGH);//digital output
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);
  Serial.println("Forward");
}
void _mBack()
{
  digitalWrite(ENA,HIGH);
  digitalWrite(ENB,HIGH);
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
  Serial.println("Back");
}
void _mleft()
{
  analogWrite(ENA,ABS);
  analogWrite(ENB,ABS);
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW); 
  Serial.println("go left!");
}
void _mright()
{
  analogWrite(ENA,ABS);
  analogWrite(ENB,ABS);
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);
  Serial.println("go right!");
}
void _mStop()
{
  digitalWrite(ENA,LOW);
  digitalWrite(ENB,LOW);
  Serial.println("Stop!");
}
void stateChange()
{
  state = !state;
  digitalWrite(LED, state);  
}
void setup()
{ 
  mySerial.begin(4800); // set the data rate for the SoftwareSerial port to send data to other Arduino.
  myservo.attach(3);// attach servo on pin 3 to servo object
  myservo.write(90);// face forward to start
  pinMode(LED, OUTPUT);
  Serial.begin(9600); // initialize standard serial port to receive remote control commands from bluetooth app.
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);
  pinMode(ENA,OUTPUT);
  pinMode(ENB,OUTPUT);
  _mStop();
}



void loop()
  { 
  getstr=Serial.read(); //check if any remote control commands were given.
 if(getstr=='f')
  {
    _mForward();
  }
  else if(getstr=='b')
  {
    _mBack();
    delay(200);
  }
  else if(getstr=='l')
  {
    _mleft();
    delay(200);
  }
  else if(getstr=='r')
  {
    _mright();
    delay(200);
  }
  else if(getstr=='s')
  {
     _mStop();     
  }
  else if(getstr=='A')
  {
  stateChange();
  }
  else if(getstr=='o') //rotate "eyes" left
  {
   Serial.println("Look Left!"); 
    if (servoPos>0)
    {
      servoPos = servoPos-10;
    }
    myservo.write(servoPos);//setservo position according to scaled value
  }
  else if(getstr=='p') //rotate "eyes" right
  {
    Serial.println("Look Right!"); 
    if (servoPos<180)
    {
      servoPos = servoPos+10;
    }
    myservo.write(servoPos);//setservo position according to scaled value
  }
  else if(getstr=='1') //Greet  
  {
    Serial.println(getstr);
    mySerial.write(getstr);        // sends data    
  }
  else if(getstr=='2') //Fart  
  {
    Serial.println(getstr);
    mySerial.write(getstr);        // sends data
    
  }
  else if(getstr=='3') //Exclaim  
  {
    Serial.println(getstr);
    mySerial.write(getstr);        // sends data    
  }
}


#include <Servo.h>

Servo myservo;  // create servo object to control a servo

int potpin = 0;  // analog pin used to connect the potentiometer
int val;    // variable to read the value from the analog pin
int AisObstaclePin = 2;// This is our input pin
int BisObstaclePin = 3;
int CisObstaclePin = 4;
int AisObstacle = HIGH;  // HIGH MEANS NO OBSTACLE        
int BisObstacle = HIGH;
int CisObstacle = HIGH;
int angle = 0;
bool dir = 1;
int state = 0;
void setup() {
  myservo.attach(9, 500, 2400); // attaches the servo on pin 9 to the servo object
  pinMode(AisObstaclePin, INPUT);
  pinMode(BisObstaclePin, INPUT);
  pinMode(CisObstaclePin, INPUT);
  Serial.begin(9600);
}

void loop() {
  
  int angle = search();
  if (angle == 1){
     Serial.println("get!!");
     search();
  }
  else if(angle == 2){
    val -= 90;
    if (val < 0) val = 0;
    Serial.println(val);
    //myservo.write(val);
    
    if (state != 2) dir *=-1
    search();
  }
  else if(angle == 3){
    val += 90;
    if (val >180 ) val = 180;
    Serial.println(val);
    //myservo.write(val);
    if (state != 3) dir *=-1
    search();
  }
  
  /*
  myservo.write(90);
  delay(1000);*/

}

int search() {

  while (1) {
    AisObstacle = digitalRead(AisObstaclePin);
    BisObstacle = digitalRead(BisObstaclePin);
    CisObstacle = digitalRead(CisObstaclePin);
    if (AisObstacle == LOW)
    {
      Serial.println("A OBSTACLE!!, A OBSTACLE!!");
      state = 1
      return 1;
    }
    else if (BisObstacle == LOW)
    {
      Serial.println("B OBSTACLE!!, B OBSTACLE!!");
      state = 2
      return 2;
    }
    else if (CisObstacle == LOW)
    {
      Serial.println("C OBSTACLE!!, C OBSTACLE!!");
      state = 3;
      return 3;
    }
    else
    {
      //Serial.println("clear");
      if (dir) {
        val += 5;
        if (val > 180) dir = 0;
      }
      else {
        val -= 5;
        if (val < 0) dir = 1;
      }

      Serial.println(val);
      myservo.write(val);
      delay(100);
    }
  }
}

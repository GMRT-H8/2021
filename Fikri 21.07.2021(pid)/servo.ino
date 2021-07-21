void initservo(){
    ESP32PWM::allocateTimer(0);
    ESP32PWM::allocateTimer(1);
    ESP32PWM::allocateTimer(2);
    ESP32PWM::allocateTimer(3);
    myservo1.setPeriodHertz(50);   // standard 50 hz servo
    myservo1.attach(servoPin1, 1000, 2000); // attaches the servo on pin 18 to the servo object
    myservo2.setPeriodHertz(50);   // standard 50 hz servo
    myservo2.attach(servoPin2, 1000, 2000); // attaches the servo on pin 18 to the servo object
    myservo3.setPeriodHertz(50);   // standard 50 hz servo
    myservo3.attach(servoPin3, 1000, 2000); // attaches the servo on pin 18 to the servo object

    pinMode(servoPin1, OUTPUT);
    pinMode(servoPin2, OUTPUT);
    pinMode(servoPin3, OUTPUT);

    flagxservo=0;
    flagxservo90=0;

    Serial.println("Servo is ready to use");
}

// for servo 1
// direction true for CW, false for CCW
// for CW velocity 0,1,2,3 for 90,60,30,0
// for CCW velocity 0,1,2,3 for 90,120,150,180
void servo1cont(bool direct, int velocity){
  static int velocitytoservo;
  velocitytoservo = 90 - velocity*30;
  if(direct){
    myservo1.write(velocitytoservo);
    Serial.println("Servo1 speed:");
    Serial.print(velocitytoservo);
  }
  if(!direct){
    velocitytoservo = 180 - velocitytoservo;
    myservo1.write(velocitytoservo);
    Serial.println("Servo1 speed:");
    Serial.print(velocitytoservo);
  }
}
// servo stop
void servo1stop(){
  myservo1.write(90);
}

// for servo 2
// direction true for CW, false for CCW
// for CW velocity 0,1,2,3 for 86, 91, 96, 101
// for CCW velocity 0,1,2,3 for 86,81,76,71
void servo2cont(bool direct, int velocity){
  int velocitytoservo;
  velocitytoservo = 90 - velocity*30;
  if(direct){
    myservo2.write(85);
    Serial.println("Servo2 speed:");
    Serial.print(velocitytoservo);
  }
  if(!direct){
    velocitytoservo = 180 - velocitytoservo;
    myservo2.write(100);
    Serial.println("Servo2 speed:");
    Serial.print(velocitytoservo);
  }
}

// servo stop
void servo2stop(){
  myservo2.write(90);
}

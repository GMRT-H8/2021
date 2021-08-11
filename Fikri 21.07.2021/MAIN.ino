// Inititalize library 
// Ps3Controller.h to functionalize ps3 controller
// ESP32Servo.h to controlling servo
#include <Ps3Controller.h>
#include <ESP32Servo.h>

// declaration of object servo
// servo1 for vertical movement
// servo2 for horizontal movement
// servo3 for gripper 90 deg rotation
Servo myservo1;
Servo myservo2;
Servo myservo3;

// variables for Ps3Controller
int player = 0;
int battery = 0;

byte encAlastleft;
int durationleft;
bool dirleft;
// variables for RPM
//static unsigned long now, lastTime, lastTime2;
int counterleft;
//int currentPos, lastPos;
//long RPM;

byte encAlastright;
int durationright;
bool dirright;
// variables for RPM
//static unsigned long now, lastTime, lastTime2;
int counterright;
//int currentPos, lastPos;
//long RPM;

double rightinput, leftinput;

// define pin encoder
const byte leftencoderA = 16;
const byte leftencoderB = 4;
const byte rightencoderA = 2;
const byte rightencoderB = 15;

// define pin IBT motor driver
const byte ML_A = 32;
const byte ML_B = 33;
const byte MR_A = 25;
const byte MR_B = 27;

// define pin servo
const byte servoPin1 = 14;
const byte servoPin2 = 12;
const byte servoPin3 = 13;

static int flagxservo90;

int velocitymotorright;
int velocitymotorleft; 
// static int RPMmotor;

void onConnect(){
    Serial.println("Connected.");
}

void setup()
{
    Serial.begin(115200);
    initmotorright();
    initmotorleft();
    //initmotor();
    initPS3Controller();
    initservo();
    //leftinitRPM();
    //rightinitRPM();
    flagxservo90 = 0;
    velocitymotorright = 82;;
    velocitymotorleft = 78;
}

void loop()
{
    if(!Ps3.isConnected())
        return;
    eventPS3Controller();
    //rightinput = rightRPM();
    //leftinput = leftRPM();
}

#include <Ps3Controller.h>
#include <ESP32Servo.h>
#include <PID_v1.h>

Servo myservo1;
Servo myservo2;
Servo myservo3;
int player = 0;
int battery = 0;

byte leftencoderA, leftencoderB;
byte rightencoderA, rightencoderB;

const byte ML_A = 12;
const byte ML_B = 13;
const byte MR_A = 2;
const byte MR_B = 4;

const byte servoPin1 = 25;
const byte servoPin2 = 26;
const byte servoPin3 = 27;

static int flagxservo;
static int flagxservo90;

static int velocitymotor; 
static double RPMmotor;

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

// left motor PID variables
double leftsetpoint, leftinput, leftoutput;
double leftKp, leftKi, leftKd;

// right motor PID variables
double rightsetpoint, rightinput, rightoutput;
double rightKp, rightKi, rightKd;

PID MyPIDleft(&leftinput, &leftoutput, &leftsetpoint, leftKp, leftKi, leftKd, DIRECT);
PID MyPIDright(&rightinput, &rightoutput, &rightsetpoint, rightKp, rightKi, rightKd, DIRECT);

void onConnect(){
    Serial.println("Connected.");
}

void setup()
{
    Serial.begin(115200);
    initmotorright();
    initmotorleft();
    dirleft = true;
    dirright = true;
    //initmotor();
    initPS3Controller();
    initservo();
    /*
    pinMode(2, OUTPUT);
    pinMode(4, OUTPUT);
    pinMode(12, OUTPUT);
    pinMode(13, OUTPUT);
    */
    RPMmotor = 60;
    velocitymotor = 100;
}

void loop()
{
    if(!Ps3.isConnected())
        return;
    eventPS3Controller();
}

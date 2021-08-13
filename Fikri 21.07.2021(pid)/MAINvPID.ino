#include <Ps3Controller.h>
#include <ESP32Servo.h>
#include <PID_v1.h>

Servo myservo1;
Servo myservo2;
Servo myservo3;
int player = 0;
int battery = 0;

const byte leftencoderA = 4;
const byte leftencoderB = 16;
const byte rightencoderA = 2; 
const byte rightencoderB = 15;

const byte ML_A = 32;
const byte ML_B = 33;
const byte MR_A = 25;
const byte MR_B = 27;


const byte servoPin1 = 12;
const byte servoPin2 = 13;
const byte servoPin3 = 26;

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

// variables for controlled motor
bool flagdirectright;
bool flagdirectleft;
bool rightact;
bool leftact;
// left motor PID variables
double leftsetpoint, leftinput, leftoutput;
double leftKp=56.3757;
double leftKi=6373.9836;
double leftKd=0.12625;

// right motor PID variables
double rightsetpoint, rightinput, rightoutput;
double rightKp = 28.6101/100;
double rightKi = 25.7195/100;
double rightKd = 7.0655/100;

PID MyPIDleft(&leftinput, &leftoutput, &leftsetpoint, leftKp, leftKi, leftKd, DIRECT);
PID MyPIDright(&rightinput, &rightoutput, &rightsetpoint, rightKp, rightKi, rightKd, DIRECT);

unsigned long past;

void onConnect(){
    Serial.println("Connected.");
}

void setup()
{
    Serial.begin(115200);
    initctrlmotorright();
    initctrlmotorleft();
    //initmotorleft();
    dirleft = true;
    dirright = true;
    //initmotor();
    initPS3Controller();
    initservo();
    //leftinitRPM();
    rightinitRPM();
    leftinitRPM();
    rightact = false;
    leftact = false;
    RPMmotor = 60;
    velocitymotor = 110;
}

void loop()
{
    if(!Ps3.isConnected())
        return;
    eventPS3Controller();
    rightinput = rightRPM();
    leftinput = leftRPM();
    ctrl_motorright(velocitymotor);
    ctrl_motorleft(velocitymotor);
    /*
    if(millis()-past>=100){
      Serial.print("flag: ");
      Serial.println(rightact);
    }
    */
}

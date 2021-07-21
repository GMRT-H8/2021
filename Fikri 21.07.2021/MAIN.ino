#include <Ps3Controller.h>
#include <ESP32Servo.h>

Servo myservo1;
Servo myservo2;
Servo myservo3;
int player = 0;
int battery = 0;

const byte ML_A = 32;
const byte ML_B = 33;
const byte MR_A = 25;
const byte MR_B = 26;

const byte servoPin1 = 14;
const byte servoPin2 = 12;
const byte servoPin3 = 13;

static int flagxservo;
static int flagxservo90;

static int velocitymotor; 
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
    /*
    pinMode(2, OUTPUT);
    pinMode(4, OUTPUT);
    pinMode(12, OUTPUT);
    pinMode(13, OUTPUT);
    */
    velocitymotor = 80;
}

void loop()
{
    if(!Ps3.isConnected())
        return;
    eventPS3Controller();
}

#include <Ps3Controller.h>
#include <ESP32Servo.h>

Servo myservo1;
Servo myservo2;
Servo myservo3;
int player = 0;
int battery = 0;

const byte ML_A = 26;
const byte ML_B = 18;
const byte MR_A = 19;
const byte MR_B = 21;

const byte servoPin1 = 25;
const byte servoPin2 = 26;
const byte servoPin3 = 27;

static int flagxservo;
static int flagxservo90;

void onConnect(){
    Serial.println("Connected.");
}

void setup()
{
    Serial.begin(115200);
    initmotorright(MR_A, MR_B);
    initmotorleft(ML_A, ML_B);
    initPS3Controller();
       
}

void loop()
{
    if(!Ps3.isConnected())
        return;
    eventPS3Controller();
}

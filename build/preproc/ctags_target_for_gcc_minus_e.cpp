# 1 "C:\\Users\\owen.lee\\Desktop\\Owen\\01.Project\\Small Projects\\RoboticArm\\Software\\RoboticArmControl\\RoboticArmControl.ino"
# 2 "C:\\Users\\owen.lee\\Desktop\\Owen\\01.Project\\Small Projects\\RoboticArm\\Software\\RoboticArmControl\\RoboticArmControl.ino" 2
# 3 "C:\\Users\\owen.lee\\Desktop\\Owen\\01.Project\\Small Projects\\RoboticArm\\Software\\RoboticArmControl\\RoboticArmControl.ino" 2

const byte servoAPin = 5;
const byte servoBPin = 6;
const byte servoCPin = 7;
const byte servoDPin = 8;

const byte joystickAPinX = A0;
const byte joystickAPinY = A1;
const byte joystickBPinX = A2;
const byte joystickBPinY = A3;

int joystickAXValue[5] = {0, 0, 0, 0, 0};
int joystickAYValue[5] = {0, 0, 0, 0, 0};
int joystickBXValue[5] = {0, 0, 0, 0, 0};
int joystickBYValue[5] = {0, 0, 0, 0, 0};

Servo servoA, servoB, servoC, servoD;

void filter();
int qsortUseComparison(const void* a, const void* b);
void servoControl();

void setup()
{
    servoA.attach(servoAPin, 500, 2400);
    servoB.attach(servoBPin, 500, 2400);
    servoC.attach(servoCPin, 500, 2400);
    servoD.attach(servoDPin, 500, 2400);
}

void loop()
{
    filter();
    servoControl();
}

void filter(){
    static byte indexOfArray = 0;
    joystickAXValue[indexOfArray] = analogRead(joystickAPinX);
    joystickAYValue[indexOfArray] = analogRead(joystickAPinY);
    joystickBXValue[indexOfArray] = analogRead(joystickBPinX);
    joystickBYValue[indexOfArray] = analogRead(joystickBPinY);

    qsort(joystickAXValue, 5, sizeof(int), qsortUseComparison);
    qsort(joystickAYValue, 5, sizeof(int), qsortUseComparison);
    qsort(joystickBXValue, 5, sizeof(int), qsortUseComparison);
    qsort(joystickBYValue, 5, sizeof(int), qsortUseComparison);

    if(++indexOfArray % 5 == 0){
        indexOfArray = 0;
    }
}

int qsortUseComparison(const void* a, const void* b){
    return (*(int*)a - *(int*)b);
}

void servoControl(){
    int servoAPos, servoBPos, servoCPos, servoDPos;

    servoAPos = map(joystickAYValue[5/2], 0, 1023, 0, 180);
    servoBPos = map(joystickAXValue[5/2], 0, 1023, 0, 100);
    servoCPos = map(joystickBYValue[5/2], 0, 1023, 0, 180);
    servoDPos = map(joystickBXValue[5/2], 0, 1023, 0, 100);

    servoA.write(servoAPos);
    servoB.write(servoBPos);
    servoC.write(servoCPos);
    servoD.write(servoDPos);

    delay(15);
}

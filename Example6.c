/*
* RSLK will follow a line using a basic line following algorithm, works on a dark
* floor with a white line or a light floor with a dark line. The robot first needs to be calibrated
* Then place the robot on the line hit the left button again to begin the line following.
*
* How to run:
* 1) Push left button on Launchpad to have the robot perform calibration.
* 2) Robot will drive forwards and backwards by a predefined distance.
* 3) Place the robot center on the line you want it to follow.
* 4) Push left button again to have the robot begin to follow the line.
*/


#include "SimpleRSLK.h"

uint16_t sensorVal[LS_NUM_SENSORS];
uint16_t sensorCalVal[LS_NUM_SENSORS];
uint16_t sensorMaxVal[LS_NUM_SENSORS];
uint16_t sensorMinVal[LS_NUM_SENSORS];
bool isCalibrationComplete = false;

void setup()
{
   Serial.begin(115200);
   setupRSLK();
   setupWaitBtn(LP_LEFT_BTN);                 // Left button on Launchpad
   setupLed(RED_LED);                         // Red led in rgb led
   clearMinMax(sensorMinVal,sensorMaxVal);
}

void loop()
{
   uint16_t normalSpeed = 10;
   uint16_t fastSpeed = 20;
   uint8_t lineColor = DARK_LINE;                        // Only valid values are DARK_LINE or LIGHT_LINE

   // Run this setup only once
   if(isCalibrationComplete == false) {
       floorCalibration();
       isCalibrationComplete = true;
   }

   readLineSensor(sensorVal);
   readCalLineSensor(sensorVal, sensorCalVal, sensorMinVal, sensorMaxVal, lineColor);
   uint32_t linePos = getLinePosition(sensorCalVal,lineColor);

   if(linePos > 0 && linePos < 3000)
   {
       setMotorSpeed(LEFT_MOTOR,normalSpeed);
       setMotorSpeed(RIGHT_MOTOR,fastSpeed);
   }
   else if(linePos > 3500)
   {
       setMotorSpeed(LEFT_MOTOR,fastSpeed);
       setMotorSpeed(RIGHT_MOTOR,normalSpeed);
   }
   else {
       setMotorSpeed(LEFT_MOTOR,normalSpeed);
       setMotorSpeed(RIGHT_MOTOR,normalSpeed);
   }
}

void floorCalibration() {
   // Place Robot On Floor (no line)
   delay(2000);
   String btnMsg = "Push left button on Launchpad to begin calibration.\n";
   btnMsg += "Make sure the robot is on the floor away from the line.\n";
   waitBtnPressed(LP_LEFT_BTN,btnMsg,RED_LED);                                     // Wait until button is pressed to start robot
   delay(1000);
   Serial.println("Running calibration on floor");
   simpleCalibrate();
   Serial.println("Reading floor values complete");
   btnMsg = "Push left button on Launchpad to begin line following.\n";
   btnMsg += "Make sure the robot is on the line.\n";
   waitBtnPressed(LP_LEFT_BTN,btnMsg,RED_LED);                                    // Wait until button is pressed to start robot
   delay(1000);
   enableMotor(BOTH_MOTORS);
}

void simpleCalibrate() {
   setMotorDirection(BOTH_MOTORS,MOTOR_DIR_FORWARD);     // Set both motors direction forward
   enableMotor(BOTH_MOTORS);                             // Enable both motors
   setMotorSpeed(BOTH_MOTORS,20);                        // Set both motors speed 20

   for(int x = 0;x<100;x++){
       readLineSensor(sensorVal);
       setSensorMinMax(sensorVal,sensorMinVal,sensorMaxVal);
   }
   disableMotor(BOTH_MOTORS);                            // Disable both motors
}
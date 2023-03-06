// TI-RSLK robot encoder driving script with closed-loop control
// Written for Energia IDE

// Define pins
const int leftMotorPWM = 6;   // PWM pin for left motor
const int leftMotorDir = 7;   // Direction pin for left motor
const int rightMotorPWM = 9;  // PWM pin for right motor
const int rightMotorDir = 8;  // Direction pin for right motor
const int leftEncoder = 3;    // Interrupt pin for left encoder
const int rightEncoder = 2;   // Interrupt pin for right encoder

// Define constants
const float wheelDiameter = 6.5;  // Diameter of the robot's wheels in centimeters
const float wheelCircumference = PI * wheelDiameter;  // Circumference of the wheels in centimeters
const int encoderTicksPerRevolution = 3200;  // Number of encoder ticks per revolution of the wheels
const float encoderDistancePerTick = wheelCircumference / encoderTicksPerRevolution;  // Distance traveled per encoder tick in centimeters
const int motorSpeed = 200;  // Motor speed (0-255)

// Define variables
volatile int leftEncoderCount = 0;   // Number of encoder ticks on the left wheel
volatile int rightEncoderCount = 0;  // Number of encoder ticks on the right wheel
float leftDistance = 0.0;            // Distance traveled by the left wheel in centimeters
float rightDistance = 0.0;           // Distance traveled by the right wheel in centimeters
float desiredDistance = 0.0;         // Desired distance between the wheels in centimeters
float previousError = 0.0;           // Previous error in distance
float integral = 0.0;                // Integral of error in distance

void setup() {
  // Initialize pins
  pinMode(leftMotorPWM, OUTPUT);
  pinMode(leftMotorDir, OUTPUT);
  pinMode(rightMotorPWM, OUTPUT);
  pinMode(rightMotorDir, OUTPUT);
  pinMode(leftEncoder, INPUT_PULLUP);
  pinMode(rightEncoder, INPUT_PULLUP);

  // Attach interrupt handlers
  attachInterrupt(digitalPinToInterrupt(leftEncoder), leftEncoderISR, RISING);
  attachInterrupt(digitalPinToInterrupt(rightEncoder), rightEncoderISR, RISING);

  // Set the desired distance to the robot's wheelbase
  desiredDistance = 17.0;  // Distance between the wheels in centimeters
}

void loop() {
  // Move forward for 1 meter
  int targetDistance = 100;  // Target distance in centimeters
  resetEncoders();
  while (leftDistance < targetDistance || rightDistance < targetDistance) {
    // Calculate the error in distance between the wheels
    float error = rightDistance - leftDistance - desiredDistance;
    
    // Calculate the derivative and integral of the error
    float derivative = error - previousError;
    integral += error;
    
    // Calculate the motor speeds based on the error and its derivative and integral
    int leftSpeed = motorSpeed + error * 2.0 + derivative * 3.0 + integral * 0.1;
    int rightSpeed = motorSpeed - error * 2.0 - derivative * 3.0 - integral * 0.1;
    
    // Set the motor speeds
    setMotorSpeed(leftSpeed, rightSpeed);
    
    // Update the previous error
    previousError = error;
  }
  
  // Stop the robot
  setMotorSpeed(0, 0);
}
// TI-RSLK robot encoder driving script
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
}

void loop() {
  // Move forward for 1 meter
  int targetDistance = 100;  // Target distance in centimeters
  resetEncoders();
  while (leftDistance < targetDistance || rightDistance < targetDistance) {
    setMotorSpeed(motorSpeed, motorSpeed);
    delay(10);
  }
  stopMotors();

  // Turn right for 90 degrees
  int targetAngle = 90;  // Target angle in degrees
  resetEncoders();
  while (leftDistance < targetAngle * wheelCircumference / 360 || rightDistance > -targetAngle * wheelCircumference / 360) {
    setMotorSpeed(motorSpeed, -motorSpeed);
    delay(10);
  }
  stopMotors();
}

void leftEncoderISR() {
  leftEncoderCount++;
  leftDistance += encoderDistancePerTick;
}

void rightEncoderISR() {
  rightEncoderCount++;
  rightDistance += encoderDistancePerTick;
}

void resetEncoders() {
  leftEncoderCount = 0;
  rightEncoderCount = 0;
  leftDistance = 0.0;
  rightDistance = 0.0;
}

void setMotorSpeed(int leftSpeed, int rightSpeed) {
  analogWrite(leftMotorPWM, abs(leftSpeed));
  digitalWrite(leftMotorDir, leftSpeed > 0 ? HIGH : LOW);
  analogWrite(rightMotorPWM, abs(rightSpeed));
  digitalWrite(rightMotorDir, rightSpeed > 0 ? HIGH
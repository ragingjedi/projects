// Pin definitions
#define LEFT_MOTOR_PWM_PIN 2
#define LEFT_MOTOR_DIR_PIN 3
#define RIGHT_MOTOR_PWM_PIN 4
#define RIGHT_MOTOR_DIR_PIN 5
#define LEFT_ENCODER_PIN 21
#define RIGHT_ENCODER_PIN 20

// Robot dimensions and constants
const float wheelDiameter = 6.5;  // in cm
const float distanceBetweenWheels = 16.7;  // in cm
const float encoderTicksPerRevolution = 3200.0;
const float encoderDistancePerTick = (M_PI * wheelDiameter) / encoderTicksPerRevolution;

// Motor speed limits
const int maxMotorSpeed = 255;
const int minMotorSpeed = 0;

// Global variables
volatile long leftEncoderCount = 0;
volatile long rightEncoderCount = 0;
float leftDistance = 0.0;
float rightDistance = 0.0;
int leftMotorSpeed = 0;
int rightMotorSpeed = 0;

// Function prototypes
void setLeftMotorSpeed(int speed);
void setRightMotorSpeed(int speed);
void moveForward(int distance);
void turnLeft(int angle);
void turnRight(int angle);
void resetEncoders();
void leftEncoderISR();
void rightEncoderISR();

void setup() {
  // Set up motor control pins
  pinMode(LEFT_MOTOR_PWM_PIN, OUTPUT);
  pinMode(LEFT_MOTOR_DIR_PIN, OUTPUT);
  pinMode(RIGHT_MOTOR_PWM_PIN, OUTPUT);
  pinMode(RIGHT_MOTOR_DIR_PIN, OUTPUT);

  // Set up encoder pins
  pinMode(LEFT_ENCODER_PIN, INPUT_PULLUP);
  pinMode(RIGHT_ENCODER_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(LEFT_ENCODER_PIN), leftEncoderISR, RISING);
  attachInterrupt(digitalPinToInterrupt(RIGHT_ENCODER_PIN), rightEncoderISR, RISING);

  // Reset the encoder counts and wheel distances
  resetEncoders();
}

void loop() {
  // Move forward for 50 cm
  moveForward(50);

  // Turn left by 90 degrees
  turnLeft(90);

  // Move forward for 50 cm
  moveForward(50);

  // Turn right by 90 degrees
  turnRight(90);

  // Stop the motors
  setLeftMotorSpeed(0);
  setRightMotorSpeed(0);
}

// Set the speed of the left motor
void setLeftMotorSpeed(int speed) {
  // Ensure that the motor speed is within the valid range
  if (speed > maxMotorSpeed) {
    speed = maxMotorSpeed;
  } else if (speed < -maxMotorSpeed) {
    speed = -maxMotorSpeed;
  }

  // Set the direction of the motor
  if (speed >= 0) {
    digitalWrite(LEFT_MOTOR_DIR_PIN, HIGH);
  } else {
    digitalWrite(LEFT_MOTOR_DIR_PIN, LOW);
    speed = -speed;
  }

  // Set the PWM signal to the motor
  analogWrite(LEFT_MOTOR_PWM_PIN, speed);
  leftMotorSpeed = speed;
}

// Set the speed of the right motor
void setRightMotorSpeed(int speed) {
  // Ensure that the motor speed is within the valid range
  if (speed > maxMotorSpeed) {
    speed = maxMotorSpeed;
  } else if (speed < -maxMotorSpeed) {
    speed = -maxMotorSpeed;
  }

  // Set the direction of the motor

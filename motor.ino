void setup(Motor motor) {
  pinMode(motor.en, OUTPUT);
  pinMode(motor.pwm, OUTPUT);
  pinMode(motor.clockwiseDir, OUTPUT);
  pinMode(motor.counterClockwiseDir , OUTPUT);
}

void refreshMotor(Motor& motor) {
  if (motor.targetPower < motor.currentPower) {
    motor.currentPower--;
    updateMotorPower(motor);
  }
}

void stright() {
  changeSpeed(rightMotor, MOTOR_SPEED);
  changeSpeed(leftMotor, -MOTOR_SPEED);
}

void reverse() {
  changeSpeed(rightMotor, -MOTOR_SPEED);
  changeSpeed(leftMotor, MOTOR_SPEED + 10);
}

void turnRight() {
  changeSpeed(rightMotor, -MOTOR_SPEED);
  changeSpeed(leftMotor, -MOTOR_SPEED);
}

void turnLeft() {
  changeSpeed(rightMotor, MOTOR_SPEED);
  changeSpeed(leftMotor, MOTOR_SPEED);
}

void stop() {
  changeSpeed(rightMotor, 0);
  changeSpeed(leftMotor, 0);
}


void changeSpeed(Motor& motor, int speed) {
  if (speed == 0) {
    digitalWrite(motor.en, LOW);
  } else {
    digitalWrite(motor.en, HIGH);
    
    if (speed > 0) {
      digitalWrite(motor.clockwiseDir, HIGH);
      digitalWrite(motor.counterClockwiseDir, LOW);
    } else {
      digitalWrite(motor.clockwiseDir, LOW);
      digitalWrite(motor.counterClockwiseDir, HIGH);
    }
    
    motor.currentPower = abs(speed);                         //было 150
    motor.targetPower = min(abs(speed), 255);
    updateMotorPower(motor);
  }
}

void updateMotorPower(Motor& motor) {
    analogWrite(motor.pwm, motor.currentPower);
}

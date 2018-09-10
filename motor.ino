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
    
    motor.currentPower = min(abs(speed), 255);                       
    motor.targetPower = min(abs(speed), 255);
    updateMotorPower(motor);
  }
}

void updateMotorPower(Motor& motor) {
    analogWrite(motor.pwm, motor.currentPower);
}

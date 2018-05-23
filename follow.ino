const int LEFT = 0;
const int RIGHT = 1;
const int CENTER = 2;

int followState = CENTER;

void strategyFollow() {

  refreshSensor(leftSensor);
  refreshSensor(rightSensor);

  Serial.print(leftSensor.value);
  Serial.print(" --- ");
  Serial.println(rightSensor.value);

  if (leftSensor.lineDetected) {
    stop();
    Serial.println("Turn right");
    turnLeft();
    delay(250);
  } else if (leftMostSensor.lineDetected) {
    stop();
    Serial.println("Turn right");
    turnLeft();
    delay(450);
  } else if (rightMostSensor.lineDetected) {
    stop();
    Serial.println("Turn left");
    turnRight();
    delay(450);
  } else if (rightSensor.lineDetected) {
    stop();
    Serial.println("Turn left");
    turnRight();
    delay(250);
  } else {
    Serial.println("Forward");
    stright();
    delay(5);
  }

}


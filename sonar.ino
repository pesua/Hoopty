void setup(Sonar& sonar) {
  pinMode(sonar.trigPin, OUTPUT);
  pinMode(sonar.echoPin, INPUT);
}

void refreshSonar(Sonar& sonar) {
  digitalWrite(sonar.trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(sonar.trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(sonar.trigPin, LOW);

  long duration = pulseIn(sonar.echoPin, HIGH);
  sonar.distance = duration * 0.034 / 2;

//  Serial.println(sonar.distance);
}


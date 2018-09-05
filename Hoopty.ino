const int MOTOR_SPEED = 100;
const int SENSOR_TRESHOLD = 600; 
const int SENSOR_TRIALS = 3;

struct Motor {
  // config
  int en;
  int pwm;
  int clockwiseDir;
  int counterClockwiseDir;

  //state
  int currentPower;
  int targetPower;
};

struct Sensor {
  int pin;
  
  int value;
  boolean lineDetected = false;                   
  boolean stateChanged = false;                   
};

struct Sonar {
  int trigPin;
  int echoPin;

  int distance;
};

Motor leftMotor;
Motor rightMotor;

Sensor leftSensor;
Sensor rightSensor;
  Sensor d2;
  Sensor d3;
  Sensor d4;
  Sensor d5;
  Sensor d6;

Sonar sonar;

void setup() {
  setupMotors();
  setupSensors();
  setupSonar();

  delay(4500); 

  Serial.begin(9600);
  Serial2.begin(38400);
  Serial2.println("AT+NAMEHOOPTY");
}

void setupSonar() {
  sonar.trigPin = 43;
  sonar.echoPin = 42;

  setup(sonar);
}

void setupMotors() {
  leftMotor.en = A1;
  leftMotor.pwm = 6;
  leftMotor.clockwiseDir = 4;
  leftMotor.counterClockwiseDir = 9;

  setup(leftMotor);
  
  rightMotor.en = A0;
  rightMotor.pwm = 5;
  rightMotor.clockwiseDir = 7;
  rightMotor.counterClockwiseDir = 8;

  setup(rightMotor);
}


void setupSensors() {
  leftSensor.pin = A15;             
  rightSensor.pin = A9;
              d2.pin = A14; 
              d3.pin = A11;
              d4.pin = A12;
              d5.pin = A13;
              d6.pin = A10;
}

void loop() {
  
  int command = -1;
  while(Serial2.available())
    command = Serial2.read();
  double turnFactor = 0.5;
  switch(command){
    case -1: break;
    case '1': setSpeed(1, 1); break;
    case '2': setSpeed(turnFactor, 1); break;
    case '3': setSpeed(-turnFactor, turnFactor); break;
    case '4': setSpeed(-turnFactor, -1); break;
    case '5': setSpeed(-turnFactor, -turnFactor); break;
    case '6': setSpeed(-1, -turnFactor); break;
    case '7': setSpeed(turnFactor, -turnFactor); break;
    case '8': setSpeed(1, turnFactor); break;
    default: setSpeed(0,0);
  }

  delay(50);

}

void refreshSensor(Sensor& sensor) {
  sensor.value = analogRead(sensor.pin);
  boolean newState = sensor.value > SENSOR_TRESHOLD;   
  sensor.stateChanged = sensor.lineDetected ^ newState;
  sensor.lineDetected = newState;
    
}

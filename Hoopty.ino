const int MOTOR_SPEED = 50;
const int SENSOR_TRESHOLD = 400; 
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
  // config
  int pin;

  // state
//  int i = 0;
//  int ringBuffer[SENSOR_TRIALS];
  
  int value;
  boolean lineDetected = true;
  boolean stateChanged = true;
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

Sonar sonar;

void setup() {
  setupMotors();
  setupSensors();
  setupSonar();

  delay(4500); 

  Serial.begin(9600);
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
}

void loop() {
  refreshSensor(leftSensor);
  refreshSensor(rightSensor);

  Serial.print(leftSensor.value);
  Serial.print(" --- ");
  Serial.println(rightSensor.value);
  
  strategy();

  refreshMotor(leftMotor);
  refreshMotor(rightMotor);
}

void refreshSensor(Sensor& sensor) {
  sensor.value = analogRead(sensor.pin);

//  sensor.ringBuffer[sensor.i] = analogRead(sensor.pin);
//  sensor.i = (sensor.i + 1) % SENSOR_TRIALS;

//  sensor.value = 0;
//  for (int i  = 0; i < SENSOR_TRIALS; i++) {
//    sensor.value += sensor.ringBuffer[i];
//  }
//  sensor.value = sensor.value / SENSOR_TRIALS;
  
  
  boolean newState = sensor.value > SENSOR_TRESHOLD;    

  sensor.stateChanged = sensor.lineDetected ^ newState;
  
  sensor.lineDetected = newState;
}


//  if (leftSensor.stateChanged || rightSensor.stateChanged) {
//
//    if (leftSensor.lineDetected && rightSensor.lineDetected) {
//      stop();
//    } else if (rightSensor.lineDetected) {
//      stop();
////      turnLeft();
//    } else if (leftSensor.lineDetected) {
//      stop();
////      turnRight();
//    } else {
////      stright();
//
//      if (sonar.distance < 110) {
//    
//        stright();
//      } else {
//        
//        turnLeft();
//      }
//    }  
//  }

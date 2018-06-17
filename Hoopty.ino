const int MOTOR_SPEED = 120;
const int SENSOR_TRESHOLD = 200; 
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
  boolean lineDetected = false;                   //было true
  boolean stateChanged = false;                   //было true
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
//  refreshSensor(leftSensor);                                              
//  refreshSensor(d2);
//  refreshSensor(d3);
//  refreshSensor(d4);
//  refreshSensor(d5);
//  refreshSensor(d6);
//  refreshSensor(rightSensor);
//
//  Serial.print(" leftSensor = ");
//  Serial.print(leftSensor.value);
//  Serial.print(" d2 = ");
//  Serial.print(d2.value);
//  Serial.print(" d3 = ");
//  Serial.print(d3.value);
//  Serial.print(" d4 = ");
//  Serial.print(d4.value);
//  Serial.print(" d5 = ");
//  Serial.print(d5.value);
//  Serial.print(" d6 = ");
//  Serial.print(d6.value);
//  Serial.print(" rightSensor = ");
//  Serial.println(rightSensor.value);

//   refreshSonar(sonar);
//   Serial.print(" sonar.distance = ");
//   Serial.println(sonar.distance);
   
 strategy();
 //line_race();
 //stright();
// delay(3000);
// right20();

//  refreshMotor(leftMotor);
//  refreshMotor(rightMotor);
}

void refreshSensor(Sensor& sensor) {
  sensor.value = analogRead(sensor.pin);

//  sensor.ringBuffer[sensor.i] = analogRead(sensor.pin);
//  sensor.i = (sensor.i + 1) % SENSOR_TRIALS;
//
//  sensor.value = 0;
//  for (int i  = 0; i < SENSOR_TRIALS; i++) {
//    sensor.value += sensor.ringBuffer[i];
//  }
//  sensor.value = sensor.value / SENSOR_TRIALS;
  
  
  boolean newState = sensor.value < SENSOR_TRESHOLD;   
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

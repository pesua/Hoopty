#define dW digitalWrite
#define dR digitalRead

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

  Motor leftMotor;
  Motor rightMotor;


/* GLOBAL CONSTANTS */

#define WHITE  1
#define BLACK   0

#define COLOR   BLACK         //Line color

#define N_SENS        5       //Number of sensors
#define R_SENS        250    //Sensor readings are mapped to this range      
#define WEIGHT_UNIT   250    //Unit for weighted average                     
#define RIGHT_DIR     1
#define LEFT_DIR      0
//#define PRESS         0
//#define RELEASE       1
#define CAL_SPEED     50     //Sensor calibration speed
#define CAL_TIME      300     //Calibration time (ms)
#define P_LINE_MIN    0.5     //Minimum brightness percentage to consider part of the line

const float SPEED = 70;      
const float KP = 1.5;         //
const float KD = 1;          //
const float KI = 0;           //

/* GLOBAL VARIABLES */

unsigned long ms = 0;
const int SENSOR[N_SENS] = { A8, A9, A10, A11, A12 };     //Arduino pins
int sens_max[N_SENS];          //Maximum value each sensor measures (calibrated)
int sens_min[N_SENS];          //Minimum value each sensor measures (calibrated)
//int start = 0;
float line_pos = 0;
float last_line_pos = 0;

void setup() {
  Serial.begin(9600);
  InitializeGPIO();
  setupMotors();
  
  for(int x = 0; x < N_SENS; x++){
      sens_max[x] = 0;
      sens_min[x] = 1023;
  }
  
}

int get_line_pos(int color, int last_dir){
    float line = 0;
    int line_detected = 0;
    float sens_scaled[N_SENS];
    float avg_num = 0;          //Average numerator
    float avg_den = 0;          //Average denominator
    
    for(int x = 0; x < N_SENS; x++){
        //Scale from 0 to R_SENS
        sens_scaled[x] = analogRead(SENSOR[x]) - sens_min[x];
        sens_scaled[x] *= R_SENS;
        sens_scaled[x] /= (sens_max[x] - sens_min[x]);
        Serial.print("SENSOR[");
        Serial.print(x); 
        Serial.print("] = ");
        Serial.print(sens_scaled[x]);
        Serial.print(" -- ");
        
        if(color == BLACK){
            sens_scaled[x] = R_SENS - sens_scaled[x];     //Reverse scale to go from R_SENS to 0
        }
        if(sens_scaled[x] >= R_SENS * (P_LINE_MIN / 100.0)){   //At least one sensor has to detect a line
            line_detected = 1;
        }
        
        avg_num += sens_scaled[x] * x * WEIGHT_UNIT;
        avg_den += sens_scaled[x];        
    }
    Serial.println(" -- ");
    if(line_detected == 1){
        line = avg_num / avg_den;                           //Weighted average
        line = line - (WEIGHT_UNIT * (N_SENS - 1) / 2);     //Change scale from 0 _ 4000 to -2000 _ 2000
        //dW(LEDG, LOW);
    }else{
        line = WEIGHT_UNIT * (N_SENS - 1) * last_dir;       //Use last direction to calculate error as the maximum value
        line = line - (WEIGHT_UNIT * (N_SENS - 1) / 2);     //Change scale
        //dW(LEDG, HIGH);
    }
    
    return line;
}

float get_PID_correction(float line, float last_line, float kp, float kd, float ki){
  float proportional = line;
  float derivative = line - last_line;
  float integral = line + last_line;
  float correction = (kp * proportional + kd * derivative + ki * integral);

//  Serial.print("correction = ");
//          Serial.println(correction);  

  return correction;
}



//  Serial.print("correction = ");
//          Serial.println(correction);  




void InitializeGPIO(){


  for(int x = 0; x < N_SENS; x++){
    pinMode(SENSOR[x], INPUT);
  }
}

void setup(Motor motor) {
  pinMode(motor.en, OUTPUT);
  pinMode(motor.pwm, OUTPUT);
  pinMode(motor.clockwiseDir, OUTPUT);
  pinMode(motor.counterClockwiseDir , OUTPUT);
}

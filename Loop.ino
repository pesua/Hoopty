void loop() {
              //changeSpeed(rightMotor, 70);
              //changeSpeed(leftMotor, -70);
      delay(5000);
      
      calibrate(CAL_TIME/2, CAL_SPEED, RIGHT_DIR);
      calibrate(CAL_TIME, CAL_SPEED, LEFT_DIR);
      calibrate(CAL_TIME, CAL_SPEED, RIGHT_DIR);
      calibrate(CAL_TIME/2, CAL_SPEED, LEFT_DIR);
      
      delay(2000);

      while(1)
        {
          Serial.print("line = ");
          Serial.print(line_pos);
          Serial.print("  ---   ");
          race();
//            for(int x = 0; x < N_SENS; x++){
//              Serial.print("sens_min"); Serial.print(x); Serial.print(" = "); Serial.print(sens_min[x]); Serial.print("; ");
//              Serial.print("sens_max"); Serial.print(x); Serial.print(" = "); Serial.print(sens_max[x]); Serial.print("; ");
//            }
//          Serial.println();
        }
      
      

// Serial.print(" --- ");


}

void race(void){
    last_line_pos = line_pos;
    line_pos = get_line_pos(COLOR, (last_line_pos>0));
        
    float PID_correction = get_PID_correction(line_pos, last_line_pos, KP, KD, KI);   
    float max_correction = SPEED;                   //Can be changed to a lower value in order to limit the correction, needs to be at most SPEED  //
    
    if(PID_correction > 0){
        PID_correction = (PID_correction > max_correction)? max_correction : PID_correction;
//        changeSpeed(rightMotor, SPEED - PID_correction);
//        changeSpeed(leftMotor, SPEED*(-1));

        changeSpeed(rightMotor, SPEED + PID_correction);
        changeSpeed(leftMotor, (SPEED - PID_correction)*(-1));
//        Serial.print("rightMotor = "); 
//        Serial.print(SPEED + PID_correction); 
//        Serial.print(" --  ");
//        Serial.print("leftMotor = "); 
//        Serial.print((SPEED - PID_correction)*(-1)); 
//        Serial.print(" --  ");
    }else{
        PID_correction = (PID_correction < -max_correction)? -max_correction : PID_correction;
//        changeSpeed(rightMotor, SPEED);
//        changeSpeed(leftMotor, (SPEED + PID_correction)*(-1));

        changeSpeed(rightMotor, SPEED + PID_correction);
        changeSpeed(leftMotor, (SPEED - PID_correction)*(-1));
//        Serial.print("rightMotor = "); 
//        Serial.print(SPEED + PID_correction); 
//        Serial.print(" --  ");
//        Serial.print("leftMotor = "); 
//        Serial.print((SPEED - PID_correction)*(-1)); 
//        Serial.print(" --  ");
    }
//        Serial.print("PID_correction = ");
//          Serial.print(PID_correction);  
//          Serial.println("  ---   ");  
}

void calibrate(int cal_time, int cal_speed, int cal_dir){
  ms = millis();
//  dW(LEDG, LOW);
  while((ms + cal_time) > millis()){
//    dW(LEDG, millis()%100 < 50);        //Blink led
    if(cal_dir == RIGHT_DIR){
      changeSpeed(rightMotor, cal_speed);
      changeSpeed(leftMotor, cal_speed);
    }
      
    if(cal_dir == LEFT_DIR){
      changeSpeed(rightMotor, -cal_speed);
      changeSpeed(leftMotor, -cal_speed);
    }
    
    int sens_value[N_SENS];
    for(int x = 0; x < N_SENS; x++){
      sens_value[x] = analogRead(SENSOR[x]);
      sens_min[x] = (sens_value[x] < sens_min[x]) ? sens_value[x] : sens_min[x];
      sens_max[x] = (sens_value[x] > sens_max[x]) ? sens_value[x] : sens_max[x];
    }
  }
  changeSpeed(rightMotor, 0);
  changeSpeed(leftMotor, 0);
//  dW(LEDG, HIGH);
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

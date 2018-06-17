const int ATTACK = 0;
const int SEARCH_TARGET = 1;
const int STOP = 2;

int state1 = STOP;

void strategy() {
  switch (state1) {
    case STOP:
      turnRight();
      state1 = SEARCH_TARGET;
      
      break;
    case SEARCH_TARGET:
      refreshSonar(sonar);

      if (sonar.distance < 60) {                //было 110
        stright();
        state1 = ATTACK;
        delay(200);
      }
        
      break;

    case ATTACK:
      
      refreshSensor(leftSensor);
      refreshSensor(rightSensor);

      //refreshSonar(sonar);
      
      if (leftSensor.lineDetected || rightSensor.lineDetected) {
          stop();
          reverse();
          delay(400);
          turnRight();
          delay(100);
          
          state1 = SEARCH_TARGET;
        }
        
           
      break;
  }
  
}


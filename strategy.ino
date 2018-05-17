const int ATTACK = 0;
const int SEARCH_TARGET = 1;
const int STOP = 2;

int state = STOP;

void strategy() {
  switch (state) {
    case STOP:
      turnRight();
      state = SEARCH_TARGET;
      
      break;
    case SEARCH_TARGET:
      refreshSonar(sonar);

      if (sonar.distance < 75) {                //было 110
        stright();
        state = ATTACK;
        delay(300);
      }
        
      break;

    case ATTACK:
      
      refreshSensor(leftSensor);
      refreshSensor(rightSensor);

      refreshSonar(sonar);
      
      if (leftSensor.lineDetected || rightSensor.lineDetected) {
          stop();
          reverse();
          delay(400);
          turnRight();
          delay(100);
          
          state = SEARCH_TARGET;
        }
        
           
      break;
  }
  
}


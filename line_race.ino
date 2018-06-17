const int STRAIGHT = 1;
const int RIGHT10 = 2;
const int RIGHT20 = 3;
const int LEFT10 = 4;
const int LEFT20 = 5;

int state = STRAIGHT;

void line_race() {
  
  switch (state)  {
    
    case STRAIGHT:
      stright();
      
      refreshSensor(d3);
      if (d3.lineDetected == 1)
        state = RIGHT10;

      refreshSensor(d5);
      if (d5.lineDetected == 1)
        state = LEFT10;
    break;

    case RIGHT10:
      left10();

      refreshSensor(d2);
      if (d2.lineDetected == 1)
        state = RIGHT20;

      refreshSensor(d4);
      if (d4.lineDetected == 1)
        state = STRAIGHT;
    break;

    case RIGHT20:
      left20();

      refreshSensor(d3);
      if (d3.lineDetected == 1)
        state = RIGHT10;
    break;

    case LEFT10:
      right10();

      refreshSensor(d6);
      if (d6.lineDetected == 1)
        state = LEFT20;

      refreshSensor(d4);
      if (d4.lineDetected == 1)
        state = STRAIGHT;
    break;

    case LEFT20:
       right20();

      refreshSensor(d5);
      if (d5.lineDetected == 1)
        state = LEFT10;


    break;

    
  }

}

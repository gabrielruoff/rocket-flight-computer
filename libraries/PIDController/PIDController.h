#ifndef PIDController_h
#define PIDController_h

#include "Arduino.h"

class PIDController
{
  public:
    PIDController(float pgain, float igain, float dgain);
    float iterate(float x);
    setInitial(float initial);
    float p;
    float i;
    float d;
    float x_sum;
    float x_prev[10];
    float iterations;
};

#endif

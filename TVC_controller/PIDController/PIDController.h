#ifndef PIDController_h
#define PIDController_h

#include "Arduino.h"

class PIDController
{
  public:
    PIDController(float pgain, float igain, float dgain);
    float getCorrectionFactor(float err[], float samplingTime);
    float p;
    float i;
    float d;
  private:
    int _pin;
};

#endif

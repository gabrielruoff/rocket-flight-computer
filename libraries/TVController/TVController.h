#ifndef TVCController_h
#define TVCController_h

#include "Arduino.h"
#include <Servo.h>

class TVController
{
  public:
    Servo xServo;
    Servo yServo;
    TVController(Servo x, Servo y, int xZero, int yZero);
    void init(int xPin, int yPin);
    int xPin;
    int yPin;
    void moveX(int degree);
    void moveY(int degrees);
    long map(long x, long in_min, long in_max, long out_min, long out_max);
    int position;
  private:
    int x0;
    int y0;
};

#endif

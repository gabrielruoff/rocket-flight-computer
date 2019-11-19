#include "Arduino.h"
#include "TVController.h"
#include <Servo.h>

// define x and y servo mins and maxes for
// the TVC's 5 degree range
#define xMin 1
#define xMax 1
#define yMin 1
#define yMax 1

TVController::TVController(Servo x, Servo y, int xZero, int yZero)
{
    Servo xServo = x;
    Servo yServo = y;
    
    int x0 = xZero;
    int y0 = yZero;
    
}

void TVController::init(int xPin, int yPin)
{
    xServo.attach(xPin);
    yServo.attach(yPin);
    
    xServo.write(x0);
    yServo.write(y0);
}

// maps values to a different numerical range
long TVController::map(long x, long in_min, long in_max, long out_min, long out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void TVController::moveX(int degrees)
{
    int position = int(map(degrees, 0, 5, xMin, xMax));
    xServo.write(position);
}

void TVController::moveY(int degrees)
{
    int position = int(map(degrees, 0, 5, yMin, yMax));
    yServo.write(position);
}

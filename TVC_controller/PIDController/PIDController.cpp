#include "Arduino.h"
#include "PIDController.h"

PIDController::PIDController(float pgain, float igain, float dgain)
{
  p = pgain;
  i = igain;
  d = dgain;
}

float PIDController::getCorrectionFactor(float err[], float samplingTime) {
  // add all of the error values
  int sum = 0;
  for(int i=0; i<sizeof(err);i++) {

  sum += err[i];
  }
 //find the average rate of change of the error
 float derr = (err[sizeof(err)]-err[0])/samplingTime;
    Serial.print("deriv: ");
    Serial.print(err[sizeof(err)]);
    Serial.print(" minus ");
    Serial.print(err[0]);
    Serial.print(" equals ");
    Serial.println(err[sizeof(err)]-err[0]);
    
  return (err[sizeof(err)]*p) + (i*sum) + (d*derr);
}


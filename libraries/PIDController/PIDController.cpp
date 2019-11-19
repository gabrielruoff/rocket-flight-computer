#include "Arduino.h"
#include "PIDController.h"

PIDController::PIDController(float pgain, float igain, float dgain)
{
  p = pgain;
  i = igain;
  d = dgain;
}

float PIDController::getCorrectionFactor(float err[], float samplingTime) {

  Serial.println("");
  Serial.println("err array (PID)");
  for(int i=0;i<5;i++) {

    Serial.println(err[i]);

  }
  Serial.println("");




  // add all of the error values
  float sum = 0;
  for(int i=0; i<5;i++) {

  sum += err[i];

  }
  // Serial.print("err sum (PID): ");
  // Serial.println(sum);
 //find the average rate of change of the error
 float derr = (err[4]-err[0])/samplingTime;
  //   Serial.print("deriv: ");
  //   Serial.print(err[4]);
  //   Serial.print(" minus ");
  //   Serial.print(err[0]);
  //   Serial.print(" equals ");
  //   Serial.println(err[4]-err[0]);

  // Serial.print("p = ");
  // Serial.print(p);
  // Serial.print(" i = ");
  // Serial.print(i);
  // Serial.print(" d = ");
  // Serial.println(d);

  // Serial.print("PID Calculation: pgain: ");
  // Serial.print(err[4]*p);
  // Serial.print(" igain: ");
  // Serial.print(i*sum);
  // Serial.print(" dgain: ");
  // Serial.println(d*derr);
  // Serial.print("PID Calculated Error: ");
  // Serial.println((err[4]*p) + (i*sum) + (d*derr));
    
  return (err[4]*p) + (i*sum) + (d*derr);
}


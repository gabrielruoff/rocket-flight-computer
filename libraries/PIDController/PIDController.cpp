#include "Arduino.h"
#include "PIDController.h"

PIDController::PIDController(float pgain, float igain, float dgain)
{
  p = pgain;
  i = igain;
  d = dgain;

  iterations = 0;
  x_sum = 0;
  x_prev = 0;
}

PIDController::setInitial(float initial) {
  x_prev = initial;
}

float PIDController::iterate(float x) {

  iterations++;
  x_sum += x;

  Serial.println("");
  float p_correction = p * x;
  Serial.print("p_correction: ");
  Serial.println(p_correction);

  float i_correction = i * (x_sum / iterations);
  Serial.print("i_correction: ");
  Serial.println(i_correction);

  float deriv = x - x_prev;
  float d_correction = d * deriv;
  Serial.print("d_correction: ");
  Serial.println(d_correction);

  float correction = p_correction + i_correction + d_correction;

  Serial.print("total correction: ");
  Serial.println(correction);

  x_prev = x;

  return correction;

  }
  
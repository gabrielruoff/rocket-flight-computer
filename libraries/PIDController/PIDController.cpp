#include "Arduino.h"
#include "PIDController.h"

PIDController::PIDController(float pgain, float igain, float dgain)
{
  p = pgain;
  i = igain;
  d = dgain;

  iterations = 0;
    float x_prev[10];
  x_sum = 0;
}

PIDController::setInitial(float initial) {
  x_prev[0] = initial;
}

float PIDController::iterate(float x) {

    x_sum = 0;
  iterations++;
  x_sum += x;

  Serial.println("");
  float p_correction = p * x;
  Serial.print("p_correction: ");
  Serial.println(p_correction);

    Serial.println("previous values:");
    for(int i = 0; i<10; i++) {
        
        x_sum += x_prev[i];
        Serial.println(x_prev[i]);
        
    }
    
    Serial.print("i sum: ");
    Serial.println(x_sum);
  float i_correction = i * (x_sum);
  Serial.print("i_correction: ");
  Serial.println(i_correction);

    // shift array over 1
    int n = sizeof(x_prev)/sizeof(x_prev[0]);
    for(int i = n; i>0; i--) {
        
        x_prev[i] = x_prev[i-1];
        
    }
    
  float deriv = x - x_prev[0];
  float d_correction = d * deriv;
  Serial.print("d_correction: ");
  Serial.println(d_correction);

  float correction = p_correction + i_correction + d_correction;

  Serial.print("total correction: ");
  Serial.println(correction);

  x_prev[0] = x;

  return correction;

  }
  

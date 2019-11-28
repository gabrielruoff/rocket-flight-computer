#include <rocket_telemetry.h>

rocket_telemetry telemetry;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);
  telemetry.initXBee();

}

void loop() {
  // put your main code here, to run repeatedly:

  if(Serial.available())
  {

    telemetry.sendToGroundStation(Serial.readString());
    
  }

}

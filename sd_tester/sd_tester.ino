#include <rocket_telemetry.h>

#define sdpin 10

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  rocket_telemetry telemetry(sdpin);
  Serial.println("");

  Serial.println("deleting log.txt");
  telemetry.deleteFile("log.txt");

  Serial.println("writing to log.txt");
    for (int i = 0; i < 10; i++) {

    telemetry.logToFile("logging" + String(i+1), "log.txt");

  }

  Serial.println("");
  Serial.println("printing log.txt");
  telemetry.printFile("log.txt");

}

void loop() {
  // put your main code here, to run repeatedly:

}

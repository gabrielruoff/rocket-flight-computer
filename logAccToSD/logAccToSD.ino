#include <rocket_telemetry.h>

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>
#include <Adafruit_L3GD20_U.h>
#include <Adafruit_9DOF.h>

#define sdpin 10



// Assign an ID to the sensors
Adafruit_9DOF dof = Adafruit_9DOF();
Adafruit_LSM303_Accel_Unified accel = Adafruit_LSM303_Accel_Unified(30301);
Adafruit_LSM303_Mag_Unified mag = Adafruit_LSM303_Mag_Unified(30302);

void setup() {
  // put your setup code here, to run once:
rocket_telemetry telemetry;
Serial.begin(115200);
telemetry.initSDCard(sdpin);

telemetry.deleteFile("log.txt");
telemetry.logToFile("begin log", "log.txt");

initSensors();

long t0 = millis();

int readings = 0;

while(millis()-t0 < 10000) {

  sensors_vec_t orientation = getOrientation();
  Serial.print("pitch: ");
  Serial.println(orientation.pitch);
  Serial.println("logging pitch");
  telemetry.logToFile(String((long(millis())-t0)) + "\t" + String(orientation.pitch), "log.txt");

  readings++;
  
}

Serial.print("readings: ");
Serial.println(readings);

}

void loop() {
  // put your main code here, to run repeatedly:

}

// Initialize Sensors
void initSensors()
{
  if (!accel.begin())
  {
    /* There was a problem detecting the LSM303 ... check your connections */
    Serial.println(F("Ooops, no LSM303 detected ... Check your wiring!"));
    while (1);
  }
  if (!mag.begin())
  {
    /* There was a problem detecting the LSM303 ... check your connections */
    Serial.println("Ooops, no LSM303 detected ... Check your wiring!");
    while (1);
  }
}

// Reads an acceleration event and returns an orientation object
sensors_vec_t getOrientation() {

  sensors_event_t mag_event;
  sensors_event_t accel_event;
  sensors_vec_t orientation;

  //Get pitch and roll from sensor
  accel.getEvent(&accel_event);
  if (dof.accelGetOrientation(&accel_event, &orientation)) {

  } else {

    Serial.println("Could not get accelerometer data. Check hardware.");

  }

  //Get heading from sensor
  mag.getEvent(&mag_event);
  if (dof.magGetOrientation(SENSOR_AXIS_Z, &mag_event, &orientation)) {

  } else {

    Serial.println("Could not get magnometer data. Check hardware.");

  }

  return orientation;

}

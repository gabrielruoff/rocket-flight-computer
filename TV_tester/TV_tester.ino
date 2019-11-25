#include <TVController.h>
#include <Servo.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>
#include <Adafruit_L3GD20_U.h>
#include <Adafruit_9DOF.h>

Servo x;
Servo y;

#define x0 45
#define y0 45

TVController TVC(x, y, x0, y0);

// Assign an ID to the sensors
Adafruit_9DOF dof = Adafruit_9DOF();
Adafruit_LSM303_Accel_Unified accel = Adafruit_LSM303_Accel_Unified(30301);
Adafruit_LSM303_Mag_Unified mag = Adafruit_LSM303_Mag_Unified(30302);

/* Update this with the correct SLP for accurate altitude measurements */
float seaLevelPressure = SENSORS_PRESSURE_SEALEVELHPA;

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

void setup() {
  // put your setup code here, to run once:

  TVC.init(4, 5);
  Serial.begin(115200);

  Serial.println("Initializing Sensors");
  initSensors();

}

void loop() {
  // put your main code here, to run repeatedly:

    int roll = 0;
    int pitch = 0;
    for(int i=0;i<5;i++) {
    sensors_vec_t o = getOrientation();
    roll+=o.roll;
    pitch+=o.pitch;
    }
    roll/=5;
    pitch/=5;

    TVC.moveX(map(roll, -90, 90, 0, 180));
    TVC.moveY(map(pitch, -90, 90, 0, 180));

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

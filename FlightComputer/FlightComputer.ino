#include <PIDController.h>
#include <TVController.h>

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>
#include <Adafruit_L3GD20_U.h>
#include <Adafruit_9DOF.h>

#include <Servo.h>

//define PID values
#define P 0.5
#define I 0.2
#define D 1

//define offset variables
float pitchOffset = 0;
float rollOffset = 0;
float headingOffset = 0;

//define error arrays
float err[5];
float suberr = 0;

//define LEDs and Buzzer
int statusLED = 7;
int buzzer = 6;

//define servos and their zeroes
Servo x;
Servo y;

#define x0 45
#define y0 45

//define PIDController
PIDController pid(P, I, D);

//define Thrust Vectoring Controller
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
  Serial.begin(115200);
  Serial.println("Flight Computer Starting"); Serial.println("");

  //initialize servos and sensors, binding x to pin 4 and y to pin 5
  Serial.println("Initializing Sensors");
  initSensors();
  TVC.init(4, 5);
  
  //sound buzzer
  tone(buzzer, 1000, 500);
  delay(200);
  tone(buzzer, 1000, 100);
  

  // Set sensor offsets
  Serial.println("Press enter to set sensor offsets");
  while(!Serial.available()) {
    
  }
  sensors_vec_t offsets = getOrientation();
  pitchOffset = offsets.pitch;
  rollOffset = offsets.roll;
  headingOffset = offsets.heading;
  Serial.println("Sensor offsets set");
  delay(500);

}

void loop() {

  //turn LED on
  digitalWrite(statusLED, HIGH);

  sensors_vec_t orientation = getOrientation();
  Serial.print("Pitch: ");
  Serial.print(orientation.pitch - pitchOffset);
  Serial.print("; Roll: ");
  Serial.print(orientation.roll - rollOffset);
  Serial.print("; Heading: ");
  Serial.println(orientation.heading - headingOffset);
  Serial.println("");

  //start counting reading time
  unsigned long t0 = micros();

  //Accumulate 5 readings and calculate their errors
  //Each reading is an average of ten sensor readings
  for(int i=0;i<5;i++){

    suberr = 0;

    //accumulate ten readings (suberrs) from the sensor and average them
    //into one reading
    for(int j=0;j<10;j++){

      //get a pitch reading from the sensor and subtract the offset
      suberr+=(getOrientation().pitch-pitchOffset);
      
    }

    //average all ten readings
    suberr/=10;

    Serial.print("Suberr avg: ");
    Serial.println(suberr);

    err[i] = suberr;
    
  }

  float samplingTime = (micros()-t0)*pow(10,-6);
  Serial.print("Sampling time: ");
  Serial.println(samplingTime);

  float corrFactor = -pid.getCorrectionFactor(err, samplingTime);
  Serial.print("Correction Factor: ");
  Serial.println(corrFactor);
  Serial.println("");
  delay(500);

  //turn LED off
  digitalWrite(statusLED, LOW);

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

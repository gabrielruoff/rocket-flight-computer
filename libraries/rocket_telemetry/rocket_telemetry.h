#ifndef rocket_telemetry_h
#define rocket_telemetry_h

#include "Arduino.h"
#include <SPI.h>
#include <SD.h>
#include <Servo.h>
#include <SoftwareSerial.h>

class rocket_telemetry
{

    public:
    rocket_telemetry();
    bool initSDCard(int SDPin);
    bool logToFile(String str, String filename);
    bool connectToGroundStation();
    void sendToGroundStation(String str);
    void initXBee();
    void sendHeartbeat();
    void printDirectory(File dir, int numTabs);
    void printFile(String filename);
    void deleteFile(String filename);
    String filename;

    private:
    File log;
    File file;
    String str;
    int SDPin;
    SoftwareSerial XBee;

};

#endif

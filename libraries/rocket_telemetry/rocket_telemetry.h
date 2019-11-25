#ifndef rocket_telemetry_h
#define rocket_telemetry_h

#include "Arduino.h"
#include <SPI.h>
#include <SD.h>
#include <Servo.h>

class rocket_telemetry
{

    public:
    rocket_telemetry(int SDPin);
    bool logToFile(String str, String filename);
    bool connectToGroundStation();
    bool sendToGroundStation(String str);
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

};

#endif

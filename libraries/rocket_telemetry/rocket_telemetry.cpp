#include "rocket_telemetry.h"
#include "Arduino.h"
#include <SPI.h>
#include <SD.h>
#include <Servo.h>
#include <SoftwareSerial.h>

// SD card stuff

rocket_telemetry::rocket_telemetry(void) : XBee(SoftwareSerial(2, 3))
{
    
}

bool rocket_telemetry::initSDCard(int SDPin) {
    
    File initFile;
    File root;
    
    Serial.print("Initializing SD card...");
    
    if (!SD.begin(SDPin)) {
        Serial.println(" initialization failed!");
        return false;
    }
    Serial.println(" initialization done.");
    
    // delete the init file
    SD.remove("INIT.TXT");
    
    // print the contents of the SD card
    Serial.println("SD card contents:");
    printDirectory(root, 0);
    
    // open the file. note that only one file can be open at a time,
    // so you have to close this one before opening another.
    initFile = SD.open("init.txt", FILE_WRITE);
    
    // if the file opened okay, write to it:
    if (initFile) {
        Serial.println("Writing init sequence to init.txt");
        initFile.println("init");
        // close the file:
        initFile.close();
        Serial.println("done.");
        
        return true;
        
    } else {
        // if the file didn't open, print an error:
        Serial.println("error opening init.txt");
    }
    
}

bool rocket_telemetry::logToFile(String str, String filename) {
    
    File file = SD.open(filename, FILE_WRITE);
    
    if(file) {
    
        file.println(str);
        file.close();
        return true;
        
    }
    
    return false;
    
}

// XBee stuff

void rocket_telemetry::initXBee() {

    XBee.begin(9600);
    
}

bool rocket_telemetry::connectToGroundStation() {
    
}

void rocket_telemetry::sendToGroundStation(String str) {
    
    int n = str.length();
    
    // declaring character array
    char char_array[n + 1];
    
    // copying the contents of the
    // string to char array
    strcpy(char_array, str.c_str());
    
    XBee.write(char_array);
    
}

void rocket_telemetry::sendHeartbeat() {
    
}

void rocket_telemetry::printDirectory(File dir, int numTabs) {
    
    while (true) {
        
        File entry =  dir.openNextFile();
        if (! entry) {
            // no more files
            break;
        }
        for (uint8_t i = 0; i < numTabs; i++) {
            Serial.print('\t');
        }
        Serial.print(entry.name());
        if (entry.isDirectory()) {
            Serial.println("/");
            printDirectory(entry, numTabs + 1);
        } else {
            // files have sizes, directories do not
            Serial.print("\t\t");
            Serial.println(entry.size(), DEC);
        }
        entry.close();
    }
}

void rocket_telemetry::printFile(String filename) {
    
    File file;
    
    file = SD.open(filename, FILE_READ);
    if (file) {
        Serial.print(filename);
        Serial.println(":");
        
        // read from the file until there's nothing else in it:
        while (file.available()) {
            Serial.write(file.read());
        }
        // close the file:
        file.close();
    } else {
        // if the file didn't open, print an error:
        Serial.print("error opening ");
        Serial.println(filename);
    }
    
}

void rocket_telemetry::deleteFile(String filename) {
    
    SD.remove(filename);
    
}

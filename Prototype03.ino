/*
  Simple Audio Player for Arduino Zero

 Demonstrates the use of the Audio library for the Arduino Zero

 Hardware required :
 * Arduino shield with a SD card on CS4
 * A sound file named "test.wav" in the root directory of the SD card
 * An audio amplifier to connect to the DAC0 and ground
 * A speaker to connect to the audio amplifier

 
 Arturo Guadalupi <a.guadalupi@arduino.cc>
 Angelo Scialabba <a.scialabba@arduino.cc>
 Claudio Indellicati <c.indellicati@arduino.cc>

 This example code is in the public domain

 http://arduino.cc/en/Tutorial/SimpleAudioPlayerZero

*/

#include <SD.h>
#include <SPI.h>
#include <AudioZero.h>

int sdPin = 4;
int sensorPin = A2;
int sensorValue = 0;
int sampleRateKHz = 2*44100;

void setup()
{
  // debug output at 115200 baud
  Serial.begin(115200);

  // setup SD-card
  Serial.print("Initializing SD card...");
  if (!SD.begin(sdPin)) {
    Serial.println(" failed!");
    while(true);
  }
  Serial.println(" done.");
}

void loop()
{
  int count = 0;
  sensorValue = analogRead(sensorPin); 

  // print the sensor and mapped sensor values:
  Serial.print("Sensor Value: ");
  Serial.println(sensorValue);

  if (sensorValue > 150) {
    // sample rate (kHz): mono = 32000 => stereo = 44100 => stereo dual channel = 88200
    AudioZero.begin(sampleRateKHz);
    
    // open wave file from sdcard
    File myFile = SD.open("test.wav");
    if (!myFile) {
      // if the file didn't open, print an error and stop
      Serial.println("error opening test.wav");
      while (true);
    }
  
    Serial.println("Playing");
    
    // until the file is not finished  
    AudioZero.play(myFile);
    AudioZero.end();
  
    Serial.println("End of file. Thank you for listening!");
    sensorValue = 0;
  }
}

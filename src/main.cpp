#include <Arduino.h>
#include <TFMPlus.h>
TFMPlus tfmP;

#include <SoftwareSerial.h>

SoftwareSerial mySerial(4, 5);

void setup()
{
  Serial.begin(115200);
  delay(20);

  while(!Serial);

  mySerial.begin(115200);
  delay(20);
  tfmP.begin(&mySerial);

  if (!tfmP.sendCommand(SOFT_RESET, 0))
    tfmP.printReply();

  delay(500);

  if (!tfmP.sendCommand(GET_FIRMWARE_VERSION, 0))
    tfmP.printReply();

  if (!tfmP.sendCommand(SET_FRAME_RATE, FRAME_20))
    tfmP.printReply();

  delay(500);
}

// Initialize variables
int16_t tfDist = 0; // Distance to object in centimeters
int16_t tfFlux = 0; // Strength or quality of return signal
int16_t tfTemp = 0; // Internal temperature of Lidar sensor chip

void loop()
{
  delay(50); // Loop delay to match the 20Hz data frame rate

  if (tfmP.getData(tfDist, tfFlux, tfTemp)) // Get data from the device.
  {
    Serial.print("$DIST,");
    Serial.print(tfDist);
    Serial.println(",*");
  }
}
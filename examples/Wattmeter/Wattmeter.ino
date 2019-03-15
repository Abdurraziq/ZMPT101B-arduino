#include "ZMPT101B.h"
#include "ACS712.h"

/*
  This example shows how to measure the power consumption
  of devices in AC electrical system
*/

// We have ZMPT101B sensor connected to A0 pin of arduino
// Replace with your version if necessary
ZMPT101B voltageSensor(A0);

// We have 5 amps version sensor connected to A1 pin of arduino
// Replace with your version if necessary
ACS712 currentSensor(ACS712_05B, A1);

void setup()
{
  Serial.begin(9600);

  // calibrate() method calibrates zero point of sensor,
  // It is not necessary, but may positively affect the accuracy
  // Ensure that no current flows through the sensor at this moment
  // If you are not sure that the current through the sensor will not leak during calibration - comment out this method
  Serial.println("Calibrating... Ensure that no current flows through the sensor at this moment");
  delay(100);
  voltageSensor.calibrate();
  currentSensor.calibrate();
  Serial.println("Done!");
}

void loop()
{
  // To measure voltage/current we need to know the frequency of voltage/current
  // By default 50Hz is used, but you can specify desired frequency
  // as first argument to getVoltageAC and getCurrentAC() method, if necessary

  float U = voltageSensor.getVoltageAC();
  float I = currentSensor.getCurrentAC();

  // To calculate the power we need voltage multiplied by current
  float P = U * I;

  Serial.println(String("U = ") + U + " V");
  Serial.println(String("I = ") + I + " A");
  Serial.println(String("P = ") + P + " Watts");

  delay(1000);
}
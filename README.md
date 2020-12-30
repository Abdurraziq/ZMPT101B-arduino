# ZMPT101B

An Arduino library to interact with the [ZMPT101B](http://www.zeming-e.com/file/0_2013_10_18_093344.pdf), an active single phase AC voltage sensor module.

This library is based on [Ruslan Koptev](https://github.com/rkoptev) ACS712 current sensors library for Arduino <https://github.com/rkoptev/ACS712-arduino>. This library is modified so that it can be used with ZMPT101B voltage sensor with the same code principle.

## Methods

### **Constructor**

```c++
ZMPT101B(uint8_t _pin)
```

Constructor has a parameters for analog input to which it is connected.

### **getVoltagetAC()**

```c++
float getVoltageAC(uint16_t frequency )
```

This method allows you to measure AC voltage. Frequency is measured in Hz. By default frequency is set to 50 Hz. Method use the Root Mean Square technique for the measurement. The measurement itself takes time of one full period (1second / frequency). RMS method allow us to measure complex signals different from the perfect sine wave.

### **calibrate()**

```c++
int calibrate()
```

This method reads the current value of the sensor and sets it as a reference point of measurement, and then returns this value. By default, this parameter is equal to half of the maximum value on analog input - 512; however, sometimes this value may vary. It depends on the individual sensor, power issues etc… It is better to execute this method at the beginning of each program. Note that when performing this method, no current must flow through the sensor, and since this is not always possible - there is the following method:

### **setZeroPoint()**

```c++
void setZeroPoint( int _zero )
```

This method sets the obtained value as a zero point for measurements. You can use the previous method once, in order to find out zero point of your sensor and then use this method in your code to set starting point without reading sensor.

### **setSensitivity()**

```c++
void setSensitivity( float sens )
```

This method sets the sensitivity value of the sensor. This sensitivity value indicates how much the output voltage value read by the ADC is compared to the value of the measured voltage source. The default value is 0.001.

## Example

This is an example of measuring electrical power using the zmpt101b sensor for voltage measurement and acs712 sensor for current measurements.

### Circuit

![circuit](/img/schematic.png)

### Code

This example code use this [ACS712 library for arduino](https://github.com/rkoptev/ACS712-arduino).

```c++
#include "ZMPT101B.h"
#include "ACS712.h"

// ZMPT101B sensor connected to A0 pin of arduino
ZMPT101B voltageSensor(A0);

// 5 amps version sensor (ACS712_05B) connected to A1 pin of arduino
ACS712 currentSensor(ACS712_05B, A1);

void setup()
{
  Serial.begin(9600);

  // calibrate() method calibrates zero point of sensor,
  // It is not necessary, but may positively affect the accuracy
  // Ensure that no current flows through the sensor at this moment
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
```

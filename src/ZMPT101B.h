#ifndef ZMPT101B_h
#define ZMPT101B_h

#include <Arduino.h>

#if CONFIG_IDF_TARGET_ESP32 == 1
#define ADC_SCALE 4095.0
#define VREF 3.3
#else
#define ADC_SCALE 1023.0
#define VREF 5.0
#endif
#define DEFAULT_FREQUENCY 50

class ZMPT101B
{
public:
	ZMPT101B(uint8_t _pin);
	int calibrate();
	float calculatesSensitivity(float voltage);
	void setZeroPoint(int _zero);
	void setSensitivity(float sens);
	int getZeroPoint();
	float getVoltageDC();
	float getVoltageAC(uint16_t frequency = 50);

private:
#if CONFIG_IDF_TARGET_ESP32 == 1
	int zero = 2048;
#else
	int zero = 512;
#endif
	float sensitivity;
	uint8_t pin;
};

#endif
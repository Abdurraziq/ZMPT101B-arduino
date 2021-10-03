#ifndef ZMPT101B_h
#define ZMPT101B_h

#include <Arduino.h>

#define ADC_SCALE 4095.0
#define VREF 3.3
#define DEFAULT_FREQUENCY 50

class ZMPT101B
{
public:
	ZMPT101B(uint8_t _pin);
	int calibrate();
	void setZeroPoint(int _zero);
	void setSensitivity(float sens);
	int getZeroPoint();
	float getVoltageDC();
	float getVoltageAC(uint16_t frequency = 50);
	float calculateSensitivity(ZMPT101B sensor, float voltage);

private:
	int zero = 1800;
	float sensitivity;
	uint8_t pin;
};

#endif
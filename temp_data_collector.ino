#include "Arduino.h"
#include "WiFi101.h"
#include "WiFiUdp.h"

#define DEBUG

const int ANLG_THERM_IN = A0;

void setup() {
	#ifdef DEBUG
	Serial.begin(9600);
	while(!Serial);
	#endif //DEBUG
}

void loop() {
	int read = analogRead(ANLG_THERM_IN);
	double temp = temperature(read);

	#ifdef DEBUG
	Serial.println(temp);
	#endif

	delay(100);
}

double temperature(int rawADC) {  //Function to perform the fancy math of the Steinhart-Hart equation
	double temp;
	temp = log(((10240000 / rawADC) - 10000));
	temp = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * temp * temp)) * temp );
	temp = temp - 273.15; // Convert Kelvin to Celsius
	temp = (temp * 9.0) / 5.0 + 32.0;
	return temp;
}

#include <OneWire.h>
#include <DallasTemperature.h>
// Porta do pino de sinal do DS18B20
#define ONE_WIRE_BUS 3

int rainPin = 7; // Pin wich rain sensor
int presencePin = 8; // Pin with presence sensor
int enginePin = 13; // Pin to turn on engine 

// Define the oneWire instace to comunicate with sensor
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
DeviceAddress sensor1;

void setup(){
	pinMode(rainPin, INPUT); // Define pin 7 how input 
	pinMode(presencePin, INPUT); // Define pin 8 how input
	pinMode(enginePin, OUTPUT); // Define pin 13 how output
}

void loop(){
	float temp; // Variable declarated to store temperature value
	int rain, presence; // Variable declarated to store rain and presence value
	
	// Reading the rain sensor value
	rain = digitalRead(rainPin); 
	
	// Reading the presence sensor value
	presence = digitalRead(presencePin); 

	// Reading the temperature sensor value
	sensors.requestTemperatures();
	temp = sensors.getTempC(sensor1);

	// Test if presence value exists
	if(presence == 1) {

		// Test if temperature is bigger than 25 degrees celsius
		if(temp > 25) {

			// Test if it's raining
			if(rain == 0) {
				digitalWrite(enginePin, HIGH); // Signal to open window
			} else {
				digitalWrite(enginePin, LOW); // Signal to close window
			}
		} else {
			digitalWrite(enginePin, LOW); // Signal to close window
		}
	} else {

		// Test if it's raining
		if(rain == 1) {
			digitalWrite(enginePin, LOW); // Signal to close window
		}
	}

	delay(2000); // Wait 2 seconds
}

#include <Arduino.h>

#include <UtilsI2C.h>
#include <Utils.h>
#include <Wire.h>

void scanBus(TwoWire& bus) {
	int nDevices;

	myPrintf( "Scanning I2C bus...\n" );

	nDevices = 0;
	for(byte address = 1, error; address < 127; ++address ) {
		bus.beginTransmission( address );
		error = bus.endTransmission();

		if ( error==0 ) {
			myPrintf( "I2C device found at address 0x%2X.\n", address );
			nDevices++;
		}
		else if ( error==4 ) {
			myPrintf( "Unknown error at address 0x%2X.\n", address );
		}
	}

	if ( nDevices==0 ) {
		myPrintf( "No I2C devices found.\n\n" );
	}
	else {
		myPrintf( "Done.\n\n");
	}
}

void scanBus(TwoWire& bus, Print& pr) {
	int nDevices;

	myPrintf( "Scanning I2C bus...\n" );
	myPrintf( "Scan...\n" );

	nDevices = 0;
	for(byte address = 1, error; address < 127; ++address ) {
		bus.beginTransmission( address );
		error = bus.endTransmission();

		if ( error==0 ) {
			myPrintf( "I2C device found at address 0x%2X.\n", address );
			myPrintf(pr, "I2C 0x%2X\n", address );
			nDevices++;
		}
		else if ( error==4 ) {
			myPrintf( "Unknown error at address 0x%2X.\n", address );
		myPrintf( pr, "Error 0x%2X\n", address );
		}		
	}

	if ( nDevices==0 ) {
		myPrintf( "No I2C devices found.\n\n" );
	myPrintf( pr, "No I2C\n\n" );
	}
	else {
		myPrintf( "Done.\n\n");
		myPrintf( pr, "Done\n\n");
	}
}
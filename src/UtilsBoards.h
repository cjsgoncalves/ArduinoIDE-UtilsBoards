#ifndef _UtilsBoards_h_
#define _UtilsBoards_h_

#ifdef ARDUINO_TTGO_LoRa32_V1
	// ESP32 – TTGO LoRa32-OLED V1
	#define BOARD_TYPE_1
	#define BOARD_FAMILY	"ESP32"
	#define BOARD_NAME	"ESP32 – TTGO LoRa32-OLED V1"

	#else
		#ifdef ARDUINO_TTGO_T1
			// ESP32 – TTGO T1
			#define BOARD_TYPE_2
			#define BOARD_FAMILY	"ESP32"
			#define BOARD_NAME	"ESP32 – TTGO T1"

		#else
			#ifdef ARDUINO_ESP32_DEV
				// ESP32 – DOIT ESP32 DEVKIT V1
				#define BOARD_TYPE_3
				#define BOARD_FAMILY	"ESP32"
				#define BOARD_NAME	"ESP32 – DOIT DEVKIT V1"

			#else
				#ifdef ARDUINO_ESP8266_WEMOS_D1MINI
					 // ESP8266 – LOLIN (WEMOS) D1 R2 & mini
					 #define BOARD_TYPE_4
					 #define BOARD_FAMILY	"ESP8266"
					 #define BOARD_NAME	"ESP8266 – LOLIN (WEMOS) D1 R2"

					 #else
						 #ifdef ARDUINO_ESP8266_GENERIC
							 // ESP8266 – Generic
							 #define BOARD_TYPE_5
							 #define BOARD_FAMILY	"ESP8266"
							 #define BOARD_NAME	"Generic ESP8266"

						 #else
							 // None of the above boards
							 #define BOARD_TYPE_6
							 #define BOARD_FAMILY	"Unknown"
							 #define BOARD_NAME	"Unknown"
						 #endif
				#endif
		#endif
	#endif
#endif

#ifdef BOARD_TYPE_1		// ESP32 – TTGO LoRa32-OLED V1
	#include <WiFi.h>
	#include <WiFiMulti.h>
	#include <ESPmDNS.h>

	#include <AsyncTCP.h>

	#include <SPIFFS.h>

	// Internal led pin
	#define LED_INTERNAL_PIN 2

	// I2C pins
	#define SDA 21
	#define SCL 22
#endif

#ifdef BOARD_TYPE_2		// ESP32 – TTGO T1
	#include <WiFi.h>
	#include <WiFiMulti.h>
	#include <ESPmDNS.h>

	#include <AsyncTCP.h>

	#include <SPIFFS.h>

	// Internal led pin
	#define LED_INTERNAL_PIN 22

	// I2C pins
	#define SDA 21
	#define SCL 22
#endif

#ifdef BOARD_TYPE_3		// ESP32 – DOIT ESP32 DEVKIT V1
	#include <WiFi.h>
	#include <WiFiMulti.h>
	#include <ESPmDNS.h>

	#include <AsyncTCP.h>

	#include <SPIFFS.h>

	// Internal led pin
	#define LED_INTERNAL_PIN 2

	// I2C pins
	#define SDA 21
	#define SCL 22
#endif

#ifdef BOARD_TYPE_4		// ESP8266 – LOLIN (WEMOS) D1 R2 & mini
	#include <ESP8266WiFi.h>
	#include <ESP8266WiFiMulti.h>
	#include <ESP8266mDNS.h>

	#include <ESPAsyncTCP.h>

	#include <FS.h>

	// Internal led pin
	#define LED_INTERNAL_PIN 2

	// I2C pins
	#define SDA 19
	#define SCL 20

	typedef ESP8266WiFiMulti WiFiMulti;
#endif

#ifdef BOARD_TYPE_5		// ESP8266 – Generic
	#include <ESP8266WiFi.h>
	#include <ESP8266WiFiMulti.h>
	#include <ESP8266mDNS.h>

	#include <ESPAsyncTCP.h>

	#include <FS.h>

	typedef ESP8266WiFiMulti WiFiMulti;

	// Internal led pin
	#define LED_INTERNAL_PIN 1

	// I2C pins
	#define SDA 0
	#define SCL 2	
#endif

#ifdef BOARD_TYPE_6		// Other Boards

	// Internal led pin
	#define LED_INTERNAL_PIN 1

	typedef void WiFiMulti;
#endif

#include <Print.h>

/**
	\brief
	Struct to hold the WiFi credentials.

	A WiFi credential is made by the name of the <b>SSID</b> and the corresponding <b>password</b>.

	\param ssid the <b>SSID</b> name of the network
	\param password the <b>password</b> name of the network
*/
typedef struct {
	const char* ssid;
	const char* password;
} WiFiMultiEntry, * PtrWiFiMultiEntry;

/**
	\brief
	Turn inboard LED <b>ON</b>.

	Utility macro to turn <b>ON</b> the internal LED of the board.
*/
#define internalLedOn()	digitalWrite( LED_INTERNAL_PIN, LOW )

/**
	\brief
	Turn inboard LED <b>OFF</b>.

	Utility macro to turn <b>OFF</b> the internal LED of the board.
*/
#define internalLedOff() digitalWrite( LED_INTERNAL_PIN, HIGH )

/**
	\brief
	Initialize the internal LED.

	This function configures the pin associatied with the internal LED to a digital output and turns off the internal LED.
*/
void initInternalLed();

/**
	\brief
	Blink the internal LED of the board.

	Function to blink the internal LED of the board. Internally uses the <code>delay(...)</code> function.
	
	\param onTime the amount of time to maintain the internal LED <b>ON</b>
	\param offTime the amount of time to maintain the internal LED <b>OFF</b>
*/
void blinkInternalLed(int onTime, int offTime);

/**
	\brief
	Show the board name.

	Utility function to show the name of the current board. By default the board name is printed to the default <code>Serial</code> port.
	
	\param pr Arduino <code>Print</code> object that suports the <b><code>print</code></b> and <b><code>println</code></b> methods
*/
void showBoardType(Print& pr=Serial);

/**
	\brief
	Initialize the WiFi.

	Function to initialize the WiFi component of the board in station mode (<code>WIFI_STA</code>).

	Beasides the authentication credentials (name of the <b>SSID</b> and corresponding <b>password</b>) this function accepts a set of aditional arguments that can be used to:

	<ul>
		<li>Reset the board if no connection could be established.</li>
		<li>Blink the internal LED while wainting for the establishment of the WiFi connection.</li>
		<li>Set the DNS host name of the board.</li>
		<li>Specify a <code>Print</code> object to show debug messages.</li>
	</ul>

	\param ssid name of the network
	\param password the matching password for the specified <code>SSID</code>
	\param resetIfNoWiFi boolean flag that can be used to reset the board if no connection could be done within 30 seconds. This is the default behavior
	\param blinkInternal boolean flag that can be used to controll the blinking of the interal LED while waiting for the establishment of the WiFi connection. The default behavior is to not blink the internal LED
	\param hostName DNS name of the board. By default the DNS name is not set.
	\param pr Arduino <code>Print</code> object that suports the <b><code>print</code></b> and <b><code>println</code></b> methods. By default these messages are shown in the default <code>Serial</code> port

	\return <b><code>true</code></b> if it was possible to connect the the specified network. In case of failure, if the flag <b><code>resetIfNoWiFi</code></b> is set to <b><code>true</code></b> the board is reset, else the value <b><code>false</code></b> is returned.
	
*/
bool initWiFi(
	const char* ssid, 
	const char* password, 
	const bool resetIfNoWiFi=true, 
	const bool blinkInternal=false, 
	const char* hostName=NULL, 
	Print& pr=Serial);

/**
	\brief
	Initialize the WiFi.

	Function to initialize the WiFi component of the board in station mode (<code>WIFI_STA</code>).

	This function receives a set of authentication credentials (name of the <b>SSID</b> and corresponding <b>password</b>). Thus board tries to establish a connection with every networs in the list until establish a connection.

	This function also accepts a set of aditional arguments that can be used to:

	<ul>
		<li>Reset the board if no connection could be established.</li>
		<li>Blink the internal LED while wainting for the establishment of the WiFi connection.</li>
		<li>Set the DNS host name of the board.</li>
		<li>Specify a <code>Print</code> object to show debug messages.</li>
	</ul>

	\param creds set of authentication credentials
	\param sizeOfCreds number of authentication credentials
	\param resetIfNoWiFi boolean flag that can be used to reset the board if no connection could be done within 30 seconds. This is the default behavior
	\param blinkInternal boolean flag that can be used to controll the blinking of the interal LED while waiting for the establishment of the WiFi connection. The default behavior is to not blink the internal LED
	\param hostName DNS name of the board. By default the DNS name is not set.
	\param pr Arduino <code>Print</code> object that suports the <b><code>print</code></b> and <b><code>println</code></b> methods. By default these messages are shown in the default <code>Serial</code> port

*/
bool initWiFi(
	PtrWiFiMultiEntry creds, 
	int sizeOfCreds, 
	const bool resetIfNoWiFi=true, 
	const bool blinkInternal=false, 
	const char* hostName=NULL, 
	Print& pr=Serial);

#endif // _UtilsBoards_h_

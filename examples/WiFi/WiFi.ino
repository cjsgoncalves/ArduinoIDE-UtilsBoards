/*
 * Setting the macro "DebugMode" here only works for files that exists in the projet directory.
 * 
 * In order for the macro work in all files (including the libraries) we need to define the macro in the compiler command line
 * For each platfor edit the file "platform.local.txt" and add the option:
 * 
 * -DDebugMode
 * 
 * to the properties "compiler.cpp.extra_flags"
 * 
 * The file "platform.local.txt" must be defined for each hardware platform.
 * 
 * For example, for the ESP32 the file is:
 * 
 * $HOMEPATH$\AppData\Local\Arduino15\packages\esp32\hardware\esp32\1.0.6
 * 
 * where $HOMEPATH$ is the home directory of the user (in my case is C:\Users\cgonc )
 */

#include <Utils.h>
#include <UtilsBoards.h>

WiFiMultiEntry creds[] = {
  { "SSID1", "pass1" },
  { "SSID2", "pass2" }
};

void setup() {
  DebugDelay( 2000 );
  
  serialBegin( 115200 );

  // The next message is printed only if the compliler flag -DDebugMode is set
  DebugMessagePrintf( "Board Testing.\n" );

  showBoardType();

  initInternalLed();

  // The next message is allways printed
  myPrintf( "Starting WiFi...\n" );

  // The debug messages inside the function "initWiFi" are printed only if the compliler flag -DDebugMode is set
    // Init WiFi with credential
    //initWiFi( creds[0].ssid, creds[0].password, true /*Blik internal led*/ );

    // Init WiFi with credential and esp hostname
    //initWiFi( creds[1].ssid, creds[1].password, false, "myESP32" /* ESP DNS name*/ );

    // Init WiFi using multiple credentials
    initWiFi( creds, 2 /*, false, NULL*/ );

    // Init WiFi using multiple credentials and esp hostname
    //initWiFi( creds, 2, true, "myESP32" );

  // The next message is allways printed
  myPrintf( "WiFi is ready.\n" );

  delay( 2000 );
}

void loop() {
  blinkInternalLed( 300, 700 );
}

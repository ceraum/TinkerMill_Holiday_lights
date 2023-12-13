#include "FastLED.h"
#include <PubSubClient.h>
#include "OTA.h"
#include "credentials.h"
#include "variables.h"

#define VOLTS          5
#define MAX_MA       5000
#define LEDPIN_1     2
#define LEDPIN_2     4
#define LED_TYPE     NEOPIXEL
#define BRIGHTNESS 80
#define FRAMES_PER_SECOND 120
#define FASTLED_INTERNAL

// Place your MQTT Broker IP address here:
const char* mqtt_server = "192.168.1.11";

WiFiClient espClient;
PubSubClient client(espClient);

// to hold the index and name of the window/ESP32
int winNum;
String winName;

// Actual number of LEDs
int NUM_LEDS_1;
int NUM_LEDS_2;

// Variables to hold the index number and name of the window
char* thisESP32;

// These define arrays bigger than any of the actual windows
CRGB leds_1[2000];
CRGB leds_2[750];

// Use this alternate assigment if using array description useful for some animation styles
// CRGBArray<2000> leds_1;
//CRGBArray<750> leds_2;

// Sets the leds in a wait state before first broadcast
bool start_animation = false;

// Special animations for windows that require them
bool mask_trees = false;
bool mask_sign = false;

// Holders for selected Palettes
CRGBPalette16 gCurrentPalette;
CRGBPalette16 gTargetPalette;

// Used to fill the glitter animation with changing colors
CRGB glitterList[] = {
    CRGB (255,255,255), // White
    CRGB (255,255,0),   // Yellow
    CRGB (255,255,0)    // Yellow
  };

// Which glitter color to use
int glitterColorIndex;

CRGB color_1 = (0, 0, 0);
CRGB color_2 = (0, 0, 0);

void setup() {
  //sanity delay and serial start
  Serial.begin(115200);
  delay(2000);

  // Get the window index ID
  winNum = windowNum(ESP.getEfuseMac());
  Serial.print("Window number:");
  Serial.println(winNum);

  // Create the window name
  winName = "win" + String(winNum);
  Serial.println(winName);

  // set up LED strip info
  // Get the actual number of leds on each strip from the variables list
  NUM_LEDS_1 = panels[winNum][0];
  NUM_LEDS_2 = perimeters[winNum][0];

  // Define the LED strips
  FastLED.addLeds<LED_TYPE,LEDPIN_1>(leds_1,NUM_LEDS_1).setCorrection(TypicalLEDStrip);
  FastLED.addLeds<LED_TYPE,LEDPIN_2>(leds_2,NUM_LEDS_2).setCorrection(TypicalLEDStrip);
  
  // Set power parameters for the led lights
  FastLED.setMaxPowerInVoltsAndMilliamps( VOLTS, MAX_MA);
  FastLED.setBrightness(BRIGHTNESS);

  // Fill with solid blue to inidcate wait for connection
  fill_solid(leds_1, NUM_LEDS_1, CRGB::Blue);
  fill_solid(leds_2, NUM_LEDS_2, CRGB::Blue);
  FastLED.show();

  // setup the OTA - this will connect to the wifi as well
  setupOTA("380WindowsSketch", mySSID, myPASSWORD);

  // The ID number used to identify the window
  Serial.println(ESP.getEfuseMac());
  
  // Fill with solid green to inidcate wait for connection to MQTT server
  fill_solid(leds_1, NUM_LEDS_1, CRGB::Green);
  fill_solid(leds_2, NUM_LEDS_2, CRGB::Green);
  FastLED.show();

  // setup the MQTT
  client.setServer(mqtt_server,1883);//1883 is the default port for MQTT server
  client.setCallback(callback);

  // Call this periodically
  ArduinoOTA.handle();

  // Fill with solid green to indicate wait for for animation start
  fill_solid(leds_1, NUM_LEDS_1, CRGB::Red);
  fill_solid(leds_2, NUM_LEDS_2, CRGB::Red);
  FastLED.show();

  glitterColorIndex = 1;

  

  // Setup the special masking for some windows
  if (winNum == 1) {

    Serial.println("Its a tree match");
    mask_trees = true;
  }

  else {
    mask_trees = false;
  }

  if (winNum == 2) {

    Serial.println("Its a sign match");
    mask_sign = true;
  }
  
  Serial.println("Waiting to start");

  // This must be called periodically for MQTT updates
  if (!client.connected()) {
        reconnect();
    }
  client.loop();

  Serial.println("Connected");

  while (!start_animation) {
    // wait for a broadcast
    client.loop();
  }
  Serial.println("Started");

  ArduinoOTA.handle();

  // on to the show

}

void loop() {

  // This must be called periodically for OTA updates
  ArduinoOTA.handle();

  // wait for a broadcast, also called periodically
  client.loop();
  
  //changing the third variable changes how quickly the lights fade
  fadeToBlackBy( leds_1, NUM_LEDS_1, 3);
  fadeToBlackBy( leds_2, NUM_LEDS_2, 3);


  EVERY_N_SECONDS( 5 ) { 
    glitterColorIndex = glitterColorIndex + 1;
    //Serial.print(glitterColorIndex);
    if ( glitterColorIndex > 2) {
        glitterColorIndex = 0;
    }
  }

  //changing this variable will increase the chance of a "star" popping up
  EVERY_N_MILLISECONDS( 20 ) { 
    addGlitter(255, leds_1);
    addGlitter(255, leds_2);
  }
  // drawTwinkles( leds_2);

  // Mask out elements if required (trees and sign)

  if (mask_trees) {
      
    draw_mask(tree_mask, sizeof tree_mask/sizeof tree_mask[0]);

  }

  if (mask_sign) {
      
    draw_mask(sign_mask, sizeof sign_mask/sizeof sign_mask[0]);

  }

  FastLED.show();

  // This must be called periodically for MQTT updates
  if (!client.connected()) {
        reconnect();
    }
  client.loop();

}










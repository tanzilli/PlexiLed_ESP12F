// https://github.com/tanzilli/PlexiLed

#include <Adafruit_NeoPixel.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncWebServer.h>
#include "LittleFS.h"
#include "html.h"

#define PIXEL_PIN     4
#define PIXEL_COUNT   12

const char* ssid     = "PlexiLed";
const char* password = "12345678";

uint8_t ledscene[PIXEL_COUNT*3];

Adafruit_NeoPixel strip(PIXEL_COUNT,PIXEL_PIN, NEO_GRB+NEO_KHZ800);

IPAddress local_IP(192,168,8,1);
IPAddress gateway(192,168,8,1);
IPAddress subnet(255,255,255,0);

AsyncWebServer server(80);

void FixedColor(int line_id,uint32_t color) {
  for(int i=0+(line_id*6); i<6+(line_id*6); i++) {
    strip.setPixelColor(i, color);
    strip.show();
  }
}

void setup() {
  Serial.begin(115200);

  Serial.print("Setting up the WiFi AP");

  WiFi.softAP(ssid, password);
  WiFi.softAPConfig(local_IP, gateway, subnet);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html);
  });

  server.on("/set_color_line1", HTTP_PUT, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", "Ok");
    int red=atoi(request->arg("red").c_str());
    int green=atoi(request->arg("green").c_str());
    int blue=atoi(request->arg("blue").c_str());
    FixedColor(0,strip.Color(red,green,blue));
  });

  server.on("/set_color_line2", HTTP_PUT, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", "Ok");
    int red=atoi(request->arg("red").c_str());
    int green=atoi(request->arg("green").c_str());
    int blue=atoi(request->arg("blue").c_str());
    FixedColor(1,strip.Color(red,green,blue));
  });

  server.on("/load_scene", HTTP_PUT, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", "Ok");
    Serial.println("/load_scene");
  });

  server.on("/save_scene", HTTP_PUT, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", "Ok");
    Serial.println("/save_scene");

    int pixel_counter=0;

    for (int i=0;i<PIXEL_COUNT*3;i+=3) {
       ledscene[i+0]=strip.getPixelColor(pixel_counter)>>16; 
       ledscene[i+1]=strip.getPixelColor(pixel_counter)>>8; 
       ledscene[i+2]=strip.getPixelColor(pixel_counter)>>0; 
       pixel_counter++;
    }

    File f = LittleFS.open("ledscene", "w");
    if (!f) {
      Serial.println("file open for writing failed");
    }
    f.write(ledscene,PIXEL_COUNT*3);
    f.close();
  });

  if (LittleFS.begin()!=true) {
    Serial.println("LittleFS error");  
  };

  if (!LittleFS.exists("ledscene")) {
    Serial.println("ledscene not exists");

    for (int i=0;i<PIXEL_COUNT*3;i+=3) {
      ledscene[i+0]=0;
      ledscene[i+1]=127;
      ledscene[i+2]=0;
    }

    File f = LittleFS.open("ledscene", "w");
    if (!f) {
      Serial.println("file open for writing failed");
    }
    f.write(ledscene,PIXEL_COUNT*3);
    f.close();
  }

  if (LittleFS.exists("ledscene")) {
    Serial.println("ledscene exists");
    File f = LittleFS.open("ledscene", "r");
    if (!f) {
      Serial.println("file open for reading failed");
    }
    f.read(ledscene,PIXEL_COUNT*3);
    f.close();
  }

  strip.begin();
  strip.setBrightness(100); 

  int index=0;
  for (int pixel_counter=0;pixel_counter<PIXEL_COUNT;pixel_counter++) {
    strip.setPixelColor(pixel_counter, strip.Color(ledscene[index+0],ledscene[index+1],ledscene[index+2]));
    index+=3;
  }
  strip.show(); 

  // Start Web server
  server.begin();
}

void loop() {
}


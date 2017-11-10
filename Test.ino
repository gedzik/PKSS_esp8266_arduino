
#include "dickbutt.h"
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>
#define OLED_RESET LED_BUILTIN //4
Adafruit_SSD1306 display(OLED_RESET);

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2


#define LOGO16_GLCD_HEIGHT 16 
#define LOGO16_GLCD_WIDTH  16 

IPAddress ip(12, 12, 12, 125);
void setup()
{
	/*lcd*/
	display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
	display.display();
	display.clearDisplay();
	delay(1000);
	display.display();
	delay(1000);
	display.drawBitmap(0, 0, dickbutt1, 128, 64, 1);
	display.display();
	delay(2000);
	display.clearDisplay();
	display.display();
	display.setTextSize(1);
	display.setTextColor(WHITE);
	display.setCursor(0, 0);
  /* wifi */
	WiFi.config(ip);
	bool isConnected = false;
	Serial.begin(115200);
	
	
	WiFi.begin("PKSS", "qwe147rty258");
	while (!(isConnected = WiFi.isConnected()))
	{
		Serial.println(isConnected);
		delay(500);
		display.println("Conecting...");
		display.display();
	}
	Serial.println(WiFi.gatewayIP());
	HTTPClient client;
	display.println("Conected!");
	display.display();
	client.begin("http://conti.ml");
	client.GET();
	WiFiClient stream = client.getStream();
	String s = stream.readString();

	Serial.println(s);

	
}

void loop()
{
	delay(1000);
	display.drawBitmap(0, 0, dickbutt1, 128, 64, 1);
	display.display();
	display.clearDisplay();
	delay(500);
	display.drawBitmap(0, 0, dickbutt2, 128, 64, 1);
	display.display();
	display.clearDisplay();
	Serial.println(WiFi.localIP());
  /* add main program code here */

}

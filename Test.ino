
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>
#include <Wire.h>


IPAddress ip(12, 12, 12, 125);
IPAddress gat(12, 12, 12, 55);
IPAddress subnet(255, 255, 255, 0);
WiFiClient client;
MySQL_Connection conn((Client *)&client);

char INSERT_SQL[] = "UPDATE pkss.system SET value = '10' WHERE name = 'test'";
char SELECT_SQL[] = "SELECT value FROM pkss.system WHERE name = 'test' ";

void setup()
{
  /* wifi */
	
	WiFi.config(ip, gat, subnet);
	bool isConnected = false;
	Serial.begin(115200);
	WiFi.begin("PKSS", "qwe147rty258");
	//WiFi.begin("gx0", "zxcvb123");
	//WiFi.begin("AndroidAP", "sddj1894");
	while (!(isConnected = WiFi.isConnected()))
	{
		Serial.println(isConnected);
		delay(500);
	}
	Serial.println(WiFi.gatewayIP());
	Serial.println("Connecting tosql ");
	if (conn.connect(gat, 3306, "pkss", "pkss125")) {
		delay(1000);
	}
	else {
		Serial.println("Connection failed.");
		conn.close();
	}
}
	/*
	HTTPClient client;

	client.begin("http://psychiatryk.ml");
	client.GET();
	WiFiClient stream = client.getStream();
	String s = stream.readString();

	Serial.println(s);*/
	//pinMode(8, OUTPUT);
	


void loop()
{
	row_values *row = NULL;
	long head_count = 0;

	//digitalWrite(D0, HIGH);
	//delay(500);
	//Serial.println(WiFi.localIP());
	//digitalWrite(D0, LOW);
  /* add main program code here */
	MySQL_Cursor *cur_mem = new MySQL_Cursor(&conn);
	MySQL_Cursor cur = MySQL_Cursor(&conn);
	cur_mem->execute(INSERT_SQL);
	cur.execute(SELECT_SQL);
	cur.get_columns();
	do {
		row = cur.get_next_row();
		if (row != NULL) {
			head_count = atol(row->values[0]);
		}
	} while (row != NULL);
	cur.close();
	Serial.println(head_count);
	delete cur_mem;
}

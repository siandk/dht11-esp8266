#include <DHT.h>
#include <DHT_U.h>
#include <ESP8266WiFi.h>
#include <WifiClient.h>

#define DHTPIN 2 // GPIO - 1 on ESP8266

const char* ssid     = "Simon";
const char* password = "aat55fbh";
const char* host = "192.168.43.83";
uint16_t port = 5000;

DHT dht(DHTPIN, DHT11);

void setup() {
  Serial.begin(115200);
  dht.begin();

  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
}

void loop()
{
  delay(2000);

  float temp = dht.readTemperature();
  float humi = dht.readHumidity();
  for (uint8_t i = 0; i < 2; i++)
  {
    delay(1000);
    String sensor;
    float value;
    if (i == 0)
    {
      sensor = "dht2-temp";
      value = temp;
    }
    else
    {
      sensor = "dht2-hum";
      value = humi;
    }
    String url = "/readings/add?sensor=" + sensor + "&value=" + value;  
  
    WiFiClient client;
    if (client.connect(host, port)) {
      client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                  "Host: " + host + ":" + port + "\r\n" + 
                  "Connection: keep-alive\r\n\r\n");
    }
    client.stop();
  }
}

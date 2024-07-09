#include <StringSplitter.h>
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <WiFiClientSecure.h>
#include <EEPROM.h>
#include <Wire.h>
#include <ESP8266TrueRandom.h>
#include <ArduinoJson.h>
#include <Adafruit_NeoPixel.h>
#include <AsyncElegantOTA.h>
#include <WebSocketsClient.h>
#include <Hash.h>
#include "web.h"
#include "utils.h"
#include <Ticker.h>
#include <ESP8266httpUpdate.h>
#include <PubSubClient.h>
#include <WebSerial.h>
#include <ESP8266Ping.h>


Ticker nightRider;
Ticker toneTimer;



const int currentVersion = 1;
const String LAMP_ID = "ts'u$squh!! |hqw#uh}q'!hswwu'qwt'tv"; //IVET - 1dc0bcde-db17-412c-ac4a-5007d2ee94fc - t!&u'&! h!'trhqtw&h$&q$hpuur!w  |q#&
//VLCOUN ac158e69-7dde-4162-a169-8846f4fced26 - $&tp} s|hr!! hqtswh$ts|h}}qs#q#& !ws
//TEST   16b0a640-dde9-42f0-84bd-6220b421b13e - ts'u$squh!! |hqw#uh}q'!hswwu'qwt'tv 
const int LEDCount = 15;

Adafruit_NeoPixel strip(LEDCount, D2, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel statusLed(1, D3, NEO_GRB + NEO_KHZ800);

const char ENDPOINT_CA_CERT[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
MIIDbTCCAlWgAwIBAgIUMbjGhpau+mWuhhJWNa/EAzpp6egwDQYJKoZIhvcNAQEL
BQAwRTELMAkGA1UEBhMCQVUxEzARBgNVBAgMClNvbWUtU3RhdGUxITAfBgNVBAoM
GEludGVybmV0IFdpZGdpdHMgUHR5IEx0ZDAgFw0yNDAzMDkwMTE4NTFaGA8yMTI0
MDIxNDAxMTg1MVowRTELMAkGA1UEBhMCQVUxEzARBgNVBAgMClNvbWUtU3RhdGUx
ITAfBgNVBAoMGEludGVybmV0IFdpZGdpdHMgUHR5IEx0ZDCCASIwDQYJKoZIhvcN
AQEBBQADggEPADCCAQoCggEBAKSD86vvgLVdZ0agg3X1H0qZMXkeJWw2zyqTKcGA
ZJkHDnVMjciRi9rSXsyh19cOwJbu2QWFJazorf0AZ+41gDHDCW+eAjC8lGEaiwpZ
/XQ0JJFQfJz+jmy2slHtkqpgmOvAS1a2RLy9XvPywQUw9PsAx6rfZm7JCbBZ0YKN
cVkalkM+yrK1dcbaIpC7EiAxwH81J3u2sCxX1D5crQV94DMsZTXT/CSkGS0CWxp/
vq1wzaqPNxlPGzTcc3Z1KQCt51LEGqM5EbIpe/aKp0ceg/1ZWRvyc8cD/0D+2LCs
qeLrEvkEHc9zeKu/+NBKW3y2SjPmCrJYZamvePFP1zMwbvkCAwEAAaNTMFEwHQYD
VR0OBBYEFCBlS8YIb19sT5+iyTh+v75OFn47MB8GA1UdIwQYMBaAFCBlS8YIb19s
T5+iyTh+v75OFn47MA8GA1UdEwEB/wQFMAMBAf8wDQYJKoZIhvcNAQELBQADggEB
AIn50arhAbnhJH3h/jzKNCcb10EiTQxH8YRGAOPzBnNMgYsJk771c+vbLAfuhIdh
SOqa6MMz1zITsMdEAUGz1TmvqbaIZdYmwxvTmLSASfpffiLTnjraYffc53zWab+W
MHpjbENnI1OIexgOPqspFMYiKctzhlaxqF7wJMrsCDimpGOMM3rWE+pzk+3LMfUW
RyH5WtG/H0DUjTwYV0ATpFI22WlgGk0AQKd76ooufh4GWvA1Obrh60CVWyyrs2z/
8RTdx+62SsS7Vn9tdaChuzS08T38p5yk7Cj4+sS30oK8v30UG5FzQFgG6kGCb+cT
ETzCaPyc49Xe96ajvsl4DRA=
-----END CERTIFICATE-----


)EOF";

const char ENDPOINT_CA_KEY[] PROGMEM = R"EOF(
-----BEGIN PRIVATE KEY-----
MIIEvQIBADANBgkqhkiG9w0BAQEFAASCBKcwggSjAgEAAoIBAQCkg/Or74C1XWdG
oIN19R9KmTF5HiVsNs8qkynBgGSZBw51TI3IkYva0l7ModfXDsCW7tkFhSWs6K39
AGfuNYAxwwlvngIwvJRhGosKWf10NCSRUHyc/o5strJR7ZKqYJjrwEtWtkS8vV7z
8sEFMPT7AMeq32ZuyQmwWdGCjXFZGpZDPsqytXXG2iKQuxIgMcB/NSd7trAsV9Q+
XK0FfeAzLGU10/wkpBktAlsaf76tcM2qjzcZTxs03HN2dSkAredSxBqjORGyKXv2
iqdHHoP9WVkb8nPHA/9A/tiwrKni6xL5BB3Pc3irv/jQSlt8tkoz5gqyWGWpr3jx
T9czMG75AgMBAAECggEACCCOWdDKsM+PJ4vn28pZyKuAcXVygdQxncoafYtkWo7z
HJ0y1HmR7dq+XQS26okCdlbsT7KACmaN9UNDuoxqWUHVwaSN8JNHNBjYBCOcg+c6
ZGCB8uAX3fmUi5dLFI0R8yuKBBvlSI0XhVOilSk2aiP2JuZn0S4dlWrTozmSbOnx
MMjGKoCpBWqZxOsENI/yhXIoMQQefC8Hv/Yxl4WsNwjCSrEhUUwmSBij/Cyji+Qa
7v8MpieHqvN4vXFA9+FiCvqD2DLPmilkomkzZOQE1ed7SytFxby/Mfu5Q7Hvp1h2
qMwsuHC6BUrTWlo9wOlIXl2KclJqtv6YAb4TaisapQKBgQDPRu3nlL88Lu0TGhvt
3uoj7KiOv9hp/1IJMdnwV6O2htAqj3c9s0X6MjeEMcp2zZDv389fFZJLdkFASX7L
syUATTB6kZnm0gb5tO5QFpiyFYc1UlHyYi8682AFXiyOnez0ZWBJs1drwrFFDOeB
CTUXxcWijTxhop3yD2jStu/o0wKBgQDLL85A5Y1kHdupSM+aTu+NmMmUBWQ/5Nt2
EfLRGiAgyLFLsZRl9jdaTD4EjywdE9RY2nDYbX+lj7SskZNp1Kydbxq9Hz/SqAc4
/rfFcSjMAPxZMEYNWY/YIzuvGNGaDjWX63H2D90BVJ5HdHWnFnfphSTCY0glZa52
Gpzhj8OpgwKBgQCCKoTUXXEKll2DFW5cnxRiowfnPUrmpdQauhem+yJwSZEIaTf0
o1RanpaGic4fdVCDkwVjLOTGRukLOhxKR6IA4niDQFRpw5Nl1N2jpc0WaLaUIbIc
iNQoLRYryMwqc7qOb+tb3SgVIBq6xjPLsMCKwUQvpIo6tiiCDnNBgGiAyQKBgHJ1
TaS1Kz74quLjxz7PtJZ5OSSPHPf5Pb93QOeV5f9Rzr4rHMOLPYc6Z709wcXng7lB
5Eum8z8agtarcvUs/sf47IEY92T9joQGyRMKOcchzwWW8f9XMna48kginQBBfONF
mH7aVM8JEdiCvDwRph8AB8MRFnUqoGqbd0CBMeFtAoGAF1L5Dpy+sdfO5t2DQE2B
YVJ3A6ZT6F1HvFvfcf5eAcjXO6jXVKVZ4cTPTeEymO9t58QPBL1rhFRoRyV/62fV
YAEIpeB/htLv0WM7CJZQDulafsLYn9FcEDf1CozG0vTKAH8nf0viKrdEJobnMt17
5OOt4KE+AfcR2tOCjRutGYg=
-----END PRIVATE KEY-----



)EOF";

//definice velikosti EEPROM
#define EEPROM_SIZE 512

char *ssid = "placeholder";
char *password = "placeholder";

//deklarce webserveru a websocketu
AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

struct Color {
  int r;
  int g;
  int b;
};

int steps = 200;
int pressTime = 0;
bool req = false;
bool activeSession = false;
bool interuptFlag = false;
bool requestAmbientFlag = false;
long cntr;
long interuptTimestamp;
String message;
int discCounter;

float rStep, gStep, bStep;
int stepDuration = 0, Gsteps = 0, smoothIndex = 0;
long stepTimeStamp;
bool smoothFlag = false;
Color z;

int lastSmoothGradient = 0, smoothGradientIndex = 0, smoothGradientSteps = 0, smoothGradientDuration = 0;
float smoothRStepX, smoothGStepX, smoothBStepX;
float smoothRStepY, smoothGStepY, smoothBStepY;
bool smoothGradientFlag = false;
Color currX, currY;

int nightRiderCount;
int nightRiderState;
int nightRiderDuration;
int nightRiderTimeStamp;
Color nightRiderColor;

enum APISources {
  FOREST,
  CUSTOMWS,
  MQTT,
  OFF
};

enum APISources APISource;

String readSSID();
String readPassword();
int readMode();
int readBrightness();
void changeMode(int mode);
void setStatusLed(int r, int g, int b);
void checkButton();
void smoothGradient(Color beginX, Color beginY, Color endX, Color endY, int steps, int duration);
Color getClrFromStr(String str);



Color currColor;
Color trgColor;


WebSocketsClient webSocket;
String messageFromAPI;

WiFiClient mqttespClient;
PubSubClient mqttclient(mqttespClient);

void webSocketEvent(WStype_t type, uint8_t *payload, size_t length) {
  switch (type) {
    case WStype_DISCONNECTED:
      Serial.printf("[WSc] Disconnected!\n");
      WebSerial.printf("[WSc] Disconnected!\n");
      if (readMode() == 1) {
        setStatusLed(255, 0, 0);
        nightRider.attach_ms(200, advanceNightRider);
      }
      activeSession = false;
      break;
    case WStype_CONNECTED:
      {
        Serial.printf("[WSc] Connected to url: %s\n", payload);
        WebSerial.printf("[WSc] Connected to url: %s\n", payload);
      }
      break;
    case WStype_TEXT:
      {

        
        messageFromAPI = (char *)payload;
        webSocket.loop();
        if (messageFromAPI.equals("Connection established")) { activeSession = true; }

        if (messageFromAPI == "") { return; }
        
        processAPIMessage();
        /*Serial.println(messageFromAPI);
        WebSerial.println(messageFromAPI);
        while (!procesData(messageFromAPI)) {
          Serial.println("Could not show, looping");
          WebSerial.println("Could not show, looping");
        }
        messageFromAPI = "";*/
        // send message to server
        // webSocket.sendTXT("message here");
        break;
      }
    case WStype_BIN:
      Serial.printf("[WSc] get binary length: %u\n", length);
      WebSerial.printf("[WSc] get binary length: %u\n", length);
      hexdump(payload, length);

      // send data to server
      // webSocket.sendBIN(payload, length);
      break;
  }
}

void initWebSocket() {
  ws.onEvent(onEvent);
  server.addHandler(&ws);
}

String processor(const String &var) {
  return String();
}

void sendAlert(String txt) {
  ws.textAll(txt);
}

void callback(char* topic, byte* payload, unsigned int length) {
  String message;
  for (int i = 0; i < length; i++) {
    message += (char)payload[i];
  }
  messageFromAPI = message;
}


//funkce pro zpracování requestu z webserveru
void handleWebSocketMessage(void *arg, uint8_t *data, size_t len) {
  AwsFrameInfo *info = (AwsFrameInfo *)arg;
  if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {
    data[len] = 0;
    Serial.println((char *)data);
    WebSerial.println((char *)data);
    message = (char *)data;
    //nastavení příznaku na true
    req = true;
    //seznam API
    //ip api https://api.ipify.org
    //loc api https://ipapi.co/latlong
    //weather api https://api.tomorrow.io/v4/timelines?location=49.403100,15.592400&fields=temperature&timesteps=1d&units=metric&apikey=QPogenzy0SYMfu4yF6zWcnPRRw0kicAC
  }
}


String getWebData() {
  Color c = getClrFromStr(readGradintColor1());
  Color c2 = getClrFromStr(readGradintColor2());
  String strr = ("init:" + readSSID() + "," + readPassword() + "," + readMode() + "," + readBrightness() + "," + readRed() + "," + readGreen() + "," + readBlue() + "," + readSpeed1() + "," + readSpeed2() + "," + readManualBrighness() + "," + String(readTime1Hours()) + ":" + String(readTime1Minutes()) + "," + String(readTime2Hours()) + ":" + String(readTime2Minutes()) + "," + readURL() + "," + String(readBeepSetting()) + "," + String(readAPIDataSource()) + "," + String(readButtonMode())  + ","
  + String(c.r) +  "," + String(c.g) +  "," +String(c.b) +  "," +String(c2.r) +  "," +String(c2.g) +  "," +String(c2.b) + "," + String(readWiFiMode()) + "," + String(readWifiTouch()) + "," + String(readOverride())
  );
  return strr;
}

String getGameData() {
  Color c = getClrFromStr(readGradintColor1());
  Color c2 = getClrFromStr(readGradintColor2());
  String strr = (String(readMode()) + "," + readBrightness() + "," + readRed() + "," + readGreen() + "," + readBlue() + "," + readSpeed1() + "," + readSpeed2() + "," + readManualBrighness() + "," + String(readTime1Hours()) + ":" + String(readTime1Minutes()) + "," + String(readTime2Hours()) + ":" + String(readTime2Minutes()) + "," + readURL() + "," + String(readBeepSetting()) + "," + String(readAPIDataSource()) + "," + String(readButtonMode()) + "," + String(WiFi.localIP().toString())
  +","+String(c.r) +  "," + String(c.g) +  "," +String(c.b) +  "," +String(c2.r) +  "," +String(c2.g) +  "," +String(c2.b) + "," + String(readWifiTouch()) + "," + String(readOverride()));
  return strr;
}

void setData(String str) {

  StringSplitter *splitter = new StringSplitter(str.c_str(),',',25);
  writeMode(atoi(splitter->getItemAtIndex(0).c_str()));
  writeBrightness(atoi(splitter->getItemAtIndex(1).c_str()));
  writeRGB(atoi(splitter->getItemAtIndex(2).c_str()),atoi(splitter->getItemAtIndex(3).c_str()),atoi(splitter->getItemAtIndex(4).c_str()));
  writeSpeed1(atoi(splitter->getItemAtIndex(5).c_str()));
  writeSpeed2(atoi(splitter->getItemAtIndex(6).c_str()));
  writeManualBrighness(atoi(splitter->getItemAtIndex(7).c_str()));
  writeTime1(atoi(splitter->getItemAtIndex(8).c_str()), atoi(splitter->getItemAtIndex(9).c_str()));
  writeTime2(atoi(splitter->getItemAtIndex(10).c_str()), atoi(splitter->getItemAtIndex(11).c_str()));
  writeURL(splitter->getItemAtIndex(12));
  setBeepSetting(atoi(splitter->getItemAtIndex(13).c_str()));
  setAPIDataSource(atoi(splitter->getItemAtIndex(14).c_str()));
  setButtonMode(atoi(splitter->getItemAtIndex(15).c_str()));
  writeGradientData1(atoi(splitter->getItemAtIndex(16).c_str()),atoi(splitter->getItemAtIndex(17).c_str()),atoi(splitter->getItemAtIndex(18).c_str()));
  writeGradientData2(atoi(splitter->getItemAtIndex(19).c_str()),atoi(splitter->getItemAtIndex(20).c_str()),atoi(splitter->getItemAtIndex(21).c_str()));
  writeWifiTouch(atoi(splitter->getItemAtIndex(22).c_str()));
  writeOverride(atoi(splitter->getItemAtIndex(23).c_str()));
  delete splitter;
}

//funkce pro zpracovávání eventů z webserveru
void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len) {
  switch (type) {
    case WS_EVT_CONNECT:
      {
        Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
        WebSerial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
        //String strr = ("init:" + readSSID() + "," + readPassword() + "," + readMode() + "," + readBrightness() + "," + readRed() + "," + readGreen() + "," + readBlue() + "," + readSpeed1() + "," + readSpeed2() + "," + readManualBrighness() + "," + String(readTime1Hours()) + ":" + String(readTime1Minutes()) + "," + String(readTime2Hours()) + ":" + String(readTime2Minutes()) + "," + readURL() + "," + String(readBeepSetting()) + "," + String(readAPIDataSource()));
        sendAlert(getWebData());
        break;
      }
    case WS_EVT_DISCONNECT:
      Serial.printf("WebSocket client #%u disconnected\n", client->id());
      break;
    case WS_EVT_DATA:
      handleWebSocketMessage(arg, data, len);
      break;
    case WS_EVT_PONG:
    case WS_EVT_ERROR:
      break;
  }
}




void setup() {
  Serial.begin(115200);
  Serial.println("Initial Memory:");
  Serial.println(ESP.getFreeHeap(), DEC);
  statusLed.begin();
  statusLed.setBrightness(255);
  statusLed.show();
  strip.begin();
  strip.setBrightness(255);
  strip.show();
  pinMode(D1, INPUT);
  attachInterrupt(digitalPinToInterrupt(D1), checkButton, CHANGE);
  nightRiderColor = {0,255,0};
  nightRider.attach_ms(200, advanceNightRider);
  delay(100);
  EEPROM.begin(EEPROM_SIZE);

  delay(500);
  WiFi.setPhyMode(WIFI_PHY_MODE_11B);
  APISource = (enum APISources)readAPIDataSource();
  if (readWiFiMode()) {
    setStatusLed(0, 255, 0);
    WiFi.begin(readSSID(), readPassword());
    Serial.println("ssid:" + readSSID() + ", passwd:" + readPassword() + ",");
    while ((int)millis() < 60 * 1000) {

      if (WiFi.status() == WL_CONNECTED) {
        break;
      }
      delay(100);
    }

    if(WiFi.status() == WL_CONNECTED) {
      String res = apiCall("https://forestcraft.cz/lamp/latestVersion");
      if(res != "") {
      int serverVersion = atoi(res.c_str());
      if(serverVersion > currentVersion) {
      WiFiClient client;
      String id = LAMP_ID;
      deobfuscateString(id);
      String str = "/lamp/update/"+ id +"/update.bin";
      ESPhttpUpdate.update(client, "https://forestcraft.cz", 80, str);} 
      }      
    }

    else {
      APISource = OFF;
      WiFi.softAP("ForestGlow", "12345678");
      setStatusLed(0, 0, 255);
    }
  }

  else {  //Standalone mode
    APISource = OFF;
    WiFi.softAP("ForestGlow", "12345678");
    setStatusLed(0, 0, 255);
  }

  Serial.println(WiFi.localIP());

  initWebSocket();

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send_P(200, "text/html", index_html, processor);
  });
  AsyncElegantOTA.begin(&server);
  WebSerial.begin(&server);
  server.begin();

  pinMode(D5, INPUT);

  delay(2000);
  setStatusLed(0, 0, 0);
  delay(500);
  switch (APISource) {
    case 0:
      {
        setupWS("forestcraft.cz");
        setStatusLed(255, 255, 255);
        break;
      }
    case 1:
      {
        setupWS(readURL());
        setStatusLed(0, 255, 0);
        break;
      }
    case 2:
      {
        String url = readURL();
        mqttclient.setServer(url.c_str(), 1883);
        mqttclient.setCallback(callback);
        setStatusLed(0, 0, 255);
        mqttReconnect();       
        break;
      }
    case 3:
      {
        setStatusLed(255, 0, 0);
        break;
      }
    default:
      {
        Serial.println("error");
        break;
      }
  }
  delay(2000);
  setStatusLed(0, 0, 0);
  delay(500);


  changeMode(readMode());
  Serial.println("Setup end memory:");
  Serial.println(ESP.getFreeHeap(), DEC);
  WebSerial.println("Setup end memory:");
  WebSerial.println(ESP.getFreeHeap(), DEC);
  nightRider.detach();
  nightRiderColor = {255,0,0};
}


void mqttReconnect() {
   mqttclient.loop();
    String id = LAMP_ID;
    deobfuscateString(id);
    if (mqttclient.connect(String("Lamp" + id).c_str())) {
    mqttclient.subscribe("message");
    }
}


//funce pro přečtení SSID z paměti EEPROM
String readSSID() {
  int n;
  n = EEPROM.read(100);
  if (n == 255) { return "ForestGlow"; }
  String str = "";
  for (int i = 0; i < n; i++) {
    if (EEPROM.read(101 + i) == 255) { continue; }
    str += char(EEPROM.read(101 + i));
  }
  if (str != "") { strcpy(ssid, str.c_str()); }
  return str;
}
//funce pro přečtení hesla z paměti EEPROM
String readPassword() {
  int k = 0;
  k = EEPROM.read(165);
  if (k == 255) { return "12345678"; }
  String str2 = "";
  for (int i = 0; i < k; i++) {
    if (EEPROM.read(166 + i) == 255) { continue; }
    str2 += char(EEPROM.read(166 + i));
  }
  if (str2 != "") { strcpy(password, str2.c_str()); }
  return str2;
}

void setBrightness() {
  //check wifi mode
  switch (readBrightness()) {
    case 0:
      {
        int currentTime = getCurrentTime();
        int sunsetTime = getSunsetTime();
        int sunriseTime = getSunriseTime();
        strip.setBrightness(255);
        statusLed.setBrightness(255);       
        if(sunsetTime < currentTime) {
          
          strip.setBrightness(64);
          statusLed.setBrightness(64);       
        }
        if(sunriseTime < currentTime) {
         
          strip.setBrightness(255);
          statusLed.setBrightness(255);       
        }

        break;
      }  //api sun set/rise
    case 1:
      {
        int timeToLower = readTime1Hours() * 3600 + readTime1Minutes() * 60;
        int timeToHigher = readTime2Hours() * 3600 + readTime2Minutes() * 60;

        int convertedTime = getCurrentTime();
          strip.setBrightness(255);
          statusLed.setBrightness(255);       
        if(timeToLower < convertedTime) {
          
          strip.setBrightness(64);
          statusLed.setBrightness(64);       
        }
        if(timeToHigher < convertedTime) {
         
          strip.setBrightness(255);
          statusLed.setBrightness(255);       
        }
    
        break;
      }  // custom time
    case 2:
      {
        strip.setBrightness(getBrightnessFromSensor());
        statusLed.setBrightness(getBrightnessFromSensor());
        Serial.println("Brightness:" + String(getBrightnessFromSensor()));
        Serial.println("BrightnessData:" + String(analogRead(A0)));
        break;
      }  //sensor
    case 3:
      {
        strip.setBrightness(readManualBrighness());
        statusLed.setBrightness(readManualBrighness());
        break;
      }  //manual
    default:
      {
        strip.setBrightness(255);
        statusLed.setBrightness(255);
      }
  }
  strip.show();
  statusLed.show();
  //
}


void loop() {


  if (req) {
    Serial.println(message);
    WebSerial.println(message);

    
    if (message.startsWith("wifi:")) {
      message.replace("wifi:", "");
      writeWiFiEEPROM(message);
      sendAlert("alert:Nastavení Wi-Fi sítě úspěšně změněno!");
    } 
    
    else if (message.startsWith("mode:")) {
      sendAlert("alert:Nastavení módu úspěšně změněno!");
      message.replace("mode:", "");
      int i = atoi(&message[0]);
      message.remove(0, 2);
      switch (i) {
        case 3:
          {
            Color c = getClrFromStr(message);
            writeRGB(c.r, c.g, c.b);
            break;
          }
        case 4:
          {
            message.replace("speed:", "");
            Serial.println(message.c_str());
            writeSpeed1(atoi(message.c_str()));
            break;
          }
        case 5:
          {
            message.replace("speed:", "");
            Serial.println(message.c_str());
            writeSpeed2(atoi(message.c_str()));
            break;
          }
        case 6: {
            StringSplitter *split = new StringSplitter(message.c_str(),':',3);
            Color c = getClrFromStr(split->getItemAtIndex(0).c_str());
            writeGradientData1(c.r, c.g, c.b);
            c = getClrFromStr(split->getItemAtIndex(1).c_str());
            writeGradientData2(c.r, c.g, c.b);
            delete split;
          
            break;}
      }

      changeMode(i);
    } 
    
    
    else if (message.startsWith("brightness:")) {
      sendAlert("alert:Nastavení jasu úspěšně změněno!");
      message.replace("brightness:", "");
      writeBrightness(atoi(&message[0]));
      int i = atoi(&message[0]);
      message.remove(0, 2);
      if (i == 3) {
        writeManualBrighness(atoi(message.c_str()));
      }
      if (i == 1) {
        StringSplitter *splitter = new StringSplitter(message.c_str(), ':', 5);
        writeTime1(atoi(splitter->getItemAtIndex(0).c_str()), atoi(splitter->getItemAtIndex(1).c_str()));
        writeTime2(atoi(splitter->getItemAtIndex(2).c_str()), atoi(splitter->getItemAtIndex(3).c_str()));
        delete splitter;
      }
      setBrightness();
    } 
    
    else if (message.startsWith("apiSource:")) {
      sendAlert("alert:Nastavení zdroje dat úspěšně změněno!");
      message.replace("apiSource:", "");
      setAPIDataSource(atoi(message.c_str()));
      Serial.printf("APISource is:%d", readAPIDataSource());
    } 
    
    else if (message.startsWith("beep:")) {
      message.replace("beep:", "");
      setBeepSetting(atoi(message.c_str()));
    } 
    
    else if (message.startsWith("button:")) {
      message.replace("button:", "");
      setButtonMode(atoi(message.c_str()));
    } 
    
    else if (message.startsWith("customURL")) {
      message.replace("customURL:", "");
      Serial.println(message);
      writeURL(message);
    }

    else if (message.startsWith("touch-wifi:")) {
      message.replace("touch-wifi:", "");
      Serial.println(message);
      writeWifiTouch(atoi(message.c_str()));
    }

    else if (message.startsWith("override:")) {
      message.replace("override:", "");
      Serial.println(message);
      writeOverride(atoi(message.c_str()));
    }

    else if(message.startsWith("reset")) {
    sendAlert("alert:Lampička se restaruje. Její připojení může chvíli trvat!");      
      Serial.println("reseting");
      ESP.restart();
    }

    else if(message.startsWith("wifiMode")) {
      sendAlert("alert:Nastavení Wi-Fi módu úspěšně změněno!");
      message.replace("wifiMode:", "");
      setWiFiMode(atoi(message.c_str()));
    }

    String str = getGameData();
    str = "readout;" + str;
    webSocket.sendTXT(str.c_str());
    req = false;
  }



  if (cntr % 10000 == 0) {
    setBrightness();
  }
  /*if (cntr % 1000 == 0) {
    
    pinMode(D5, INPUT);
  }*/
  
  if (cntr % 5000 == 0) {
    ws.cleanupClients();
  }

  if (webSocket.isConnected() && readMode() == 1 && nightRider.active()) {
    setStatusLed(0, 0, 0);
    nightRider.detach();
  }

  if (cntr % 10000 == 0) {
    if (APISource == FOREST || APISource == CUSTOMWS) {
      if (!activeSession) {
        inicializeConection();
        if (readMode() == 1) {
          setStatusLed(255, 0, 0);
          nightRider.attach_ms(200, advanceNightRider);
          goto skip;
        } 
      }
    }
    setStatusLed(0, 0, 0);
  }
  skip:
  if (millis() > interuptTimestamp && interuptFlag) {
    interuptFlag = false;
    if(requestAmbientFlag) {webSocket.sendTXT("done");}
    requestAmbientFlag = false;
  }

  if (smoothFlag && (stepTimeStamp + ((long)stepDuration)) < millis()) {
    stepTimeStamp = millis();
    advanceSmooth();
    if (smoothIndex == Gsteps) {
      smoothFlag = false;
      if (readMode() == 1) { webSocket.sendTXT("done"); }
    }
  }

  if (smoothGradientFlag && lastSmoothGradient + smoothGradientDuration < millis()) {
    lastSmoothGradient = millis();
    advenceSmoothGradient();
    if (smoothGradientIndex + 1 == smoothGradientSteps) {
      smoothGradientFlag = false;
      if (readMode() == 1) { webSocket.sendTXT("done"); }
    }
  }

  cntr = millis();

  runMode();
  if(readMode() != 1 && readOverride() && interuptFlag) {
    processAPIMessage();
  }
  webSocket.loop();

  //Serial.println(digitalRead(D6);
}

ICACHE_RAM_ATTR void checkButton() {
  if (!readButtonMode()) { return; }
  if (digitalRead(D1)) {
    pressTime = millis();
    return;
  }
  pressTime = millis() - pressTime;
  if (pressTime > 5000 && readWifiTouch()) {
    setWiFiMode(!readWiFiMode());
    if (readBeepSetting()) {
      pinMode(D5, OUTPUT);
      tone(D5, 783, 1000);
    }
    tone(D5, 1600, 200);
    delay(1000);
    tone(D5, 1600, 200);
    ESP.restart();
    return;
  }
  if (pressTime > 1500) {
    changeMode(0);
    if (readBeepSetting()) {
      pinMode(D5, OUTPUT);
      tone(D5, 783, 300);
      toneTimer.once_ms(300,nobeep);
    }
    return;
  }
  int mode = readMode() + 1;
  if (mode > 6) { mode = 0; }
  if (readBeepSetting()) {
    pinMode(D5, OUTPUT);
    tone(D5, 783, 100);
    toneTimer.once_ms(100,nobeep);
    
  }
  changeMode(mode);
}


HTTPClient http;
WiFiClientSecure wifiClient;

void setupConnection(String url) {
  if ((WiFi.status() == WL_CONNECTED)) {
    //wifiClient.setInsecure();
    //připojení na zadanou URL
    wifiClient.connect(url, 80);
    wifiClient.setInsecure();
    //wifiClient.setFingerprint(fingerprint);
    Serial.println(wifiClient.connected());
    //spištění http requestu
    http.begin(wifiClient, url);
    http.setReuse(true);
    http.setTimeout(5000);

  } else {
    Serial.println("Idk error");
  }
}

//funkce pro zavolíní API
String callSettedAPI() {
  int httpCode = http.GET();

  //zkotrolováníhttp kódu
  if (httpCode > 0) {
    //uložení výsledu http requstu do proměné
    String payload = http.getString();
    return payload;
  }

  else {
    Serial.println(httpCode);
    Serial.println("Error on HTTP request");
    return "";
  }
}

Color getClrFromStr(String str) {
  StringSplitter *splitter = new StringSplitter(str.c_str(), ',', 3);
  Color c;
  c.r = atoi(splitter->getItemAtIndex(0).c_str());
  c.g = atoi(splitter->getItemAtIndex(1).c_str());
  c.b = atoi(splitter->getItemAtIndex(2).c_str());
  delete splitter;
  return c;
}

void nobeep() {
  noTone(D5);
  pinMode(D5, INPUT);
}

bool procesData(String result) {

  if (result.startsWith("readout")) {
    String str = getGameData();
    str = "readout;" + str;
    webSocket.sendTXT(str.c_str());
    return true;
  }

  if (result.startsWith("request:")) {
    if (req != false) { return false; }
    result.replace("request:", "");
    req = true;
    message = result;
    return true;
  }

  if(result.startsWith("setting:")) {
    result.replace("setting:", "");
    setData(result);    
    return true;
  }

  if(readOverride() && readMode() != 1) {
    if(messageFromAPI.indexOf("interrupt:") == -1) {
        return true;
    }            
  }

  if (!result.startsWith("update:")) { return true; }
  result.replace("update:", "");
  if (!strip.canShow()) { return false; }
  StringSplitter *splitterg = new StringSplitter(result.c_str(), ';', 10);
  for (int i = 0; i < splitterg->getItemCount(); i++) {

    String str = splitterg->getItemAtIndex(i);
    if(str.length()<2) {continue;}
    if (!(str.startsWith("beep") || str.startsWith("interrupt"))) {
      smoothFlag = false;
      smoothGradientFlag = false;
    }

    if (str.startsWith("FILL:")) {
      str.replace("FILL:", "");
      fill(getClrFromStr(str));
      continue;
    }

    if (str.startsWith("beep:") && readBeepSetting()) {
      str.replace("beep:", "");
      StringSplitter *splitter = new StringSplitter(str.c_str(), ':', 3);
      pinMode(D5, OUTPUT);
      tone(D5, atoi(splitter->getItemAtIndex(0).c_str()));
      toneTimer.once_ms(atoi(splitter->getItemAtIndex(1).c_str()),nobeep);
      delete splitter;
      continue;
    }

    if (str.startsWith("interrupt:")) {
      str.replace("interrupt:", "");
      interuptTimestamp = millis() + str.toInt();
      interuptFlag = true;
      if(readMode() == 1) {requestAmbientFlag = true;}
      continue;
    }
    //LEDsmoothGradient
    if (str.startsWith("SMOOTH_GRADIENT:")) {
      str.replace("SMOOTH_GRADIENT:", "");
      StringSplitter *splitter = new StringSplitter(str.c_str(), ':', 7);
      smoothGradient(getClrFromStr(splitter->getItemAtIndex(0)), getClrFromStr(splitter->getItemAtIndex(1)), getClrFromStr(splitter->getItemAtIndex(2)), getClrFromStr(splitter->getItemAtIndex(3)), atoi(splitter->getItemAtIndex(4).c_str()));
      delete splitter;
      continue;
    }
    //LEDsmooth:0
    if (str.startsWith("SMOOTH:")) {
      str.replace("SMOOTH:", "");
      StringSplitter *splitter = new StringSplitter(str.c_str(), ':', 5);
      smoothSet(getClrFromStr(splitter->getItemAtIndex(0)), getClrFromStr(splitter->getItemAtIndex(1)), atoi(splitter->getItemAtIndex(2).c_str()), true);
      delete splitter;
      continue;
    }

    //LEDgradient:0
    if (str.startsWith("GRADIENT:")) {
      str.replace("GRADIENT:", "");
      StringSplitter *splitter = new StringSplitter(str.c_str(), ':', 3);
      gradient(getClrFromStr(splitter->getItemAtIndex(0)), getClrFromStr(splitter->getItemAtIndex(1)), LEDCount);
      delete splitter;
      continue;
    }

    if (str.startsWith("SMOOTH_PREV:")) {
      str.replace("SMOOTH_PREV:", "");
      StringSplitter *splitter = new StringSplitter(str.c_str(), ':', 5);
      uint32_t color = strip.getPixelColor(0);
      Color c = {(color >> 16) & 0xFF,(color >> 8) & 0xFF,(color >> 0) & 0xFF};
      smoothSet(c, getClrFromStr(splitter->getItemAtIndex(0)), atoi(splitter->getItemAtIndex(1).c_str()),true);
  
      delete splitter;
      continue;
    }


    if (str.startsWith("GRADIENT_PREV:")) {
      str.replace("GRADIENT_PREV:", "");
      StringSplitter *splitter = new StringSplitter(str.c_str(), ':', 3);
      uint32_t color = strip.getPixelColor(0);
      Color c = {(color >> 16) & 0xFF,(color >> 8) & 0xFF,(color >> 0) & 0xFF};
      Serial.printf("r:%d,g:%d,b:%d\n",c.r,c.g,c.b);
      gradient(getClrFromStr(splitter->getItemAtIndex(0)), c, LEDCount);
      delete splitter;
      continue;
    }

    if (str.startsWith("SMOOTH_GRADIENT_PREV:")) {
      str.replace("SMOOTH_GRADIENT_PREV:", "");
      StringSplitter *splitter = new StringSplitter(str.c_str(), ':', 5);
      uint32_t color = strip.getPixelColor(0);
      uint32_t color2 = strip.getPixelColor(14);
      Color c = {(color >> 16) & 0xFF,(color >> 8) & 0xFF,(color >> 0) & 0xFF};
      Color c2 = {(color2 >> 16) & 0xFF,(color2 >> 8) & 0xFF,(color2 >> 0) & 0xFF};
      smoothGradient(c, c2,getClrFromStr(splitter->getItemAtIndex(0)), getClrFromStr(splitter->getItemAtIndex(1)), atoi(splitter->getItemAtIndex(2).c_str()));
  
      delete splitter;
      continue;
    }
  }
  delete splitterg;
  return true;
}
void setStatusLed(int r, int g, int b) {
  statusLed.setPixelColor(0, statusLed.Color(r, g, b));
  statusLed.show();
}

void deobfuscateString(String &str) {
  int len = str.length();
  for (int i = 0; i < len; i++) {
    str[i] = str.charAt(i) ^ 69;
  }
}


void changeMode(int mode) {

  if (mode != 1) { nightRider.detach(); setStatusLed(0, 0, 0);}
  writeMode(mode);
  if (mode == 0) { off(); }
  if (mode == 1) {
    off();
    if (APISource == OFF) {
      changeMode(2);
      return;
    }
  }
  if (mode == 2) {
    white();
  }
  if (mode == 3) {
    rgb();
  }
  if (mode == 4) {
    int rgbLastUpdate = millis();
    smoothSet({ 255, 0, 0 }, { 0, 255, 0 }, abs(256 - readSpeed1()), false);
  }
  if (mode == 5) {
    int ambiLastUpdate = millis();
    currColor = { random(256), random(256), random(256) };
    trgColor = { random(256), random(256), random(256) };
    smoothSet(currColor, trgColor, abs(256 - readSpeed2()), false);
  }
  String str = getGameData();
  str = "readout;" + str;
  webSocket.sendTXT(str.c_str());
}

void processAPIMessage() {
  switch (APISource) {
          case FOREST:
          case CUSTOMWS:
            {
              webSocket.loop();
              if (messageFromAPI == "") { return; }
              Serial.println(messageFromAPI);
              WebSerial.println(messageFromAPI);

              

              while (!procesData(messageFromAPI)) {}
              messageFromAPI = "";
              break;
            }
          case MQTT:
            {
              if(!mqttclient.connected()) {mqttReconnect();}
              mqttclient.loop();
              if (messageFromAPI == "") { return; }
              Serial.println(messageFromAPI);
              WebSerial.println(messageFromAPI);

              if(readOverride() && readMode() != 1) {
                if(messageFromAPI.indexOf("interrupt:") != 1) {
                  return;
                }
              }
              
              while (!procesData(messageFromAPI)) {
              }
              messageFromAPI = "";
              break;
            }

          case OFF:
            {
              changeMode(2);
              Serial.println("is offf");
              break;
            }
        }
}


void runMode() {
  if(interuptFlag) {return;}
  switch (readMode()) {
    case 1:
      {
        processAPIMessage();
        break;
      }
    case 2:
      {
        if (cntr % 200 == 0) {
          white();
        }
        break;
      }
    case 3:
      {

        if (cntr % 200 == 0) {
          rgb();
        }
        break;
      }
    case 4:
      {
        rgbFade();
        break;
      }
    case 5:
      {
        ambient();
        break;
      }
      case 6:
      {
        if (cntr % 200 == 0) {
        gradient(getClrFromStr(readGradintColor1()),getClrFromStr(readGradintColor2()),LEDCount);
        }
        break;

      }
    case 0:
      {
        if (cntr % 200 == 0) {
          off();
        }
        break;
      }
  }
}

void white() {
  strip.fill(strip.Color(255, 255, 255), 0);
  strip.show();
}

void rgb() {
  strip.fill(strip.Color(readRed(), readGreen(), readBlue()), 0);
  strip.show();
}

void off() {
  strip.fill(strip.Color(0, 0, 0), 0);
  strip.show();
}

long rgbLastUpdate = 0;
int rgbFadeState = 0;

void rgbFade() {
  if (rgbLastUpdate + abs(256 - readSpeed1()) < millis()) {
    advanceSmooth();
    rgbLastUpdate = millis();
    if (smoothIndex == 255) {
      smoothIndex = 0;
      switch (++rgbFadeState % 3) {
        case 0:
          {
            smoothSet({ 255, 0, 0 }, { 0, 255, 0 }, abs(256 - readSpeed1()), false);
            break;
          }
        case 1:
          {
            smoothSet({ 0, 255, 0 }, { 0, 0, 255 }, abs(256 - readSpeed1()), false);
            break;
          }
        case 2:
          {
            smoothSet({ 0, 0, 255 }, { 255, 0, 0 }, abs(256 - readSpeed1()), false);
            break;
          }
      }
    }
  }
}

void fill(Color c) {
  strip.fill(strip.Color(c.r, c.g, c.b), 0);
  strip.show();
}


long ambiLastUpdate = 0;
void ambient() {
  if (ambiLastUpdate + abs(256 - readSpeed2()) < millis()) {
    advanceSmooth();
    ambiLastUpdate = millis();
    if (smoothIndex == 255) {
      currColor = trgColor;
      trgColor = { random(256), random(256), random(256) };
      smoothIndex = 0;
      smoothSet(currColor, trgColor,abs(256 - readSpeed2()), false);
    }
  }
}

void smoothSet(Color x, Color y, int d, bool autoProgress) {
  if(d == 0) {fill(y);return;}
  int steps = 255;
  int duration = d/steps;
  Serial.printf("parsed to smootrh %d,%d,%d",d,steps,duration);
  rStep = (float)(x.r - y.r) / (float)(steps - 1);
  gStep = (float)(x.g - y.g) / (float)(steps - 1);
  bStep = (float)(x.b - y.b) / (float)(steps - 1);
  stepDuration = duration;
  Gsteps = steps;
  stepTimeStamp = millis();
  smoothIndex = 0;
  smoothFlag = autoProgress;
  z = x;
}

void advanceSmooth() {
  strip.fill(strip.Color((int)(z.r - (rStep * smoothIndex)), (int)(z.g - (gStep * smoothIndex)), (int)(z.b - (bStep * smoothIndex++))), 0);
  strip.show();
}

void gradient(Color x, Color y, int n) {
  float rStep = (float)(x.r - y.r) / (float)(n - 1);
  float gStep = (float)(x.g - y.g) / (float)(n - 1);
  float bStep = (float)(x.b - y.b) / (float)(n - 1);
  for (int i = 0; i < n; i++) {
    strip.setPixelColor(i, (int)(x.r - (rStep * i)), (int)(x.g - (gStep * i)), (int)(x.b - (bStep * i)));
  }
  strip.show();
  
}


void smoothGradient(Color beginX, Color beginY, Color endX, Color endY, int d) {
  if(d == 0) {gradient(endX, endY, LEDCount);return;}
  int steps = 255;
  int duration = d/steps;
  smoothRStepX = (float)(beginX.r - endX.r) / (float)(steps - 1);
  smoothGStepX = (float)(beginX.g - endX.g) / (float)(steps - 1);
  smoothBStepX = (float)(beginX.b - endX.b) / (float)(steps - 1);

  smoothRStepY = (float)(beginY.r - endY.r) / (float)(steps - 1);
  smoothGStepY = (float)(beginY.g - endY.g) / (float)(steps - 1);
  smoothBStepY = (float)(beginY.b - endY.b) / (float)(steps - 1);
  Serial.printf("xr:%f,g:%f,b:%f\n", smoothRStepX, smoothGStepX, smoothBStepX);
  Serial.printf("yr:%f,g:%f,b:%f\n", smoothRStepY, smoothGStepY, smoothBStepY);
  lastSmoothGradient = millis();
  smoothGradientSteps = steps;
  smoothGradientDuration = duration;
  smoothGradientFlag = true;
  smoothGradientIndex = 0;
  gradient(beginX, beginY, LEDCount);
  currX = beginX;
  currY = beginY;
  Serial.printf("XR:%d,XG:%d,XB:%d,YR:%d,YG:%d,YB:%d\n", currX.r, currX.g, currX.b, currY.r, currY.g, currY.b);
}

void advenceSmoothGradient() {
  smoothGradientIndex++;
  Serial.printf("xr:%d,xg:%d,xb:%d,yr:%d,yg:%d,yb:%d\n", currX.r - (int)(smoothRStepX * smoothGradientIndex), currX.g - (int)(smoothGStepX * smoothGradientIndex), currX.b - (int)(smoothBStepX * smoothGradientIndex), currY.r - (int)(smoothRStepY * smoothGradientIndex), currY.g - (int)(smoothGStepY * smoothGradientIndex), currY.b - (int)(smoothBStepY * smoothGradientIndex));
  gradient({ currX.r - (int)(smoothRStepX * smoothGradientIndex), currX.g - (int)(smoothGStepX * smoothGradientIndex), currX.b - (int)(smoothBStepX * smoothGradientIndex) }, { currY.r - (int)(smoothRStepY * smoothGradientIndex), currY.g - (int)(smoothGStepY * smoothGradientIndex), currY.b - (int)(smoothBStepY * smoothGradientIndex) }, 15);
}

void setupNightRider() {
  nightRiderCount = 0;
  nightRiderState = 1;
}

void advanceNightRider() {
  nightRiderTimeStamp = millis();
  if (nightRiderCount >= 13) {
    nightRiderState = 2;
  } else if (nightRiderCount <= 0) {
    nightRiderState = 1;
  }

  switch (nightRiderState) {
    case 2:
      {
        nightRiderCount--;
        break;
      }
    case 1:
      {
        nightRiderCount++;
        break;
      }
    case 0:
      {
        break;
      }
  }
  fill({ 0, 0, 0 });
  strip.setPixelColor(nightRiderCount, nightRiderColor.r, nightRiderColor.g, nightRiderColor.b);
  strip.setPixelColor(nightRiderCount + 1, nightRiderColor.r, nightRiderColor.g, nightRiderColor.b);
  strip.show();
}

void inicializeConection() {
  String id = LAMP_ID;
  deobfuscateString(id);
  String idk = "init;" + String(id) + ";" + getGameData();
  Serial.println(idk);
  webSocket.sendTXT(idk);
}

void setupWS(String s) {
  StringSplitter *splitter = new StringSplitter(s.c_str(), ':', 3);
  if(!Ping.ping(splitter->getItemAtIndex(0).c_str(),3)) {
    delete splitter;
    return;
  }
  delete splitter;

  webSocket.setSSLClientCertKey(ENDPOINT_CA_CERT, ENDPOINT_CA_KEY);
  if(s.indexOf(":") == -1) {
    webSocket.beginSSL(s.c_str(), 25569);
  }
  else {
    StringSplitter *splitter = new StringSplitter(s.c_str(), ':', 3);
    webSocket.beginSSL(splitter->getItemAtIndex(0).c_str(), atoi(splitter->getItemAtIndex(1).c_str()));
    delete splitter;
  }
  
  webSocket.setReconnectInterval(20000);

  webSocket.onEvent(webSocketEvent);
  webSocket.enableHeartbeat(20000, 60000, 3);
  webSocket.loop();
}

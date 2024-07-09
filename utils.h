#include "WString.h"
#include "EEPROM.h"


//funkce pro zapsání wifi údajů do paměti EEPROM
void writeWiFiEEPROM(String message) {
  Serial.println(message);
  StringSplitter *splitter = new StringSplitter(message, ',', 10);

  int length = splitter->getItemAtIndex(0).length();

  EEPROM.write(100, length);

  for (int i = 0; i < length; i++) {
    EEPROM.write(101 + i, splitter->getItemAtIndex(0)[i]);
  }



  int length2 = splitter->getItemAtIndex(1).length();

  EEPROM.write(165, length2);
  for (int i = 0; i < length2; i++) {
    EEPROM.write(166 + i, splitter->getItemAtIndex(1)[i]);
  }
  delete splitter;
  EEPROM.commit();
}

void writeSSID(String ssid) {
  EEPROM.write(100, ssid.length());
  for(int i = 0;i<ssid.length();i++) {
    EEPROM.write(101 + i, ssid.c_str()[i]);
  }
}

void writePassword(String passwd) {
  EEPROM.write(165, passwd.length());
  for(int i = 0;i<passwd.length();i++) {
    EEPROM.write(166 + i, passwd.c_str()[i]);
  }
}


void writeURL(String url) {
  int length = url.length();
  if (length > 200) { return; }
  EEPROM.write(239, length);
  for (int i = 0; i < length; i++) {
    EEPROM.write(240 + i, url[i]);
  }
  EEPROM.commit();
}

String readURL() {
  int n;
  n = EEPROM.read(239);
  if (n == 255) { return ""; }
  String str = "";
  for (int i = 0; i < n; i++) {
    if (EEPROM.read(240 + i) == 255) { continue; }
    str += char(EEPROM.read(240 + i));
  }
  //if (str != "") { strcpy(ssid, str.c_str()); }
  return str;
}


void writeMode(int mode) {
  EEPROM.write(0, mode);
  EEPROM.commit();
}

int readMode() {
  int i = EEPROM.read(0);
  if (i > 20) { return 0; }
  return i;
}

void writeBrightness(int brightness) {
  EEPROM.write(1, brightness);
  EEPROM.commit();
}
int readBrightness() {
  return EEPROM.read(1);
}

void writeRGB(int r, int g, int b) {
  EEPROM.write(2, r);
  EEPROM.write(3, g);
  EEPROM.write(4, b);
  EEPROM.commit();
}

int readRed() {
  return EEPROM.read(2);
}
int readGreen() {
  return EEPROM.read(3);
}
int readBlue() {
  return EEPROM.read(4);
}

void writeSpeed1(int speed) {
  EEPROM.write(5, speed);
  EEPROM.commit();
}

int readSpeed1() {
  return EEPROM.read(5);
}

void writeSpeed2(int speed) {
  EEPROM.write(6, speed);
  EEPROM.commit();
}

int readSpeed2() {
  return EEPROM.read(6);
}

void writeManualBrighness(int brightness) {
  EEPROM.write(7, brightness);
  EEPROM.commit();
}

int readManualBrighness() {
  return EEPROM.read(7);
}

void writeTime1(int hours, int minutes) {
  EEPROM.write(8, hours);
  EEPROM.write(9, minutes);
  EEPROM.commit();
}

int readTime1Hours() {
  return EEPROM.read(8);
}
int readTime1Minutes() {
  return EEPROM.read(9);
}

void writeTime2(int hours, int minutes) {
  EEPROM.write(10, hours);
  EEPROM.write(11, minutes);
  EEPROM.commit();
}

int readTime2Hours() {
  return EEPROM.read(10);
}
int readTime2Minutes() {
  return EEPROM.read(11);
}

int getBrightnessFromSensor() {
  int x = analogRead(A0);
  if(x<100) {x=100;}
  if(x>400) {x=400;}
  return map(x, 400, 100, 100, 255);
}



int getTimeInSeconds(String str, bool pm) {
  int i = 0;
  StringSplitter *splitter = new StringSplitter(str, ',', 3);
  int hours = atoi(splitter->getItemAtIndex(0).c_str());
  if (pm) { hours += 12; }
  i += hours * 3600;
  int min = atoi(splitter->getItemAtIndex(1).c_str());
  i += min * 60;
  int sec = atoi(splitter->getItemAtIndex(2).c_str());
  i += sec;
  delete splitter;
  return i;
}

void setAPIDataSource(int i) {
  EEPROM.write(12, i);
  EEPROM.commit();
}

int readAPIDataSource() {
  return EEPROM.read(12);
}

void setBeepSetting(int i) {
  EEPROM.write(13, i);
  EEPROM.commit();
}

int readBeepSetting() {
  return EEPROM.read(13);
} 

int readWiFiMode() {
   return EEPROM.read(14);
}

void setWiFiMode(int i) {
  EEPROM.write(14, i);
  EEPROM.commit();
}

int readButtonMode() {
   return EEPROM.read(15);
}

void setButtonMode(int i) {
  EEPROM.write(15, i);
  EEPROM.commit();
}

void writeGradientData1(int r, int g, int b) {
  EEPROM.write(16, r);
  EEPROM.write(17, g);
  EEPROM.write(18, b);
  EEPROM.commit();
}

void writeGradientData2(int r, int g, int b) {
  EEPROM.write(19, r);
  EEPROM.write(20, g);
  EEPROM.write(21, b);
  EEPROM.commit();
}

String readGradintColor1() {
  return String(EEPROM.read(16)) + "," + String(EEPROM.read(17)) + "," + String(EEPROM.read(18));
}

String readGradintColor2() {
  return String(EEPROM.read(19)) + "," + String(EEPROM.read(20)) + "," + String(EEPROM.read(21));
}

void writeWifiTouch(int i) {
  EEPROM.write(22, i);
  EEPROM.commit();
}

int readWifiTouch() {
  return EEPROM.read(22);
}

void writeOverride(int i) {
  EEPROM.write(23, i);
  EEPROM.commit();
}

int readOverride() {
  return EEPROM.read(23);
}

void writeBrightnessToggle(int i) {
  EEPROM.write(24, i);
}

int readBrightnessToggle() {
  return EEPROM.read(24);
}


String apiCall(String url) {
  if ((WiFi.status() == WL_CONNECTED)) {
    HTTPClient http;
    WiFiClientSecure wifiClient;
    wifiClient.setInsecure();
    wifiClient.connect(url, 80);
    http.begin(wifiClient, url);
    int httpCode = http.GET();
    if (httpCode > 0) {
      return http.getString();
    }

    else {
      return "";
    }

    http.end();
  }
  
  return "";
}

float getLongitude() {
  String str = apiCall("https://ipapi.co/longitude");
  return atof(str.c_str());
}
float getLatitude() {
  String str = apiCall("https://ipapi.co/latitude");
  return atof(str.c_str());
}
int getSunriseTime() {
  String result = apiCall("https://api.sunrisesunset.io/json?lat=" + String(getLatitude()) + "&lng=" + String(getLongitude()) + "&timezone=CET");
  if(result == "") {return -1;}
  DynamicJsonDocument doc(200);
  deserializeJson(doc, result);
  String sunriseString = String(doc["results"]["sunrise"]);
  doc.~BasicJsonDocument();
  return getTimeInSeconds(sunriseString, sunriseString.endsWith("PM"));
}

int getSunsetTime() {
  String result = apiCall("https://api.sunrisesunset.io/json?lat=" + String(getLatitude()) + "&lng=" + String(getLongitude()) + "&timezone=CET");
  if(result == "") {return -1;}
  DynamicJsonDocument doc(200);
  deserializeJson(doc, result);
  String sunriseString = String(doc["results"]["sunset"]);
  doc.~BasicJsonDocument();
  return getTimeInSeconds(sunriseString, sunriseString.endsWith("PM"));
}

String getIP() {
  return apiCall("https://api.ipify.org");
}

int getCurrentTime() {
  String timeString = apiCall("https://timeapi.io/api/Time/current/ip?ipAddress=" + getIP());
  if(timeString == "") {return -1;}
  DynamicJsonDocument timeDoc(300);
  deserializeJson(timeDoc, timeString);
  String stringTime = timeDoc["time"] + ":00";
  stringTime.replace(":", ",");
  timeDoc.~BasicJsonDocument();
  return getTimeInSeconds(stringTime, false);
}


#include <Arduino.h>
#include "my_lv_ports.h"
#include <TFT_eSPI.h>
#include <lvgl.h>
#include <WiFi.h>
#include <Arduino_JSON.h>
#include <HTTPClient.h>
#if LV_BUILD_EXAMPLES && LV_USE_LABEL

static lv_obj_t *label;
static uint32_t seconds = 0;
int timezone = 19;
const char *ssid = "CS431";
const char *password = "baiducom";
String openWeatherMapApiKey = "5c6f2117cecf3bd94b66e4034a37afc1";
// city Illinois chicago
String city = "Champaign County";
String countryCode = "US";
String jsonBuffer;
unsigned long lastTime = 0;
bool first = true;
unsigned long timerDelay = 10000;

String httpGETRequest(const char *serverName)
{
  WiFiClient client;
  HTTPClient http;

  // Your Domain name with URL path or IP address with path
  http.begin(client, serverName);

  // Send HTTP POST request
  int httpResponseCode = http.GET();

  String payload = "{}";

  if (httpResponseCode > 0)
  {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    payload = http.getString();
  }
  else
  {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  // Free resources
  http.end();

  return payload;
}

JSONVar retrieve_weather_info()
{
  // Check WiFi connection status
  if (WiFi.status() == WL_CONNECTED)
  {
    String serverPath = "http://api.openweathermap.org/data/2.5/weather?q=" + city + "," + countryCode + "&APPID=" + openWeatherMapApiKey;

    jsonBuffer = httpGETRequest(serverPath.c_str());
    Serial.println(jsonBuffer);
    JSONVar myObject = JSON.parse(jsonBuffer);

    // JSON.typeof(jsonVar) can be used to get the type of the var
    if (JSON.typeof(myObject) == "undefined")
    {
      Serial.println("Parsing input failed!");
      return myObject;
    }
    return myObject;

    // Serial.print("JSON object = ");
    // Serial.println(myObject);
    // Serial.print("Temperature: ");
    // Serial.println(myObject["main"]["temp"]);
    // Serial.print("Pressure: ");
    // Serial.println(myObject["main"]["pressure"]);
    // Serial.print("Humidity: ");
    // Serial.println(myObject["main"]["humidity"]);
    // Serial.print("Wind Speed: ");
    // Serial.println(myObject["wind"]["speed"]);
  }
  else
  {
    Serial.println("WiFi Disconnected");
    JSONVar temp;
    return temp;
  }
  
}
void wifi_init(void)
{
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println("SSID");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  // get current time
  configTime(timezone * 3600, 0, "pool.ntp.org", "time.nist.gov");
  Serial.println("Waiting for NTP time sync: ");
  time_t now = time(nullptr);
  while (now < 8 * 3600 * 2)
  {
    delay(500);
    Serial.print(".");
    now = time(nullptr);
  }
  Serial.println("");
}

static void update_clock(void)
{
  uint32_t hours = seconds / 3600;
  uint32_t minutes = (seconds % 3600) / 60;
  uint32_t remaining_seconds = seconds % 60;

  char buffer[9];
  snprintf(buffer, sizeof(buffer), "%02u:%02u:%02u", hours, minutes, remaining_seconds);
  lv_label_set_text(label, buffer);
}

static void reset_time(lv_event_t *e)
{
  seconds = 0;
  update_clock();
}

static void timer_callback(lv_timer_t *timer)
{
  seconds++;
  update_clock();
}

void lv_clock(void)
{
  /*Change the active screen's background color*/
  lv_obj_set_style_bg_color(lv_scr_act(), lv_color_hex(0x003a57), LV_PART_MAIN);
   /*Set a larger font*/
  // lv_style_set_text_font(&my_style, LV_STATE_DEFAULT, &lv_font_montserrat_28); 

  /*Create a white label, set its text and align it to the center*/
  label = lv_label_create(lv_scr_act());
  lv_label_set_text(label, "00:00:00");
  lv_obj_set_style_text_color(label, lv_color_hex(0xffffff), LV_PART_MAIN);
  lv_obj_align(label, LV_ALIGN_CENTER, 0, -30);

  /*Create a reset button and a label for the button*/
  // lv_obj_t * reset_button = lv_btn_create(lv_scr_act());
  // lv_obj_set_size(reset_button, 100, 50);
  // lv_obj_align(reset_button, LV_ALIGN_CENTER, 0, 30);
  // lv_obj_add_event_cb(reset_button, reset_time, LV_EVENT_CLICKED, NULL);

  // lv_obj_t * reset_button_label = lv_label_create(reset_button);
  // lv_label_set_text(reset_button_label, "Reset");

  // text scrolling.
  lv_obj_t *label2 = lv_label_create(lv_scr_act());
  lv_label_set_long_mode(label2, LV_LABEL_LONG_SCROLL_CIRCULAR); /*Circular scroll*/
  lv_obj_set_width(label2, 150);
  lv_label_set_text(label2, "WEATHER XXXXXXXXXXXXXXXXXXXXXXXXXX");
  lv_obj_set_style_text_color(label2, lv_color_hex(0xffffff), LV_PART_MAIN);
  lv_obj_align(label2, LV_ALIGN_CENTER, 0, 40);

  /*Create a timer to update the clock every second*/
  lv_timer_create(timer_callback, 1000, NULL);
}
void lv_weather(JSONVar myObject)
{

  /*Create a white label, set its text and align it to the center*/
  auto temp_label = lv_label_create(lv_scr_act());
  // parse the jsonvar myObject["main"]["temp"] to a string
  float temp = (JSON.stringify(myObject["main"]["temp"])).toFloat() - 273.15;

  String temp_string = String(temp);

  lv_label_set_text(temp_label, temp_string.c_str());
  lv_obj_set_style_text_color(temp_label, lv_color_hex(0xffffff), LV_PART_MAIN);
  lv_obj_align(temp_label, LV_ALIGN_CENTER, 0, -60);
}
#endif
void setup()
{
  Serial.begin(115200); /* prepare for possible serial debug */

  String LVGL_Arduino = "Hello Arduino! ";
  LVGL_Arduino += String('V') + lv_version_major() + "." + lv_version_minor() +
                  "." + lv_version_patch();

  Serial.println(LVGL_Arduino);
  Serial.println("I am LVGL_Arduino");
  wifi_init();
  time_t now;
  struct tm *timeinfo;
  time(&now);
  timeinfo = localtime(&now);
  // serial print the time
  Serial.println(asctime(timeinfo));
  seconds = timeinfo->tm_sec + timeinfo->tm_min * 60 + timeinfo->tm_hour * 3600;
  //
  JSONVar myobject = retrieve_weather_info();

  lv_init();
  my_disp_init();

  /* Create simple label */
  // lv_obj_t *label = lv_label_create(lv_scr_act());
  // lv_label_set_text(label, LVGL_Arduino.c_str());
  // lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
  lv_clock();
  lv_weather(myobject);

  Serial.println("Setup done");
}

void loop()
{
  lv_timer_handler(); /* let the GUI do its work */
  delay(5);
}
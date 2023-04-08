#include <Arduino.h>
#include "my_lv_ports.h"
#include <TFT_eSPI.h>
#include <lvgl.h>
#include "demos/lv_demos.h"
#include <WiFi.h>

#if LV_BUILD_EXAMPLES && LV_USE_LABEL

static lv_obj_t * label;
static uint32_t seconds = 0;
int timezone = 19;
const char* ssid = "CS431";
const char* password = "baiducom";

void wifi_init(void) {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println("SSID");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  // get current time
  // configTime(timezone * 3600, 0, "pool.ntp.org", "time.nist.gov");
  // Serial.println("Waiting for NTP time sync: ");
  // while (!time(nullptr)) {
  //   Serial.print(".");
  //   delay(1000);
  // }
  // Serial.println("");
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

static void reset_time(lv_event_t * e)
{
    seconds = 0;
    update_clock();
}

static void timer_callback(lv_timer_t * timer)
{
    seconds++;
    update_clock();
}

void lv_example_get_started_2(void)
{
    /*Change the active screen's background color*/
    lv_obj_set_style_bg_color(lv_scr_act(), lv_color_hex(0x003a57), LV_PART_MAIN);

    /*Create a white label, set its text and align it to the center*/
    label = lv_label_create(lv_scr_act());
    lv_label_set_text(label, "00:00:00");
    lv_obj_set_style_text_color(label, lv_color_hex(0xffffff), LV_PART_MAIN);
    lv_obj_align(label, LV_ALIGN_CENTER, 0, -30);

    /*Create a reset button and a label for the button*/
    lv_obj_t * reset_button = lv_btn_create(lv_scr_act());
    lv_obj_set_size(reset_button, 100, 50);
    lv_obj_align(reset_button, LV_ALIGN_CENTER, 0, 30);
    lv_obj_add_event_cb(reset_button, reset_time, LV_EVENT_CLICKED, NULL);

    lv_obj_t * reset_button_label = lv_label_create(reset_button);
    lv_label_set_text(reset_button_label, "Reset");

    /*Create a timer to update the clock every second*/
    lv_timer_create(timer_callback, 1000, NULL);
}


#endif
void setup() {
  Serial.begin(115200); /* prepare for possible serial debug */

  String LVGL_Arduino = "Hello Arduino! ";
  LVGL_Arduino += String('V') + lv_version_major() + "." + lv_version_minor() +
                  "." + lv_version_patch();

  Serial.println(LVGL_Arduino);
  Serial.println("I am LVGL_Arduino");
  wifi_init();
  // time_t now;
  // struct tm* timeinfo;
  // time(&now);
  // timeinfo = localtime(&now);
  // seconds = timeinfo->tm_sec + timeinfo->tm_min * 60 + timeinfo->tm_hour * 3600;
  lv_init();
  my_disp_init();
  lv_example_get_started_2();
  Serial.println("Setup done");
}

void loop() {
  lv_timer_handler(); /* let the GUI do its work */
  delay(5);
}
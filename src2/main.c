#include "lvgl.h"
#include "app_hal.h"

#include "demos/lv_demos.h"
#if LV_BUILD_EXAMPLES && LV_USE_LABEL

static lv_obj_t * label;
static uint32_t seconds = 0;

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
int main(void)
{
    lv_init();

    hal_setup();

    lv_example_get_started_2();

    hal_loop();
}

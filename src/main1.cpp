// #include <lvgl.h>
// #include <Adafruit_GFX.h>
// #include <Adafruit_ST7789.h>
// #include <SPI.h>
// #define TFT_CS        5 // Hallowing display control pins: chip select
// #define TFT_RST       16 // Display reset
// #define TFT_DC        27 // Display data/command select
// #define TFT_BACKLIGHT  26 // Display backlight pin

// // OPTION 1 (recommended) is to use the HARDWARE SPI pins, which are unique
// // to each board and not reassignable.
// //Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

// // OPTION 2 lets you interface the display using ANY TWO or THREE PINS,
// // tradeoff being that performance is not as fast as hardware SPI above.
// #define TFT_MOSI 23  // Data out
// #define TFT_SCLK 18  // Clock out

// // OPTION 1 (recommended) is to use the HARDWARE SPI pins, which are unique
// // to each board and not reassignable. For Arduino Uno: MOSI = pin 11 and
// // SCLK = pin 13. This is the fastest mode of operation and is required if
// // using the breakout board's microSD card.

// Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

// void lv_example_get_started_1(void)
// {
//     /*Change the active screen's background color*/
//     lv_obj_set_style_bg_color(lv_scr_act(), lv_color_hex(0x003a57), LV_PART_MAIN);

//     /*Create a white label, set its text and align it to the center*/
//     lv_obj_t * label = lv_label_create(lv_scr_act());
//     lv_label_set_text(label, "Hello world");
//     lv_obj_set_style_text_color(lv_scr_act(), lv_color_hex(0xffffff), LV_PART_MAIN);
//     lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
// }
// static void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p) {
//   uint16_t width = area->x2 - area->x1 + 1;
//   uint16_t height = area->y2 - area->y1 + 1;

//   tft.startWrite();
//   tft.setAddrWindow(area->x1, area->y1, width, height);
//   tft.writePixels((uint16_t*)color_p, width * height);
//   tft.endWrite();

//   lv_disp_flush_ready(disp);
// }

// void setup(void) {
//   Serial.begin(9600);
//   Serial.print(F("Hello! lgvl hello world Test"));

//   // Use this initializer (uncomment) if using a 1.3" or 1.54" 240x240 TFT:
//   //tft.init(240, 240);           // Init ST7789 240x240

//   // OR use this initializer (uncomment) if using a 1.69" 280x240 TFT:
//   //tft.init(240, 280);           // Init ST7789 280x240

//   // OR use this initializer (uncomment) if using a 2.0" 320x240 TFT:
//   tft.init(240, 320);           // Init ST7789 320x240

//   // OR use this initializer (uncomment) if using a 1.14" 240x135 TFT:
//   //tft.init(135, 240);           // Init ST7789 240x135
  
//   // OR use this initializer (uncomment) if using a 1.47" 172x320 TFT:
//   //tft.init(172, 320);           // Init ST7789 172x320

//   // OR use this initializer (uncomment) if using a 1.9" 170x320 TFT:
//   //tft.init(170, 320);           // Init ST7789 170x320

//   // SPI speed defaults to SPI_DEFAULT_FREQ defined in the library, you can override it here
//   // Note that speed allowable depends on chip and quality of wiring, if you go too fast, you
//   // may end up with a black screen some times, or all the time.
//   //tft.setSPISpeed(40000000);
//   Serial.println(F("Initialized"));
//   delay(500);

//   // lgvl part
//   lv_init();
//   static lv_disp_draw_buf_t draw_buf;
//   static lv_color_t buf[320 * 10];
//   lv_disp_draw_buf_init(&draw_buf, buf, NULL, 320 * 10);

//   lv_disp_drv_t disp_drv;
//   lv_disp_drv_init(&disp_drv);
//   disp_drv.flush_cb = my_disp_flush; 
//   disp_drv.draw_buf = &draw_buf;
//   lv_disp_drv_register(&disp_drv);

//   lv_example_get_started_1();

  
// }
// void loop(void) {

// }
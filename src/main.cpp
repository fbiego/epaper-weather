#include <Arduino.h>
#include <WiFi.h>
#include <WiFiMulti.h>
#include "ChronosESP32.h"
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "lvgl.h"

#include "ui/ui.h"

#define ENABLE_GxEPD2_GFX 0
#include <GxEPD2_BW.h>

GxEPD2_BW<GxEPD2_371, GxEPD2_371::HEIGHT> display(GxEPD2_371(/*CS=5*/ 45, /*DC=*/46, /*RST=*/47, /*BUSY=*/48)); // GDEW0371W7 240x416, UC8171 (IL0324)

#define GxEPD2_DISPLAY_CLASS GxEPD2_BW
#define GxEPD2_DRIVER_CLASS GxEPD2_371 // GDEW0371W7  240x416, UC8171 (IL0324), (missing)

#define SCR_WIDTH 416
#define SCR_HEIGHT 240
#define LVBUF ((SCR_WIDTH * SCR_HEIGHT / 8) + 8)

WiFiMulti wifiMulti;
ESP32Time rtc(3600 * 3);

static lv_display_t *lvDisplay;
static uint8_t lvBuffer[LVBUF];
uint8_t *lvBuf;

bool screen, data; // flags for data
int lastUpdate = -1;

String query = "__CITY__";
String token = "__API_KEY__";
String url = "http://api.weatherapi.com/v1/forecast.json?key=" + token + "&q=" + query + "&days=3&aqi=no&alerts=no";

const lv_image_dsc_t *dayIcon(int code);
const lv_image_dsc_t *nightIcon(int code);

void rotate90(const uint8_t *input, int width, int height)
{
  int newWidth = height;
  int newHeight = width;
  int inputBytesPerRow = width / 8;
  int outputBytesPerRow = newWidth / 8;

  for (int y = 0; y < height; ++y)
  {
    for (int x = 0; x < width; ++x)
    {
      // Calculate the input bit position
      int inputByteIndex = (y * inputBytesPerRow) + (x / 8);
      int inputBit = (input[inputByteIndex] >> (7 - (x % 8))) & 0x01;

      // Calculate the rotated position in the output
      int newX = y;
      int newY = width - x - 1;
      int outputByteIndex = (newY * outputBytesPerRow) + (newX / 8);
      int outputBitPos = 7 - (newX % 8);

      // Set the output bit
      if (!inputBit)
      {
        lvBuffer[outputByteIndex] |= (1 << outputBitPos);
      }
      else
      {
        lvBuffer[outputByteIndex] &= ~(1 << outputBitPos);
      }
    }
  }
}

void my_disp_flush(lv_display_t *disp, const lv_area_t *area, unsigned char *data)
{
  int16_t width = area->x2 - area->x1 + 1;
  int16_t height = area->y2 - area->y1 + 1;

  // display.drawImage((uint8_t *)data + 8, area->x1, area->y1, width, height);

  rotate90((uint8_t *)data + 8, width, height);

  // Draw the rotated image
  display.drawImage(lvBuffer, area->y1, area->x1, height, width);

  lv_display_flush_ready(disp);

  // flushing complete when bottom right area flushed
  screen = (area->x1 + width == SCR_WIDTH) && (area->y1 + height == SCR_HEIGHT);
}

void addForecast(int code, float temp, int hour, bool day)
{
  ui_forecastItem = lv_obj_create(ui_forecastList);
  lv_obj_set_width(ui_forecastItem, 59);
  lv_obj_set_height(ui_forecastItem, 70);
  lv_obj_set_x(ui_forecastItem, 67);
  lv_obj_set_y(ui_forecastItem, 26);
  lv_obj_set_align(ui_forecastItem, LV_ALIGN_CENTER);
  lv_obj_set_flex_flow(ui_forecastItem, LV_FLEX_FLOW_COLUMN);
  lv_obj_set_flex_align(ui_forecastItem, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
  lv_obj_remove_flag(ui_forecastItem, LV_OBJ_FLAG_SCROLLABLE); /// Flags
  lv_obj_set_style_border_width(ui_forecastItem, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_pad_left(ui_forecastItem, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_pad_right(ui_forecastItem, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_pad_top(ui_forecastItem, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_pad_bottom(ui_forecastItem, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_pad_row(ui_forecastItem, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_pad_column(ui_forecastItem, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

  ui_forecastIcon = lv_image_create(ui_forecastItem);
  lv_image_set_src(ui_forecastIcon, day ? dayIcon(code) : nightIcon(code));
  lv_obj_set_width(ui_forecastIcon, 32);
  lv_obj_set_height(ui_forecastIcon, 32);
  lv_obj_set_align(ui_forecastIcon, LV_ALIGN_CENTER);
  lv_obj_add_flag(ui_forecastIcon, LV_OBJ_FLAG_CLICKABLE);     /// Flags
  lv_obj_remove_flag(ui_forecastIcon, LV_OBJ_FLAG_SCROLLABLE); /// Flags
  lv_image_set_scale(ui_forecastIcon, 128);
  lv_obj_set_style_image_recolor(ui_forecastIcon, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_image_recolor_opa(ui_forecastIcon, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

  ui_forecastTemp = lv_label_create(ui_forecastItem);
  lv_obj_set_width(ui_forecastTemp, 51);
  lv_obj_set_height(ui_forecastTemp, LV_SIZE_CONTENT); /// 1
  lv_obj_set_align(ui_forecastTemp, LV_ALIGN_CENTER);
  lv_label_set_long_mode(ui_forecastTemp, LV_LABEL_LONG_CLIP);
  lv_label_set_text_fmt(ui_forecastTemp, "%.0f°C", temp);
  lv_obj_set_style_text_align(ui_forecastTemp, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_font(ui_forecastTemp, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);

  ui_forecastTime = lv_label_create(ui_forecastItem);
  lv_obj_set_width(ui_forecastTime, 52);
  lv_obj_set_height(ui_forecastTime, LV_SIZE_CONTENT); /// 1
  lv_obj_set_align(ui_forecastTime, LV_ALIGN_CENTER);
  lv_label_set_long_mode(ui_forecastTime, LV_LABEL_LONG_CLIP);
  lv_label_set_text_fmt(ui_forecastTime, "%02d:00", hour);
  lv_obj_set_style_text_align(ui_forecastTime, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_font(ui_forecastTime, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
}

void updateTime()
{
  HTTPClient http;
  http.begin("https://iot.fbiego.com/api/v1/time");
  int httpCode = http.GET();
  String payload = http.getString();
  Serial.println(payload);
  if (httpCode == HTTP_CODE_OK)
  {
    DynamicJsonDocument json(512);
    deserializeJson(json, payload);
    rtc.setTime(json["timestamp"].as<unsigned long>());
  }
  http.end();
}

void updateData()
{
  HTTPClient http;
  Serial.println(url);
  http.begin(url);
  int httpCode = http.GET();
  String payload = http.getString();
  Serial.println(httpCode);
  if (httpCode == HTTP_CODE_OK)
  {
    // Serial.println(payload);
    DynamicJsonDocument json(16384);
    deserializeJson(json, payload);

    lv_label_set_text(ui_wifiName, WiFi.SSID().c_str());
    lv_label_set_text(ui_cityText, json["location"]["name"].as<const char *>());
    lv_label_set_text(ui_countryText, json["location"]["country"].as<const char *>());
    lv_label_set_text_fmt(ui_currentTemp, "%.1f°C", json["current"]["temp_c"].as<float>());
    lv_label_set_text(ui_updateTime, rtc.getTime("%T %D").c_str());
    lv_label_set_text(ui_weatherText, json["current"]["condition"]["text"].as<const char *>());
    lv_label_set_text_fmt(ui_humidityText, "%.0f%%", json["current"]["humidity"].as<float>());
    lv_label_set_text_fmt(ui_uvText, "%.1f", json["current"]["uv"].as<float>());
    lv_label_set_text_fmt(ui_rainText, "%.1f", json["current"]["precip_mm"].as<float>());
    lv_label_set_text_fmt(ui_windText, "%.0fkm/h", json["current"]["wind_kph"].as<float>());

    int currentCode = json["current"]["condition"]["code"].as<int>();
    int isDay = json["current"]["is_day"].as<int>();

    lv_image_set_src(ui_weatherIcon, isDay ? dayIcon(currentCode) : nightIcon(currentCode));


    lv_obj_clean(ui_forecastList); // clear the list in preparation of new data

    int day = 0;
    int z = 0;
    int high = json["current"]["temp_c"].as<int>();
    int low = high;

    JsonArray forecast = json["forecast"]["forecastday"].as<JsonArray>();
    Serial.printf("Forecast array %d\n", forecast.size());
    for (JsonVariant v : forecast)
    {
      if (v.is<JsonObject>())
      {

        int h = 0;
        JsonArray hour = v["hour"].as<JsonArray>();
        Serial.printf("Hour array %d\n", hour.size());
        for (JsonVariant k : hour)
        {
          if (k.is<JsonObject>())
          {
            float t = k["temp_c"].as<float>();
            int code = k["condition"]["code"].as<int>();
            int is_day = k["is_day"].as<int>();


            if ((int)t > high && day == 0)
            {
              high = (int)t;
            }
            if ((int)t < low && day == 0)
            {
              low = (int)t;
            }

            if (h % 4 == 0 && z < 7)
            {
              if ((day == 0 && h > rtc.getHour(true)) || day > 0)
              {
                addForecast(code, t, h, is_day == 1);
                Serial.printf("Added index %d, hour %d, day %d \n", z, h, day);
                z++;
              }
            }
          }

          h++;
        }
      }
      day++;
    }

    lv_label_set_text_fmt(ui_highLowTemp, "H:%d L:%d", high, low);
  }
  http.end();
}

static uint32_t my_tick(void)
{
  return millis();
}

void epd_setup()
{

  SPI.begin(12, -1, 11, 45);
  display.init(115200, true);
  if (display.pages() > 1)
  {
    delay(100);
    Serial.print("pages = ");
    Serial.print(display.pages());
    Serial.print(" page height = ");
    Serial.println(display.pageHeight());
    delay(1000);
  }
  // display.clearScreen(); return;
  //  first update should be full refresh
  delay(1000);
}

void setup()
{

  Serial.begin(115200);

  Serial.println("Startup 0");

  // Initialization settings, executed once when the program starts
  pinMode(7, OUTPUT);    // Set pin 7 to output mode
  digitalWrite(7, HIGH); // Set pin 7 to high level to activate the screen power
  pinMode(41, OUTPUT);
  digitalWrite(41, HIGH);

  WiFi.mode(WIFI_STA);
  // wifiMulti.addAP("__SSID__", "__PASS__");
  // wifiMulti.addAP("__SSID2__", "__PASS2__");
  // wifiMulti.addAP("__SSID3__", "__PASS3__");

  epd_setup();

  lv_init();

  lv_tick_set_cb(my_tick);

  lvDisplay = lv_display_create(SCR_WIDTH, SCR_HEIGHT);
  lv_display_set_flush_cb(lvDisplay, my_disp_flush);
  lvBuf = (uint8_t *)malloc(LVBUF);
  lv_display_set_buffers(lvDisplay, lvBuf, NULL, LVBUF, LV_DISPLAY_RENDER_MODE_DIRECT);

  ui_init();

  lv_obj_clean(ui_forecastList);

  lv_label_set_text(ui_cityText, "");
  lv_label_set_text(ui_countryText, "");
  lv_label_set_text(ui_currentTemp, "0.0°C");
  lv_label_set_text(ui_updateTime, rtc.getTimeDate().c_str());
  lv_label_set_text(ui_weatherText, "");
  lv_label_set_text(ui_humidityText, "0.0%");
  lv_label_set_text(ui_uvText, "0.0");
  lv_label_set_text(ui_rainText, "0.0");
  lv_label_set_text(ui_windText, "0.0km/h");
  lv_label_set_text(ui_highLowTemp, "H:0 L:0");
  lv_label_set_text(ui_wifiName, "Connecting...");

  int tries;
  while (wifiMulti.run() != WL_CONNECTED)
  {
    delay(100);
    tries++;
    if (tries > 1000)
    {
      ESP.restart();
    }
  }

  updateTime();

  updateData();

  digitalWrite(41, LOW);

  lastUpdate = rtc.getHour();
}

void loop()
{
  lv_timer_handler(); // Update the UI-
  delay(10);

  if (lastUpdate != rtc.getHour())
  {
    ESP.restart();
  }
}

const lv_image_dsc_t *dayIcon(int code)
{
  switch (code)
  {
  case 1000:
    return &ui_img_day_113_png;
  case 1003:
    return &ui_img_day_116_png;
  case 1006:
    return &ui_img_day_119_png;
  case 1009:
    return &ui_img_day_122_png;
  case 1030:
    return &ui_img_day_143_png;
  case 1063:
    return &ui_img_day_176_png;
  case 1066:
    return &ui_img_day_179_png;
  case 1069:
    return &ui_img_day_182_png;
  case 1072:
    return &ui_img_day_185_png;
  case 1087:
    return &ui_img_day_200_png;
  case 1114:
    return &ui_img_day_227_png;
  case 1117:
    return &ui_img_day_230_png;
  case 1135:
    return &ui_img_day_248_png;
  case 1147:
    return &ui_img_day_260_png;
  case 1150:
    return &ui_img_day_263_png;
  case 1153:
    return &ui_img_day_266_png;
  case 1168:
    return &ui_img_day_281_png;
  case 1171:
    return &ui_img_day_284_png;
  case 1180:
    return &ui_img_day_293_png;
  case 1183:
    return &ui_img_day_296_png;
  case 1186:
    return &ui_img_day_299_png;
  case 1189:
    return &ui_img_day_302_png;
  case 1192:
    return &ui_img_day_305_png;
  case 1195:
    return &ui_img_day_308_png;
  case 1198:
    return &ui_img_day_311_png;
  case 1201:
    return &ui_img_day_314_png;
  case 1204:
    return &ui_img_day_317_png;
  case 1207:
    return &ui_img_day_320_png;
  case 1210:
    return &ui_img_day_323_png;
  case 1213:
    return &ui_img_day_326_png;
  case 1216:
    return &ui_img_day_329_png;
  case 1219:
    return &ui_img_day_332_png;
  case 1222:
    return &ui_img_day_335_png;
  case 1225:
    return &ui_img_day_338_png;
  case 1237:
    return &ui_img_day_350_png;
  case 1240:
    return &ui_img_day_353_png;
  case 1243:
    return &ui_img_day_356_png;
  case 1246:
    return &ui_img_day_359_png;
  case 1249:
    return &ui_img_day_362_png;
  case 1252:
    return &ui_img_day_365_png;
  case 1255:
    return &ui_img_day_368_png;
  case 1258:
    return &ui_img_day_371_png;
  case 1261:
    return &ui_img_day_374_png;
  case 1264:
    return &ui_img_day_377_png;
  case 1273:
    return &ui_img_day_386_png;
  case 1276:
    return &ui_img_day_389_png;
  case 1279:
    return &ui_img_day_392_png;
  case 1282:
    return &ui_img_day_395_png;
  default:
    return NULL; // Return -1 if code not found
  }
}


const lv_image_dsc_t *nightIcon(int code)
{
  switch (code)
  {
  case 1000:
    return &ui_img_night_113_png;
  case 1003:
    return &ui_img_night_116_png;
  case 1006:
    return &ui_img_night_119_png;
  case 1009:
    return &ui_img_night_122_png;
  case 1030:
    return &ui_img_night_143_png;
  case 1063:
    return &ui_img_night_176_png;
  case 1066:
    return &ui_img_night_179_png;
  case 1069:
    return &ui_img_night_182_png;
  case 1072:
    return &ui_img_night_185_png;
  case 1087:
    return &ui_img_night_200_png;
  case 1114:
    return &ui_img_night_227_png;
  case 1117:
    return &ui_img_night_230_png;
  case 1135:
    return &ui_img_night_248_png;
  case 1147:
    return &ui_img_night_260_png;
  case 1150:
    return &ui_img_night_263_png;
  case 1153:
    return &ui_img_night_266_png;
  case 1168:
    return &ui_img_night_281_png;
  case 1171:
    return &ui_img_night_284_png;
  case 1180:
    return &ui_img_night_293_png;
  case 1183:
    return &ui_img_night_296_png;
  case 1186:
    return &ui_img_night_299_png;
  case 1189:
    return &ui_img_night_302_png;
  case 1192:
    return &ui_img_night_305_png;
  case 1195:
    return &ui_img_night_308_png;
  case 1198:
    return &ui_img_night_311_png;
  case 1201:
    return &ui_img_night_314_png;
  case 1204:
    return &ui_img_night_317_png;
  case 1207:
    return &ui_img_night_320_png;
  case 1210:
    return &ui_img_night_323_png;
  case 1213:
    return &ui_img_night_326_png;
  case 1216:
    return &ui_img_night_329_png;
  case 1219:
    return &ui_img_night_332_png;
  case 1222:
    return &ui_img_night_335_png;
  case 1225:
    return &ui_img_night_338_png;
  case 1237:
    return &ui_img_night_350_png;
  case 1240:
    return &ui_img_night_353_png;
  case 1243:
    return &ui_img_night_356_png;
  case 1246:
    return &ui_img_night_359_png;
  case 1249:
    return &ui_img_night_362_png;
  case 1252:
    return &ui_img_night_365_png;
  case 1255:
    return &ui_img_night_368_png;
  case 1258:
    return &ui_img_night_371_png;
  case 1261:
    return &ui_img_night_374_png;
  case 1264:
    return &ui_img_night_377_png;
  case 1273:
    return &ui_img_night_386_png;
  case 1276:
    return &ui_img_night_389_png;
  case 1279:
    return &ui_img_night_392_png;
  case 1282:
    return &ui_img_night_395_png;
  default:
    return NULL; // Return -1 if code not found
  }
}
// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.4.2
// LVGL version: 9.1.0
// Project name: Weather

#include "../ui.h"

void ui_Screen1_screen_init(void)
{
    ui_Screen1 = lv_obj_create(NULL);
    lv_obj_remove_flag(ui_Screen1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_Screen1, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Screen1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_cityText = lv_label_create(ui_Screen1);
    lv_obj_set_width(ui_cityText, 150);
    lv_obj_set_height(ui_cityText, LV_SIZE_CONTENT);    /// 1
    lv_label_set_long_mode(ui_cityText, LV_LABEL_LONG_CLIP);
    lv_label_set_text(ui_cityText, "Nairobi");
    lv_obj_set_style_text_font(ui_cityText, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_weatherIcon = lv_image_create(ui_Screen1);
    lv_image_set_src(ui_weatherIcon, &ui_img_day_176_png);
    lv_obj_set_width(ui_weatherIcon, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_weatherIcon, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_weatherIcon, 0);
    lv_obj_set_y(ui_weatherIcon, -40);
    lv_obj_set_align(ui_weatherIcon, LV_ALIGN_LEFT_MID);
    lv_obj_add_flag(ui_weatherIcon, LV_OBJ_FLAG_CLICKABLE);     /// Flags
    lv_obj_remove_flag(ui_weatherIcon, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_image_recolor(ui_weatherIcon, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_image_recolor_opa(ui_weatherIcon, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_currentTemp = lv_label_create(ui_Screen1);
    lv_obj_set_width(ui_currentTemp, 120);
    lv_obj_set_height(ui_currentTemp, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_currentTemp, 70);
    lv_obj_set_y(ui_currentTemp, -50);
    lv_obj_set_align(ui_currentTemp, LV_ALIGN_LEFT_MID);
    lv_label_set_long_mode(ui_currentTemp, LV_LABEL_LONG_CLIP);
    lv_label_set_text(ui_currentTemp, "19.3°C");
    lv_obj_set_style_text_font(ui_currentTemp, &lv_font_montserrat_36, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_updateTime = lv_label_create(ui_Screen1);
    lv_obj_set_width(ui_updateTime, 144);
    lv_obj_set_height(ui_updateTime, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_updateTime, LV_ALIGN_TOP_RIGHT);
    lv_label_set_long_mode(ui_updateTime, LV_LABEL_LONG_CLIP);
    lv_label_set_text(ui_updateTime, "12:45:39 10/11/2024");
    lv_obj_set_style_text_align(ui_updateTime, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_updateTime, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_highLowTemp = lv_label_create(ui_Screen1);
    lv_obj_set_width(ui_highLowTemp, 120);
    lv_obj_set_height(ui_highLowTemp, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_highLowTemp, 70);
    lv_obj_set_y(ui_highLowTemp, -20);
    lv_obj_set_align(ui_highLowTemp, LV_ALIGN_LEFT_MID);
    lv_label_set_long_mode(ui_highLowTemp, LV_LABEL_LONG_CLIP);
    lv_label_set_text(ui_highLowTemp, "H:25 L:16");
    lv_obj_set_style_text_font(ui_highLowTemp, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_weatherText = lv_label_create(ui_Screen1);
    lv_obj_set_width(ui_weatherText, 180);
    lv_obj_set_height(ui_weatherText, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_weatherText, 0);
    lv_obj_set_y(ui_weatherText, 10);
    lv_obj_set_align(ui_weatherText, LV_ALIGN_LEFT_MID);
    
    lv_label_set_text(ui_weatherText, "Partly Cloudy");
    lv_obj_set_style_text_font(ui_weatherText, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_humidityIcon = lv_image_create(ui_Screen1);
    lv_image_set_src(ui_humidityIcon, &ui_img_humidity_icon_png);
    lv_obj_set_width(ui_humidityIcon, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_humidityIcon, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_humidityIcon, 200);
    lv_obj_set_y(ui_humidityIcon, -60);
    lv_obj_set_align(ui_humidityIcon, LV_ALIGN_LEFT_MID);
    lv_obj_add_flag(ui_humidityIcon, LV_OBJ_FLAG_CLICKABLE);     /// Flags
    lv_obj_remove_flag(ui_humidityIcon, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_windIcon = lv_image_create(ui_Screen1);
    lv_image_set_src(ui_windIcon, &ui_img_wind_icon_png);
    lv_obj_set_width(ui_windIcon, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_windIcon, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_windIcon, 300);
    lv_obj_set_y(ui_windIcon, 0);
    lv_obj_set_align(ui_windIcon, LV_ALIGN_LEFT_MID);
    lv_obj_add_flag(ui_windIcon, LV_OBJ_FLAG_CLICKABLE);     /// Flags
    lv_obj_remove_flag(ui_windIcon, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_rainIcon = lv_image_create(ui_Screen1);
    lv_image_set_src(ui_rainIcon, &ui_img_rain_icon_png);
    lv_obj_set_width(ui_rainIcon, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_rainIcon, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_rainIcon, 200);
    lv_obj_set_y(ui_rainIcon, 0);
    lv_obj_set_align(ui_rainIcon, LV_ALIGN_LEFT_MID);
    lv_obj_add_flag(ui_rainIcon, LV_OBJ_FLAG_CLICKABLE);     /// Flags
    lv_obj_remove_flag(ui_rainIcon, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_uvIcon = lv_image_create(ui_Screen1);
    lv_image_set_src(ui_uvIcon, &ui_img_uv_icon_png);
    lv_obj_set_width(ui_uvIcon, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_uvIcon, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_uvIcon, 300);
    lv_obj_set_y(ui_uvIcon, -60);
    lv_obj_set_align(ui_uvIcon, LV_ALIGN_LEFT_MID);
    lv_obj_add_flag(ui_uvIcon, LV_OBJ_FLAG_CLICKABLE);     /// Flags
    lv_obj_remove_flag(ui_uvIcon, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_humidityText = lv_label_create(ui_Screen1);
    lv_obj_set_width(ui_humidityText, 50);
    lv_obj_set_height(ui_humidityText, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_humidityText, 240);
    lv_obj_set_y(ui_humidityText, -60);
    lv_obj_set_align(ui_humidityText, LV_ALIGN_LEFT_MID);
    lv_label_set_text(ui_humidityText, "50%");
    lv_obj_set_style_text_font(ui_humidityText, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_uvText = lv_label_create(ui_Screen1);
    lv_obj_set_width(ui_uvText, 60);
    lv_obj_set_height(ui_uvText, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_uvText, 340);
    lv_obj_set_y(ui_uvText, -60);
    lv_obj_set_align(ui_uvText, LV_ALIGN_LEFT_MID);
    lv_label_set_text(ui_uvText, "3.2");
    lv_obj_set_style_text_font(ui_uvText, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_rainText = lv_label_create(ui_Screen1);
    lv_obj_set_width(ui_rainText, 50);
    lv_obj_set_height(ui_rainText, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_rainText, 240);
    lv_obj_set_y(ui_rainText, 0);
    lv_obj_set_align(ui_rainText, LV_ALIGN_LEFT_MID);
    lv_label_set_text(ui_rainText, "34");
    lv_obj_set_style_text_font(ui_rainText, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_windText = lv_label_create(ui_Screen1);
    lv_obj_set_width(ui_windText, 60);
    lv_obj_set_height(ui_windText, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_windText, 340);
    lv_obj_set_y(ui_windText, 0);
    lv_obj_set_align(ui_windText, LV_ALIGN_LEFT_MID);
    lv_label_set_text(ui_windText, "15km/h");
    lv_obj_set_style_text_font(ui_windText, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_countryText = lv_label_create(ui_Screen1);
    lv_obj_set_width(ui_countryText, 150);
    lv_obj_set_height(ui_countryText, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_countryText, 0);
    lv_obj_set_y(ui_countryText, 20);
    lv_label_set_long_mode(ui_countryText, LV_LABEL_LONG_CLIP);
    lv_label_set_text(ui_countryText, "Kenya");
    lv_obj_set_style_text_font(ui_countryText, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_wifiName = lv_label_create(ui_Screen1);
    lv_obj_set_width(ui_wifiName, 100);
    lv_obj_set_height(ui_wifiName, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_wifiName, 160);
    lv_obj_set_y(ui_wifiName, 3);
    lv_label_set_long_mode(ui_wifiName, LV_LABEL_LONG_CLIP);
    lv_label_set_text(ui_wifiName, "Pixel_7");
    lv_obj_set_style_text_font(ui_wifiName, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_forecastList = lv_obj_create(ui_Screen1);
    lv_obj_set_width(ui_forecastList, 416);
    lv_obj_set_height(ui_forecastList, 70);
    lv_obj_set_x(ui_forecastList, 0);
    lv_obj_set_y(ui_forecastList, 81);
    lv_obj_set_align(ui_forecastList, LV_ALIGN_CENTER);
    lv_obj_set_flex_flow(ui_forecastList, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(ui_forecastList, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
    lv_obj_remove_flag(ui_forecastList, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_forecastList, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_forecastList, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_forecastList, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_forecastList, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui_forecastList, LV_BORDER_SIDE_TOP, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_forecastList, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_forecastList, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_forecastList, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_forecastList, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_row(ui_forecastList, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_column(ui_forecastList, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_forecastItem = lv_obj_create(ui_forecastList);
    lv_obj_set_width(ui_forecastItem, 59);
    lv_obj_set_height(ui_forecastItem, 70);
    lv_obj_set_x(ui_forecastItem, 67);
    lv_obj_set_y(ui_forecastItem, 26);
    lv_obj_set_align(ui_forecastItem, LV_ALIGN_CENTER);
    lv_obj_set_flex_flow(ui_forecastItem, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(ui_forecastItem, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_remove_flag(ui_forecastItem, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_border_width(ui_forecastItem, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_forecastItem, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_forecastItem, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_forecastItem, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_forecastItem, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_row(ui_forecastItem, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_column(ui_forecastItem, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_forecastIcon = lv_image_create(ui_forecastItem);
    lv_image_set_src(ui_forecastIcon, &ui_img_day_368_png);
    lv_obj_set_width(ui_forecastIcon, 32);
    lv_obj_set_height(ui_forecastIcon, 32);
    lv_obj_set_align(ui_forecastIcon, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_forecastIcon, LV_OBJ_FLAG_CLICKABLE);     /// Flags
    lv_obj_remove_flag(ui_forecastIcon, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_image_set_scale(ui_forecastIcon, 128);
    lv_obj_set_style_image_recolor(ui_forecastIcon, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_image_recolor_opa(ui_forecastIcon, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_forecastTemp = lv_label_create(ui_forecastItem);
    lv_obj_set_width(ui_forecastTemp, 51);
    lv_obj_set_height(ui_forecastTemp, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_forecastTemp, LV_ALIGN_CENTER);
    lv_label_set_long_mode(ui_forecastTemp, LV_LABEL_LONG_CLIP);
    lv_label_set_text(ui_forecastTemp, "24°C");
    lv_obj_set_style_text_align(ui_forecastTemp, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_forecastTemp, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_forecastTime = lv_label_create(ui_forecastItem);
    lv_obj_set_width(ui_forecastTime, 52);
    lv_obj_set_height(ui_forecastTime, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_forecastTime, LV_ALIGN_CENTER);
    lv_label_set_long_mode(ui_forecastTime, LV_LABEL_LONG_CLIP);
    lv_label_set_text(ui_forecastTime, "12:00");
    lv_obj_set_style_text_align(ui_forecastTime, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_forecastTime, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);

}

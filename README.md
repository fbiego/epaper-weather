# ePaper Weather

A project to display real-time weather data on a 240x416 ePaper display.

## Overview

This project uses an ESP32-based ePaper display to fetch and show weather data. The display updates hourly with the latest information retrieved from a weather API via WiFi.

## Features

- Fetches real-time weather data from [WeatherAPI](https://www.weatherapi.com/)
- Displays weather information on a 240x416 ePaper display
- Updates once every hour to show current conditions

## Requirements

1. ESP32 3.7" ePaper Display (240x416 resolution)
   - [`Elecrow ePaper Display`](https://www.elecrow.com/crowpanel-esp32-3-7-e-paper-hmi-display-with-240-416-resolution-black-white-color-driven-by-spi-interface.html)
2. WeatherAPI key
   - [Sign up for an API key](https://www.weatherapi.com/)
3. Set your location in the code for accurate weather data

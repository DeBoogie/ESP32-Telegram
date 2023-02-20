
# ESP32-Telegram

A simple wrapper for Telegram Bot **READ/SEND** operations.

## Installation

* Copy `Telegram.cpp`, `Telegram.h` and `ArduinoJson.h` alongside of your `main.cpp`
* **You can obtain `ArduinoJson.h` from https://arduinojson.org/v6/doc/installation/**
* Remember rename `ArduinoJson-vX.XX.X.h` to `ArduinoJson.h`

## Example
```
#include <Arduino.h>
#include <Telegram.h>
#include <WiFi.h>

String chatId = "1234567890";
Telegram::Telegram telegram("3412604351:ABFopWfkL1fKu5_KmGfaA5DbRM9Gjey7uxs");

void setup()
{
  Serial.begin(9600);

  WiFi.begin("IoT", "");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  telegram.sendMessage(chatId, "Starting up...");
}

void loop()
{
  vector<Telegram::Message> messages = telegram.readMessages();
  for (Telegram::Message message : messages)
  {
    Serial.println("[" + message.chat_id + "]: " + message.text);
  }

  delay(500);
}
```


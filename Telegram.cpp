/**
 * @file Telegram.cpp
 * @brief A minimal wrapper for sending and receiving messages from the Telegram API using an ESP32 board.
 *
 * A Simple way to send and receive messages from Telegram using an ESP32 board with internet connectivity.
 *
 * @author Eetu T. (DeBoogie)
 * @date 20/02/2023
 *
 * @see https://core.telegram.org/bots/api
 */

#include "Telegram.h"

using namespace std;

namespace Telegram
{
    HTTPClient http;
    int _offset = 0;

    Message::Message(String text, String chat_id)
    {
        this->text = text;
        this->chat_id = chat_id;
    }

    Telegram::Telegram(String token)
    {
        _token = token;
    }

    void Telegram::sendMessage(String chat_id, String text)
    {
        String url = _url + _token + "/sendMessage?chat_id=" + chat_id + "&text=" + text;
        _sendRequest(url);
    }

    String Telegram::_sendRequest(String url)
    {
        http.begin(url);
        int httpCode = http.GET();
        String payload = http.getString();
        http.end();

        return payload;
    }

    vector<Message> Telegram::readMessages(int timeout, int limit)
    {
        String url = _url + _token + "/getUpdates?timeout=" + timeout + "&limit=" + limit + "&offset=" + _offset;
        String response = _sendRequest(url);

        DynamicJsonDocument doc(1024);
        deserializeJson(doc, response);
        JsonObject obj = doc.as<JsonObject>();
        vector<Message> messages;

        if (obj["ok"] == true)
        {
            JsonArray result = obj["result"].as<JsonArray>();
            for (JsonObject update : result)
            {
                JsonObject message = update["message"].as<JsonObject>();
                String text = message["text"].as<String>();
                String chat_id = message["chat"]["id"].as<String>();
                _offset = update["update_id"].as<int>() + 1;
                messages.push_back(Message(text, chat_id));
            }
        }

        return messages;
    };
};
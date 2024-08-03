/**
 * @file Telegram.h
 * @brief A minimal wrapper for sending and receiving messages from the Telegram API using an ESP32 board.
 *
 * A Simple way to send and receive messages from Telegram using an ESP32 board with internet connectivity.
 *
 * @author Eetu T. (DeBoogie)
 * @date 20/02/2023
 *
 * @see https://core.telegram.org/bots/api
 */

#ifndef TELEGRAM_H
#define TELEGRAM_H

#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <vector>
#include <string>

namespace Telegram
{
    class Message
    {
    public:
        Message(String text, String chat_id);
        String text;
        String chat_id;
    };

    class Telegram
    {
    public:
        explicit Telegram(String token);
        void sendMessage(String chat_id, String text);
        std::vector<Message> readMessages(int timeout = 3, int limit = 100);

    private:
        String _token;
        const String _url = "https://api.telegram.org/bot";
        String _sendRequest(String url);
        int _offset = 0;
    };
};

#endif
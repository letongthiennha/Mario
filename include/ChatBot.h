#pragma once
#include "raylib.h"
#include <string>
#include <unordered_map>
#include <vector>

class ChatBot {
private:
    std::unordered_map<std::string, std::string> qa;

    ChatBot();

    static std::string ToLower(const std::string& str);
    int WordMatch(const std::string& a, const std::string& b);
    void LoadQA(const std::string& filename);

public:
    static ChatBot& GetInstance();

    ChatBot(const ChatBot&) = delete;
    void operator=(const ChatBot&) = delete;

    std::string Response(const std::string& input);
};
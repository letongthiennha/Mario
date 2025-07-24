#pragma once
#pragma once
#include "raylib.h"
#include "TextBox.h"
#include "ChatBot.h"
#include <string>
#include <vector>

class ChatBotScreen
{
public:
    ChatBotScreen(Rectangle bounds, Rectangle inputBox);
    void update();
    void draw();

private:
    Rectangle bounds;
    TextBox inputBox;
    Texture2D chatBotIcon;
	std::string responseText;
};
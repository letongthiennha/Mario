#include "ChatBotScreen.h"
#include "ResourceManager.h"
#include <iostream>
#include <sstream>

ChatBotScreen::ChatBotScreen(Rectangle bounds, Rectangle inputBox): bounds(bounds), inputBox(inputBox)
{
	chatBotIcon = ResourceManager::getInstance().getTexture("CHAT_BOT_ICON");
	if (chatBotIcon.id <= 0) {
		std::cout << "Warning: Failed to load texture for CHAT_BOT_ICON." << std::endl;
	}
	chatBotTitle = ResourceManager::getInstance().getTexture("CHAT_BOT_TITLE");
	if (chatBotTitle.id <= 0) {
		std::cout << "Warning: Failed to load texture for CHAT_BOT_TITLE." << std::endl;
	}
}

void ChatBotScreen::update() {
	inputBox.Update();

	if (IsKeyPressed(KEY_ENTER)) {
		std::string userInput = inputBox.GetText();
		if (!userInput.empty()) {
			responseText = ChatBot::GetInstance().Response(userInput);
			inputBox.Clear(); 
		}
		inputBox.setSelected(false);
	}
}

void ChatBotScreen::draw() {
	DrawRectangleRec(bounds, RAYWHITE);
	DrawRectangle(bounds.x, bounds.y, bounds.width, 80, LIGHTGRAY);
	DrawRectangleLinesEx(bounds, 2, DARKGRAY);
	DrawLine(bounds.x, bounds.y + 80, bounds.x + bounds.width, bounds.y + 80, DARKGRAY);

	// --- Title and Icon Drawing ---
	float iconSize = 48.0f;
	float padding = 10.0f;
	float headerHeight = 80.0f;

	if (chatBotTitle.id > 0) {
		// Calculate dimensions and positions for texture-based title
		float titleHeight = 60.0f; // Desired height for the title texture
		float titleWidth = ((float)chatBotTitle.width / (float)chatBotTitle.height) * titleHeight; // Maintain aspect ratio
		float totalWidth = titleWidth + padding + iconSize;
		float startX = bounds.x + (bounds.width - totalWidth) / 2;
		float titleY = bounds.y + (headerHeight - titleHeight) / 2;
		float iconY = bounds.y + (headerHeight - iconSize) / 2;

		// Draw title texture
		Rectangle titleSourceRec = { 0.0f, 0.0f, (float)chatBotTitle.width, (float)chatBotTitle.height };
		Rectangle titleDestRec = { startX, titleY, titleWidth, titleHeight };
		DrawTexturePro(chatBotTitle, titleSourceRec, titleDestRec, { 0, 0 }, 0.0f, WHITE);

		// Draw icon
		if (chatBotIcon.id > 0) {
			Rectangle iconSourceRec = { 0.0f, 0.0f, (float)chatBotIcon.width, (float)chatBotIcon.height };
			Rectangle iconDestRec = { startX + titleWidth + padding, iconY, iconSize, iconSize };
			DrawTexturePro(chatBotIcon, iconSourceRec, iconDestRec, { 0, 0 }, 0.0f, WHITE);
		}
	}

	if (!responseText.empty())
	{
		const Font& responseFont = ResourceManager::getInstance().getFonts("CHAT_BOT_FONT");
		float responseFontSize = 32.0f; // Increased font size
		float textPadding = 20.0f;
		float lineSpacing = 5.0f;
		float maxWidth = bounds.width - (2 * textPadding);
		float currentY = bounds.y + 100;

		std::vector<std::string> lines;
		std::string currentLine;
		std::stringstream ss(responseText);
		std::string word;

		while (ss >> word) {
			std::string tempLine = currentLine.empty() ? word : (currentLine + " " + word);
			if (MeasureTextEx(responseFont, tempLine.c_str(), responseFontSize, 1).x < maxWidth) {
				currentLine = tempLine;
			}
			else {
				lines.push_back(currentLine);
				currentLine = word;
			}
		}
		if (!currentLine.empty()) {
			lines.push_back(currentLine);
		}
		for (const auto& line : lines) {
			DrawTextEx(responseFont, line.c_str(), { bounds.x + textPadding, currentY }, responseFontSize, 1, BLACK);
			currentY += MeasureTextEx(responseFont, line.c_str(), responseFontSize, 1).y + lineSpacing;
		}
	}

	inputBox.Draw();
}
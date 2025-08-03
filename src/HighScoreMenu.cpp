#include "HighScoreScreenState.h"
#include "ResourceManager.h"
#include "GameClock.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>

HighScoreScreenState::HighScoreScreenState(StateManager* manager): State(manager),
backButton({ 20, 20 }, { 64, 64 })
{
	backgroundTexture = ResourceManager::getInstance().getTexture("SB_BACKGROUND_1");

	backButton.setTextures(ResourceManager::getInstance().getTexture("HOME_BUTTON_RELEASE"),
		ResourceManager::getInstance().getTexture("HOME_BUTTON_PRESS"));

	readGameInfosFromFile("saves/scores.txt");
}

HighScoreScreenState::~HighScoreScreenState() {

}

void HighScoreScreenState::update() {
	backButton.update();
	if (backButton.isClicked()) {
		stateManager->goBack();
	}

	updateBackground();
}

void HighScoreScreenState::draw() {
	DrawTexturePro(backgroundTexture, 
		{ 0, 0, (float)backgroundTexture.width, (float)backgroundTexture.height },
		{ 0, 0, (float)GetScreenWidth(), (float)GetScreenHeight() }, { 0, 0 }, 0.0f, WHITE);
	backButton.Draw();
	drawScores();
}

void HighScoreScreenState::updateBackground() {
	backgroundAcumulationTime += GameClock::getInstance().DeltaTime;

	if (backgroundAcumulationTime > backgroundSpeed) {
		backgroundAcumulationTime = 0.0f;
		backgroundFrame = (backgroundFrame + 1) % 4;
		backgroundTexture = ResourceManager::getInstance().getTexture("SB_BACKGROUND_" + std::to_string(backgroundFrame + 1));
	}
}

void HighScoreScreenState::readGameInfosFromFile(const std::string& filePath) {
	std::ifstream file(filePath);
	if(file.is_open()) {
		std::string line;
		GameInfo info;
		while (std::getline(file, line)) {
			std::stringstream ss(line);
			if (ss >> info.date >> info.time >> info.scores[0] >> info.scores[1] >> info.scores[2] >> info.scores[3]) {
				gameInfos.push_back(info);
				std::cout<< "Read game info: " << info.date << " " << info.time << " " 
					<< info.scores[0] << " " << info.scores[1] << " " 
					<< info.scores[2] << " " << info.scores[3] << std::endl;
			}
		}
		stable_sort(gameInfos.begin(), gameInfos.end());
		reverse(gameInfos.begin(), gameInfos.end());
		file.close();
	} else {
		// Handle file not found or error
		std::cerr << "Error opening file: " << filePath << std::endl;
	}
}

void HighScoreScreenState::drawScores() {
	Font titleFont = ResourceManager::getInstance().getFonts("SETTING_FONT");
	Font infoFont = ResourceManager::getInstance().getFonts("CHAT_BOT_TITLE_FONT");

	// Layout setup
	const float boardWidth = 1200.0f;
	const float boardStartX = (GetScreenWidth() - boardWidth) / 2;  // center horizontally
	const float boardEndX = boardStartX + boardWidth;

	const int numColumns = 7; // Rank, Date, Time, Map1, Map2, Map3, Total
	const float columnWidth = boardWidth / numColumns;

	const float headerY = 250.0f; 
	const float rowHeight = 40.0f;

	// Column titles
	const std::string headers[] = { "Rank", "Date", "Time", "Map 1", "Map 2", "Map 3", "Total" };

	// Draw headers
	for (int i = 0; i < numColumns; ++i) {
		float centerX = boardStartX + i * columnWidth + columnWidth / 2;
		Vector2 textSize = MeasureTextEx(titleFont, headers[i].c_str(), 20, 2);
		DrawTextEx(titleFont, headers[i].c_str(),
			{ centerX - textSize.x / 2, headerY },
			20, 2, BLACK);
	}

	// Draw score rows
	int rank = 1;
	float yPos = headerY + rowHeight;
	for (const auto& info : gameInfos) {
		const auto& scores = info.getScores();
		if (scores.size() >= 4) {
			std::string values[] = {
				std::to_string(rank),
				info.getDate(),
				info.getTime(),
				std::to_string(scores[0]),
				std::to_string(scores[1]),
				std::to_string(scores[2]),
				std::to_string(scores[3]) // assuming total
			};

			for (int i = 0; i < numColumns; ++i) {
				float centerX = boardStartX + i * columnWidth + columnWidth / 2;
				Vector2 textSize = MeasureTextEx(infoFont, values[i].c_str(), 20, 2);
				DrawTextEx(infoFont, values[i].c_str(),
					{ centerX - textSize.x / 2, yPos },
					20, 2, BLACK);
			}

			rank++;
			if (rank == 11) break; // Limit to top 10 score
			yPos += rowHeight;
		}
	}
}

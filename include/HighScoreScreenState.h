#pragma once
#include "State.h"
#include "MenuState.h"
#include "Button2.h"
#include <string>
#include <vector>

class GameInfo {
public:
	GameInfo(const std::string& date, const std::string& time, const std::vector<int>& scores)
		: date(date), time(time), scores(scores) {}
	GameInfo() : date(""), time(""), scores(4, 0) {} // Default constructor initializes scores to 0
	const std::string& getDate() const { return date; }
	const std::string& getTime() const { return time; }
	const std::vector<int>& getScores() const { return scores; }
	void setDate(const std::string& newDate) { date = newDate; }
	void setTime(const std::string& newTime) { time = newTime; }
	void setScores(const std::vector<int>& newScores) { scores = newScores; }
	bool operator < (const GameInfo& other) const {
		if(scores[3]!= other.scores[3]) {
			return scores[3] < other.scores[3]; // Compare by the fourth score
		}
		if(scores[2] != other.scores[2]) {
			return scores[2] < other.scores[2]; // Compare by the third score
		}
		if(scores[1] != other.scores[1]) {
			return scores[1] < other.scores[1]; // Compare by the second score
		}
		if(scores[0] != other.scores[0]) {
			return scores[0] < other.scores[0]; // Compare by the first score
		}
		return true;
	}
private:
	std::string date;
	std::string time;
	std::vector<int> scores;
	friend class HighScoreScreenState; // Allow HighScoreScreenState to access private members
};

class HighScoreScreenState : public State {
public:
	HighScoreScreenState(StateManager* manager);
	~HighScoreScreenState();

	void update() override;
	void draw() override;
	void updateBackground();
	void drawScores();

	void readGameInfosFromFile(const std::string& filePath);
private:
	Button2 backButton;
	Texture2D backgroundTexture;

	float backgroundAcumulationTime = 0.0f;
	float backgroundSpeed = 0.3f;
	int backgroundFrame = 0;

	std::vector<GameInfo> gameInfos;
};
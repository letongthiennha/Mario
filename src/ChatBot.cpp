#include "ChatBot.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>

ChatBot::ChatBot() {
    LoadQA("resources/ChatBot/chat.txt");
}

ChatBot& ChatBot::GetInstance() {
    static ChatBot instance;
    return instance;
}

std::string ChatBot::ToLower(const std::string& str) {
    std::string res;
    for (char c : str) {
        res += std::tolower(static_cast<unsigned char>(c));
    }
    return res;
}

int ChatBot::WordMatch(const std::string& a, const std::string& b) {
    std::istringstream issA(ToLower(a)), issB(ToLower(b));
    std::vector<std::string> wordsA, wordsB;
    std::string word;
    while (issA >> word) wordsA.push_back(word);
    while (issB >> word) wordsB.push_back(word);
    int matches = 0;
    for (const auto& wa : wordsA) {
        for (const auto& wb : wordsB) {
            if (wb.find(wa) != std::string::npos) {
                ++matches;
            }
        }
    }
    return matches;
}

void ChatBot::LoadQA(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;
    while (getline(file, line)) {
        size_t sep = line.find('|');
        if (sep != std::string::npos) {
            std::string question = line.substr(0, sep);
            std::string answer = line.substr(sep + 1);
            qa[ToLower(question)] = answer;
        }
    }
}

std::string ChatBot::Response(const std::string& input) {
    int maxMatch = 0;
    std::string best = "I don't understand.";

    for (const auto& [q, a] : qa) {
        int score = WordMatch(input, q);
        if (score > maxMatch) {
            maxMatch = score;
            best = a;
        }
    }
    return best;
}
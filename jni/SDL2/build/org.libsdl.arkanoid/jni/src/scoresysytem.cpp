#include "include/scoresysytem.h"

int ToInt(std::string str) {

    int num;

    std::istringstream stream(str);
    stream >> num;

    return num;
}

ScoreSystem::ScoreSystem() {

    bestScore    = 0;
    currentScore = 0;
}

ScoreSystem::~ScoreSystem() {

    if (!SaveBestScore()) {

        std::cout << "Error: Cannot save bestscore (ScoreSystem)" << std::endl;
    }
}

void ScoreSystem::IncreaseCurrentScore(BrickType type) {

    if (type == type1) {

        currentScore += 1;
    }
    else if (type == type2) {

        currentScore += 2;
    }
    else if (type == type3) {

        currentScore += 3;
    }

    if (currentScore > bestScore) {

        bestScore = currentScore;
    }
}

bool ScoreSystem::LoadBestScore() {

    std::fstream file;

    file.open(pathToScoreFile.c_str(), std::fstream::in);

    if (!file.is_open()) {

        return false;
    }

    std::string line;

    while (std::getline(file, line)) {

        if (line.find("bestscore:") != std::string::npos) {

            std::string score = line.substr((line.find("bestscore:") + 10), line.size() -  10);

            bestScore = ToInt(score);

            return true;
        }
    }

    return false;
}

bool ScoreSystem::SaveBestScore() {


    std::remove(pathToScoreFile.c_str());

    std::ofstream file(pathToScoreFile.c_str());

    file << "bestscore:" + std::to_string(bestScore);

    return true;
}


bool ScoreSystem::Init(std::string pathToScoreFile) {

    this->pathToScoreFile = pathToScoreFile;

    if (!LoadBestScore()) {

        return false;
    }

    return true;
}

void ScoreSystem::ResetCurrentScore() {

    currentScore = 0;
}

void ScoreSystem::Save() {

    if (!SaveBestScore()) {

        std::cout << "Error: Cannot save bestscore (ScoreSystem)" << std::endl;
    }
}

unsigned ScoreSystem::GetBestScore() {

    return bestScore;
}

unsigned ScoreSystem::GetCurrentScore() {

    return currentScore;
}

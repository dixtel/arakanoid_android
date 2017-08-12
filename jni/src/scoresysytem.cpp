#include "include/scoresysytem.h"

template <typename T>
std::string to_string(T value)
{
    std::ostringstream os ;
    os << value ;
    return os.str() ;
}

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
        
        SDL_Log("Error: Cannot save bestscore (ScoreSystem)");
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

    const char *base_path = SDL_AndroidGetInternalStoragePath();

    std::string final_path;

    final_path.append(base_path);
    final_path.append("/");
    final_path.append(scoreFile);

    File file(final_path);

    std::string line = file.GetData();

    if (line.find("bestscore:") != std::string::npos) {

        std::string score = line.substr((line.find("bestscore:") + 10), line.size() -  10);

        bestScore = ToInt(score);

        return true;
    }

    return false;
}

bool ScoreSystem::SaveBestScore() {

   const char *base_path = SDL_AndroidGetInternalStoragePath();

    std::string final_path;

    final_path.append(base_path);
    final_path.append("/");
    final_path.append(scoreFile);

    File file(final_path);

    if (!file.WriteData("bestscore:" + to_string(bestScore))) {

        return false;
    }

    return true;
}


bool ScoreSystem::Init(std::string scoreFile) {

    this->scoreFile = scoreFile;

    if (!LoadBestScore()) {

        return false;
    }

    return true;
}

void ScoreSystem::ResetCurrentScore() {

    currentScore = 0;
}

void ScoreSystem::Save() {

    if (currentScore >= bestScore) {

        if (!SaveBestScore()) {

            SDL_Log("Error: Cannot save bestscore (ScoreSystem)");
        }
    }
}

unsigned ScoreSystem::GetBestScore() {

    return bestScore;
}

unsigned ScoreSystem::GetCurrentScore() {

    return currentScore;
}

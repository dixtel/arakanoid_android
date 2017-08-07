#ifndef SCORESYSTEM_H
#define SCORESYSTEM_H

#include <SDL.h>

#include "include/brick.h"

#include <string>
#include <fstream>
#include <sstream>


class ScoreSystem {

    friend class BrickManager;

    void IncreaseCurrentScore(BrickType type);

protected:

    std::string pathToScoreFile;

    unsigned bestScore;
    unsigned currentScore;

    bool LoadBestScore();
    bool SaveBestScore();
public:

    ScoreSystem();
    ~ScoreSystem();

    bool Init(std::string pathToScoreFile);
    void ResetCurrentScore();
    void Save();

    unsigned GetBestScore();
    unsigned GetCurrentScore();
};

#endif // SCORESYSTEM_H

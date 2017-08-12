#ifndef PLAYER_H
#define PLAYER_H

#include <SDL.h>

#include "include/fileread.h"
#include "include/filewrite.h"


class File {

    std::string path;
public:

    File(const std::string path);

    bool WriteData(const std::string data);

    std::string GetData();
};

#endif // PLAYER_H

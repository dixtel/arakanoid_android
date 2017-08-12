#ifndef FILEREAD_H
#define FILEREAD_H

#include <SDL.h>

#include "include/logerror.h"

class FileRead {

public:

    FileRead();
    
    std::string GetData(const std::string path);
};

#endif // FILEREAD_H
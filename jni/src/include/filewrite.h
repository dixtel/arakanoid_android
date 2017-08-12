#ifndef FILEWRITE_H
#define FILEWRITE_H

#include <SDL.h>

#include "include/logerror.h"


class FileWrite {

public:

    FileWrite();

    bool Write(const std::string path, const std::string data);
};


#endif // FILEWRITE_H
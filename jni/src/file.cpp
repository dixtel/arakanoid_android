#include "include/file.h"

File::File(const std::string path) {

	this->path = path;
}

bool File::WriteData(const std::string data) {

    FileWrite file;

    if (!file.Write(path, data)) {

        std::string msg("Error Write ");
        msg.append(path.c_str());

        SDL_Log("%s", msg.c_str());

        return false;
    }

    return true;
}

std::string File::GetData() {

    FileRead file;
    
    std::string data = file.GetData(path);

    if (data == "") {

    	std::string msg("Error GetData ");
        msg.append(path.c_str());

        SDL_Log("%s", msg.c_str());
    }

    return data;
}
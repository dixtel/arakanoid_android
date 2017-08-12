#include "include/filewrite.h"

FileWrite::FileWrite() {

}

bool FileWrite::Write(const std::string path, const std::string data) {

    SDL_RWops *io = SDL_RWFromFile(path.c_str(), "wb");

    if (io == NULL) {

        PrintError("SDL_RWFromFile path:" + path + " (FileWrite)");
        return false;
    }

    size_t data_len = SDL_strlen(data.c_str());

    if (SDL_RWwrite(io, data.c_str(), 1, data_len) != data_len) {

        PrintError("SDL_RWwrite");
        SDL_RWclose(io);
        return false;
    }

    SDL_RWclose(io);

    return true;
}
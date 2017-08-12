#include "include/fileread.h"

FileRead::FileRead() {

}
    
std::string FileRead::GetData(const std::string path) {
    
    SDL_RWops *io = SDL_RWFromFile(path.c_str(), "rb");

    if (io == NULL) {

        PrintError("SDL_RWFromFile path:" + path + " (FileRead)");
        return "";
    }

    size_t file_size = SDL_RWsize(io);

    char buffor[file_size];

    if (SDL_RWread(io, buffor, 1, file_size) == 0) {

        PrintError("SDL_RWread");
        SDL_RWclose(io);
        return "";
    }

    SDL_RWclose(io);

    return buffor;
}
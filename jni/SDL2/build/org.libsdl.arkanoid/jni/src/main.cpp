#include "include/game.h"
#include "include/logsdlerror.h"

#include <string>
#include <sstream>

const unsigned WINDOW_WIDTH = 640;
const unsigned WINDOW_HEIGHT = 960;
const std::string WINDOW_TITLE = "Arkanoid";


int main(int argv, char ** args) {
    Game game(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);

    if (!game.InitSDL()) {

        LogSDLError(std::cout, "InitSDL");
        return 1;
    }

    if (!game.InitGame()) {

        LogSDLError(std::cout, "InitGame");
        return 1;
    }

    if (!game.InitStates()) {

        LogSDLError(std::cout, "InitStates");
        return 1;
    }

    game.Start();

    return 0;
}

//#include <iostream>
//#include <sstream>

//int main () {

//    std::string line = "1 2 3 4 5";
//    std::string type;
//    std::stringstream stream;
//    stream << line;

//    while (stream >> type) {
//        std::cout << type << std::endl;
//    }

//    return 0;
//}

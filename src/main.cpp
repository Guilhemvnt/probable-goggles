/*
** probable-goggles
** File description:
** main
*/

#include "soft.hpp"

//to remove if no use
volatile bool shouldExit = false;
//to remove if no use
void signalHandler(int signum) {
    if (signum == SIGINT) {
        shouldExit = true;
    }
}

// <bool writeData(std::ostringstream &logLine)
// {
//     std::ofstream outputFile("logs/test.txt", std::ios::app | std::ios::out);
//     if (!outputFile.is_open()) {
//         std::cout << "Failed to open the output file." << std::endl;
//         shouldExit = true;
//         return false;
//     }
//     outputFile.close();
//     return true;
// }>

int startingUp()
{
    NcursesGUI ncursesGUI;
    ncursesGUI.init();
    while (true) {
        ncursesGUI.draw();
        //use it at the end always
        if(ncursesGUI.handleInput() == 1)
            break;
    
    }
    ncursesGUI.close();
    return 0;
}

int main() 
{
    startingUp();
    return 0;
}

#include "menu.h"

using namespace std;

int main()
{
    Menu mainMenu("MainMenu", {"Create", "Block", "WakeUp", "Stop"
        , "Show", "SwitchAlgorithm"});
    mainMenu.Run();
    return 0;
}
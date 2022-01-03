#include "menu.h"

using namespace std;

int main()
{
    Menu mainMenu("MainMenu", {"Allocate", "Free", "Show"});
    mainMenu.Run();
    return 0;
}
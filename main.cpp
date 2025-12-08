///////START OF main.cpp //////
/*
BRUTUS BOUNCE
for copyright purposes this game is basically a reskin of doodle jump so dont publish it
(though we did add a feature that doodle jump does not have so points for us because they have 25 games so you would think theyve thought of everything)

Coded by Ben Coughlin and Art by Sophie Subit for FEH SDP
Professor - Adithya Jayakumar
Class time - 12:40

Code started - November 21st 2025
Code Finished - December 7th 2025


*/

#include "Game.h"
#include <windows.h>
#include <iostream>
//#include "game_assets.h"

int main()
{
    //game is pretty demanding computationally so give it access to as much ram as it wants
    if (!SetPriorityClass(GetCurrentProcess(), HIGH_PRIORITY_CLASS)) {
        std::cout << "Priority could not be set\n";
    }
    //create a object of game which will house eveyrhting included in this game
    Game game;
    //pull up the menu
    game.Menu();
    return 0;
}


////////END OF main.cpp///////

#include "Game.h"
#include <iostream>

//Main function
int main(){
	Game game;
	game.run();
	return 0;
}

/*
+ Clearly structure code
+ Everything works as it should
+ Reasonably incapsulated (excluding the fact that the program doesn't use very many setter functions)
+ Settings changing affects game but doesn't break it 
(ex. you can change the setting for ship velocity by changing one value without having to change anything else)

- Constructors for gameobjects are very long/complicated
- Game class is a god class
- Could be made more efficient with abstraction
- mLevel variable in game class is currrently not being used for anything but to show how many coins you've picked up in the console

^ Create a baseclass for gameobjects (this could also simplify the constructors for gameobjects)
^ Create classes for resource management and other game functions (such as collision and window handling) to relieve the Game class
^ Make it so that the level you're on (how many coins you've picked up) shows up as a number in the renderwindow for the game

*/
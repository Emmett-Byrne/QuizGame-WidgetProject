/// <summary>
/// @authors:
///		Emmett Byrne
///		Przemyslaw Tomczyk
/// 
/// @brief:
///		A simple program that has ui for future reusability
///		featue: keeps game progress if you return to the main menu in the middle of a quiz
/// 
/// @bug:
///		No known bugs
/// </summary>

#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#endif 


#pragma comment(lib,"libyaml-cppmdd") 
#include "Game.h"

/// <summary>
/// main enrtry point
/// </summary>
/// <returns>true</returns>
int main()
{
	Game game;
	game.run();

	return 1;
}
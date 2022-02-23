/// <summary>
/// @authors:
///		Emmett Byrne
///		Przemyslaw Tomczyk
/// 
/// @brief:
///		A simple program that has ui for future reusability
/// 
/// @bug:
///		No known bugs
/// </summary>

#ifndef GAME
#define GAME

#include "Frame.h"
#include <SFML/Graphics.hpp>
#include "VLayout.h"
#include "TextButton.h"
#include "button.h"
#include "CheckButton.h"
#include "RadioButton.h"
#include "Slider.h"
#include "XBOX360CONTROLLER.h"

#include "States.h"

#include "MainMenu.h"
#include "OptionMenu.h"
#include "HighscoreMenu.h"
#include "SplashScreen.h"
#include "LicenseScreen.h"
#include "GameScreen.h"
#include "StoryScreen.h"
#include "CreditsScreen.h"

class Game
{
public:
	Game();
	~Game();
	/// <summary>
	/// main method for game
	/// </summary>
	void run();

private:
	void processEvents();
	void update(sf::Time t_deltaTime);
	void render();
	
	sf::RenderStates state;
	sf::RenderWindow m_window; // main SFML window
	sf::Font m_ArialBlackfont; // font used by message
	bool m_exitGame; // control exiting game

	Menu m_currentMenu;
	bool m_changingMenu;

	StoryScreen m_storyScreen;
	SplashScreen m_splashScreen;
	LicenseScreen m_licenseScreen;
	MainMenu m_mainMenu;
	OptionMenu m_optionMenu;
	HighscoreMenu m_highMenu;
	CreditsScreen m_creditsScreen;
	GameScreen m_gameScreen;

	Xbox360Controller m_controller;

	Options m_options;
};

#endif // !GAME


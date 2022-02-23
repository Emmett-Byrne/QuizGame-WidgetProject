#include "Game.h"
#include <iostream>

Game::Game() :
	m_window{ sf::VideoMode{ 1200, 900, 32 }, "SFML Game" },
	m_exitGame{ false }, //when true game will exit
	m_currentMenu(Menu::StateCutscene),
	m_storyScreen(m_currentMenu),
	m_splashScreen(m_currentMenu),
	m_licenseScreen(m_currentMenu),
	m_mainMenu(m_ArialBlackfont, m_window, m_currentMenu, m_options),
	m_optionMenu(m_ArialBlackfont, m_window, m_currentMenu, m_options),
	m_highMenu(m_ArialBlackfont, m_window, m_currentMenu, m_options),
	m_gameScreen(m_ArialBlackfont, m_window, m_currentMenu, m_options),
	m_creditsScreen(m_ArialBlackfont, m_window, m_currentMenu, m_options)
{
	if (!m_ArialBlackfont.loadFromFile("ASSETS\\FONTS\\ariblk.ttf"))
	{
		std::cout << "problem loading arial black font" << std::endl;
	}

	m_options.musicVol = 100;
	m_options.soundVol = 100;
	m_options.mute = false;
	m_options.animSpeed = 50;
	m_options.fontSize = 2;

}


Game::~Game()
{
}


void Game::run()
{

	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Time timePerFrame = sf::seconds(1.f / 60.f); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
		}
		render(); // as many as possible
	}
}

/// <summary>
/// handle user and system events/ input
/// get key presses/ mouse moves etc. from OS
/// and user :: Don't do game update here
/// </summary>
void Game::processEvents()
{
	sf::Event event;
	m_controller.update();

	switch (m_currentMenu)
	{
	case Menu::StateSplash:
		m_splashScreen.processEvents(m_controller);
		break;
	case Menu::StateLicense:
		//m_licenseScreen.processEvents(m_controller);
		break;
	case Menu::StateMainMenu:
		m_mainMenu.processEvents(m_controller);
		break;
	case Menu::StateOptions:
		m_optionMenu.processEvents(m_controller);
		break;
	case Menu::StateQuiz:
		m_gameScreen.processEvents(m_controller);
		break;
	case Menu::StateHighScore:
		m_highMenu.processEvents(m_controller);
		break;
	case Menu::StateCredits:
		m_creditsScreen.processEvents(m_controller);
		break;
	default:
		break;
	}
	
	while (m_window.pollEvent(event))
	{
		if ( sf::Event::Closed == event.type) // window message
		{
			m_window.close();
		}

		if (sf::Event::KeyPressed == event.type) //user key press
		{
			if (sf::Keyboard::Escape == event.key.code)
			{
				m_exitGame = true;
			}
		}

		if (m_currentMenu == Menu::StateQuiz)
		{
			//m_gameScreen.processEvents(m_controller, event);
		}
	}
}

/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame)
	{
		m_window.close();
	}

	switch (m_currentMenu)
	{
	case Menu::StateCutscene:
		m_storyScreen.update(t_deltaTime);
		m_changingMenu = m_storyScreen.getChengeMenu();
		m_storyScreen.resetChangeMenu();
		break;
	case Menu::StateSplash:
		if (m_changingMenu)
		{
			m_splashScreen.transitionIn();
		}
		m_splashScreen.update(t_deltaTime);
		m_changingMenu = m_splashScreen.getChengeMenu();
		m_splashScreen.resetChangeMenu();
		break;
	case Menu::StateLicense:
		if (m_changingMenu)
		{
			m_licenseScreen.transitionIn();
		}
		m_licenseScreen.update(t_deltaTime);
		m_changingMenu = m_licenseScreen.getChengeMenu();
		m_licenseScreen.resetChangeMenu();
		break;
	case Menu::StateMainMenu:
		if (m_changingMenu)
		{
			m_mainMenu.transitionIn();
		}
		m_mainMenu.update(t_deltaTime);
		m_changingMenu = m_mainMenu.getChengeMenu();
		m_mainMenu.resetChangeMenu();
		break;
	case Menu::StateOptions:
		if (m_changingMenu)
		{
			m_optionMenu.transitionIn();
		}
		m_optionMenu.update(t_deltaTime);
		m_changingMenu = m_optionMenu.getChangeMenu();
		m_optionMenu.resetChangeMenu();
		break;
	case Menu::StateQuiz:
		if (m_changingMenu)
		{
			m_gameScreen.transitionIn();
		}
		m_gameScreen.update(t_deltaTime);
		m_changingMenu = m_gameScreen.getChangeMenu();
		m_gameScreen.resetChangeMenu();
		break;
	case Menu::StateHighScore:
		if (m_changingMenu)
		{
			m_highMenu.transitionIn();
		}
		m_highMenu.update(t_deltaTime);
		m_changingMenu = m_highMenu.getChengeMenu();
		m_highMenu.resetChangeMenu();
		break;
	case Menu::StateCredits:
		if (m_changingMenu)
		{
			m_creditsScreen.transitionIn();
		}
		m_creditsScreen.update(t_deltaTime);
		m_changingMenu = m_creditsScreen.getChengeMenu();
		m_creditsScreen.resetChangeMenu();
		break;
	case Menu::StateQuit:
		m_exitGame = true;
		break;
	default:
		break;
	}
}

/// <summary>
/// draw the frame and then switch bufers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::Black);
	switch (m_currentMenu)
	{
	case StateCutscene:
		m_storyScreen.render(m_window);
		break;

	case StateSplash:
		m_splashScreen.render(m_window);
		break;

	case StateLicense:
		m_licenseScreen.render(m_window);
		break;

	case StateMainMenu:
		m_mainMenu.render(m_window);
		break;

	case StateOptions:
		m_optionMenu.render(m_window);
		break;

	case StateQuiz:
		m_gameScreen.render(m_window);
		break;

	case StateHighScore:
		m_highMenu.render(m_window);
		break;

	case StateCredits:
		m_creditsScreen.render(m_window);
		break;

	default: 
		break;
	}
	m_window.display();
}
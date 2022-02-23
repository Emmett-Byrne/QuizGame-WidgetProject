#include "MainMenu.h"



MainMenu::MainMenu(sf::Font & font, sf::RenderWindow & window, Menu & state, Options & options) :
	m_title("Main Menu", font),
	m_mainMenu(window),
	m_state(state),
	m_options(options)
{
	initGui();
	m_transitionTotalTime = sf::seconds(2);

	sf::Transform temp;
	temp.translate(0, -1200);
	m_renderState.transform = temp;
}


MainMenu::~MainMenu()
{
}

void MainMenu::initGui()
{
	if (!m_ArialBlackfont.loadFromFile("ASSETS\\FONTS\\ariblk.ttf"))
	{
		std::cout << "problem loading arial black font" << std::endl;
	}

	//initialising all the pointers to actual buttons
	m_Play = new TextButton("Play", m_ArialBlackfont, 280);
	m_OptionsButton = new TextButton("Options", m_ArialBlackfont, 280);
	m_HighScore = new TextButton("High Score", m_ArialBlackfont, 280);
	m_Credits = new TextButton("Credits", m_ArialBlackfont, 280);
	m_Quit = new TextButton("Quit", m_ArialBlackfont, 280);

	//setting their size
	m_Play->setCharacterSize(15);
	m_OptionsButton->setCharacterSize(15);
	m_HighScore->setCharacterSize(15);
	m_Credits->setCharacterSize(15);
	m_Quit->setCharacterSize(15);

	//setting the strings that will be returned on a button input
	m_Play->setDown("options");
	m_Play->setA("playmenu");

	m_OptionsButton->setUp("play");
	m_OptionsButton->setDown("highscore");
	m_OptionsButton->setA("optionsmenu");

	m_HighScore->setUp("options");
	m_HighScore->setDown("credits");
	m_HighScore->setA("highscoremenu");

	m_Credits->setUp("highscore");
	m_Credits->setDown("quit");
	m_Credits->setA("creditsmenu");

	m_Quit->setUp("credits");
	m_Quit->setA("quitmenu");

	//adding the buttons to the layout
	VLayout* layout = new VLayout;
	layout->setSpace(25);
	layout->add(m_Play);
	layout->add(m_OptionsButton);
	layout->add(m_HighScore);
	layout->add(m_Credits);
	layout->add(m_Quit);

	m_mainMenu.setLayout(layout);

	//setting the current selected widget
	m_selected = m_Play;
	m_selected->select(); //this just changes the colour of the selected button so that you can see that it's been selected
}

//takes in a string and does something based on the string
void MainMenu::messageHandler(std::string s)
{
	if (s == "play")
	{
		m_selected->deselect(); //changes colour back to default
		m_selected = m_Play; //changes the currently selected widget to this
		m_selected->select(); //changes the colour so that it looks like it's selected
		std::cout << "play" << std::endl;
	}

	if (s == "options")
	{
		m_selected->deselect();
		m_selected = m_OptionsButton;
		m_selected->select();
		std::cout << "options" << std::endl;
	}

	if (s == "highscore")
	{
		m_selected->deselect();
		m_selected = m_HighScore;
		m_selected->select();
		std::cout << "highscore" << std::endl;
	}

	if (s == "credits")
	{
		m_selected->deselect();
		m_selected = m_Credits;
		m_selected->select();
		std::cout << "credits" << std::endl;
	}

	if (s == "quit")
	{
		m_selected->deselect();
		m_selected = m_Quit;
		m_selected->select();
		std::cout << "quit" << std::endl;
	}

	if (s == "playmenu")
	{
		//pass in a reference to the current manu state and change it to PlayMenu
		transitionOut(Menu::StateQuiz);
	}

	if (s == "optionsmenu")
	{
		transitionOut(Menu::StateOptions);
	}

	if (s == "highscoremenu")
	{
		transitionOut(Menu::StateHighScore);
	}

	if (s == "creditsmenu")
	{
		transitionOut(Menu::StateCredits);
	}

	if (s == "quitmenu")
	{
		transitionOut(Menu::StateQuit);
	}
}

void MainMenu::processEvents(Xbox360Controller & pad)
{

	if (!m_transitionIn && !m_transitionOut)
	{
		if (pad.m_currentState.DpadUp && !pad.m_previousState.DpadUp)
		{
			messageHandler(m_selected->getUp()); //returns a string 
		}
		if (pad.m_currentState.DpadDown && !pad.m_previousState.DpadDown)
		{
			messageHandler(m_selected->getDown());
		}
		if (pad.m_currentState.DpadLeft && !pad.m_previousState.DpadLeft)
		{
			messageHandler(m_selected->getLeft());
		}
		if (pad.m_currentState.DpadRight && !pad.m_previousState.DpadRight)
		{
			messageHandler(m_selected->getRight());
		}
		if (pad.m_currentState.A && !pad.m_previousState.A ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			messageHandler(m_selected->getA());
		}
	}
}

void MainMenu::update(sf::Time t_deltaTime)
{
	m_Play->setCharacterSize(m_options.fontSize * 5 + 10);
	m_OptionsButton->setCharacterSize(m_options.fontSize * 5 + 10);
	m_HighScore->setCharacterSize(m_options.fontSize * 5 + 10);
	m_Credits->setCharacterSize(m_options.fontSize * 5 + 10);
	m_Quit->setCharacterSize(m_options.fontSize * 5 + 10);

	double scaler;
	if (m_transitionIn || m_transitionOut)
	{
		m_transitionTime -= t_deltaTime;
		scaler = t_deltaTime.asSeconds() / (m_transitionTotalTime.asSeconds() / 100 * m_options.animSpeed);

		
	}

	if (m_transitionIn)
	{
		m_renderState.transform.translate(sf::Vector2f(0, scaler * 1200));

		if (m_transitionTime.asSeconds() < 0)
		{
			m_transitionIn = false;

			m_renderState = sf::Transform();
		}
	}

	if (m_transitionOut)
	{
		m_renderState.transform.translate(sf::Vector2f(0, scaler * -1200));
		if (m_transitionTime.asSeconds() < 0)
		{
			m_transitionOut = false;
			m_state = m_nextState;
			m_changeMenu = true;
		}
	}
}

void MainMenu::render(sf::RenderWindow & window)
{
	window.draw(m_title, m_renderState);
	window.draw(m_mainMenu, m_renderState);
}

void MainMenu::transitionIn()
{
	m_selected->deselect();
	m_selected = m_Play;
	m_selected->select();

	sf::Transform temp;
	temp.translate(0, -1200);
	m_renderState.transform = temp;

	m_transitionIn = true;

	m_transitionTime = sf::seconds(m_transitionTotalTime.asSeconds() / 100 * m_options.animSpeed);
}

void MainMenu::transitionOut(Menu s)
{
	m_transitionOut = true;
	m_transitionTime = sf::seconds(m_transitionTotalTime.asSeconds() / 100 * m_options.animSpeed);

	m_nextState = s;
}

bool MainMenu::getChengeMenu()
{
	return m_changeMenu;
}

void MainMenu::resetChangeMenu()
{
	m_changeMenu = false;
}

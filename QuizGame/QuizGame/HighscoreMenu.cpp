#include "HighscoreMenu.h"



HighscoreMenu::HighscoreMenu(sf::Font & t_font, sf::RenderWindow & t_window, Menu & state, Options & options) :
	m_title("Highscores", t_font),
	m_highscoreMenu(t_window),
	m_state(state),
	m_options(options),
	m_score1("", t_font),
	m_score2("", t_font),
	m_score3("", t_font),
	m_score4("", t_font),
	m_score5("", t_font)
{
	m_score1.setPosition(500, 200);
	m_score2.setPosition(500, 250);
	m_score3.setPosition(500, 300);
	m_score4.setPosition(500, 350);
	m_score5.setPosition(500, 400);

	initGui();
	m_transitionTotalTime = sf::seconds(2);

	sf::Transform temp;
	temp.translate(0, -1200);
	m_renderState.transform = temp;

	m_scoreData[0].name = "dan";
	m_scoreData[1].name = "kwl";
	m_scoreData[2].name = "bru";
	m_scoreData[3].name = "dud";
	m_scoreData[4].name = "ayy";

	m_scoreData[0].score = 30;
	m_scoreData[1].score = 20;
	m_scoreData[2].score = 20;
	m_scoreData[3].score = 10;
	m_scoreData[4].score = 0;

	m_scoreData[0].day = 11;
	m_scoreData[1].day = 12;
	m_scoreData[2].day = 20;
	m_scoreData[3].day = 2;
	m_scoreData[4].day = 25;

	m_scoreData[0].month = 7;
	m_scoreData[1].month = 7;
	m_scoreData[2].month = 7;
	m_scoreData[3].month = 7;
	m_scoreData[4].month = 7;

	m_scoreData[0].year = 1990;
	m_scoreData[1].year = 1990;
	m_scoreData[2].year = 1990;
	m_scoreData[3].year = 1990;
	m_scoreData[4].year = 1990;
}


HighscoreMenu::~HighscoreMenu()
{
}

void HighscoreMenu::processEvents(Xbox360Controller & pad)
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
		if (pad.m_currentState.A && !pad.m_previousState.A)
		{
			messageHandler(m_selected->getA());
		}
	}
}

void HighscoreMenu::update(sf::Time t_deltaTime)
{
	m_sortName->setCharacterSize(m_options.fontSize * 5 + 10);
	m_sortScore->setCharacterSize(m_options.fontSize * 5 + 10);
	m_sortDate->setCharacterSize(m_options.fontSize * 5 + 10);
	m_back->setCharacterSize(m_options.fontSize * 5 + 10);
	m_score1.setCharacterSize(m_options.fontSize * 5 + 10);
	m_score2.setCharacterSize(m_options.fontSize * 5 + 10);
	m_score3.setCharacterSize(m_options.fontSize * 5 + 10);
	m_score4.setCharacterSize(m_options.fontSize * 5 + 10);
	m_score5.setCharacterSize(m_options.fontSize * 5 + 10);

	m_score1.setText(m_scoreData[0].name +
		" - score: " + std::to_string(m_scoreData[0].score) +
		", date: " + std::to_string(m_scoreData[0].day) +
		"-" + std::to_string(m_scoreData[0].month) +
		"-" + std::to_string(m_scoreData[0].year));


	m_score2.setText(m_scoreData[1].name +
		" - score: " + std::to_string(m_scoreData[1].score) +
		", date: " + std::to_string(m_scoreData[1].day) +
		"-" + std::to_string(m_scoreData[1].month) +
		"-" + std::to_string(m_scoreData[1].year));


	m_score3.setText(m_scoreData[2].name +
		" - score: " + std::to_string(m_scoreData[2].score) +
		", date: " + std::to_string(m_scoreData[2].day) +
		"-" + std::to_string(m_scoreData[2].month) +
		"-" + std::to_string(m_scoreData[2].year));


	m_score4.setText(m_scoreData[3].name +
		" - score: " + std::to_string(m_scoreData[3].score) +
		", date: " + std::to_string(m_scoreData[3].day) +
		"-" + std::to_string(m_scoreData[3].month) +
		"-" + std::to_string(m_scoreData[3].year));


	m_score5.setText(m_scoreData[4].name +
		" - score: " + std::to_string(m_scoreData[4].score) +
		", date: " + std::to_string(m_scoreData[4].day) +
		"-" + std::to_string(m_scoreData[4].month) +
		"-" + std::to_string(m_scoreData[4].year));

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

void HighscoreMenu::render(sf::RenderWindow & t_window)
{
	sf::RenderStates state = m_renderState;
	state.transform.translate(-300, 0);

	t_window.draw(m_highscoreMenu, state);
	t_window.draw(m_title, m_renderState);
	t_window.draw(m_score1, m_renderState);
	t_window.draw(m_score2, m_renderState);
	t_window.draw(m_score3, m_renderState);
	t_window.draw(m_score4, m_renderState);
	t_window.draw(m_score5, m_renderState);
}

void HighscoreMenu::messageHandler(std::string s)
{
	if (s == "sortNameButton")
	{
		m_selected->deselect();
		m_selected = m_sortName;
		m_selected->select();
	}

	if (s == "sortScoreButton")
	{
		m_selected->deselect();
		m_selected = m_sortScore;
		m_selected->select();
	}

	if (s == "sortDateButton")
	{
		m_selected->deselect();
		m_selected = m_sortDate;
		m_selected->select();
	}

	if (s == "backButton")
	{
		m_selected->deselect();
		m_selected = m_back;
		m_selected->select();
	}

	if (s == "sortname")
	{
		sortName();
	}

	if (s == "sortscore")
	{
		sortScore();
	}

	if (s == "sortdate")
	{
		sortDate();
	}

	if (s == "mainmenu")
	{
		transitionOut(Menu::StateMainMenu);
	}

}

void HighscoreMenu::transitionIn()
{
	m_selected->deselect();
	m_selected = m_back;
	m_selected->select();

	sf::Transform temp;
	temp.translate(0, -1200);
	m_renderState.transform = temp;

	m_transitionIn = true;

	m_transitionTime = sf::seconds(m_transitionTotalTime.asSeconds() / 100 * m_options.animSpeed);
}

void HighscoreMenu::transitionOut(Menu s)
{
	m_transitionOut = true;
	m_transitionTime = sf::seconds(m_transitionTotalTime.asSeconds() / 100 * m_options.animSpeed);

	m_nextState = s;
}

bool HighscoreMenu::getChengeMenu()
{
	return m_changeMenu;
}

void HighscoreMenu::resetChangeMenu()
{
	m_changeMenu = false;
}

void HighscoreMenu::sortName()
{
	bool done = false;

	while (!done)
	{
		done = true;

		for (int i = 0; i != 5 - 1; ++i)
		{
			if (m_scoreData[i].name[0] > m_scoreData[i + 1].name[0])
			{
				Scores temp = m_scoreData[i];
				m_scoreData[i] = m_scoreData[i + 1];
				m_scoreData[i + 1] = temp;

				done = false;
			}
		}
	}
}

void HighscoreMenu::sortScore()
{
	bool done = false;

	while (!done)
	{
		done = true;

		for (int i = 0; i != 5 - 1; ++i)
		{
			if (m_scoreData[i].score < m_scoreData[i + 1].score)
			{
				Scores temp = m_scoreData[i];
				m_scoreData[i] = m_scoreData[i + 1];
				m_scoreData[i + 1] = temp;

				done = false;
			}
		}
	}
}

void HighscoreMenu::sortDate()
{
	bool done = false;

	while (!done)
	{
		done = true;

		for (int i = 0; i != 5 - 1; ++i)
		{
			if (m_scoreData[i].day > m_scoreData[i + 1].day)
			{
				Scores temp = m_scoreData[i];
				m_scoreData[i] = m_scoreData[i + 1];
				m_scoreData[i + 1] = temp;

				done = false;
			}
		}
	}
}

void HighscoreMenu::initGui()
{
	if (!m_arialBlackFont.loadFromFile("ASSETS\\FONTS\\ariblk.ttf"))
	{
		std::cout << "problem loading arial black font" << std::endl;
	}

	VLayout* layout = new VLayout;
	layout->setSpace(25);

	m_sortName = new TextButton("Sort by name", m_arialBlackFont, 250);
	m_sortName->setCharacterSize(CHARACTER_SIZE);
	layout->add(m_sortName);

	m_sortScore = new TextButton("Sort by Score", m_arialBlackFont, 250);
	m_sortScore->setCharacterSize(CHARACTER_SIZE);
	layout->add(m_sortScore);

	m_sortDate = new TextButton("Sort by Date", m_arialBlackFont, 250);
	m_sortDate->setCharacterSize(CHARACTER_SIZE);
	layout->add(m_sortDate);

	m_back = new TextButton("Back", m_arialBlackFont, 250);
	m_back->setCharacterSize(CHARACTER_SIZE);
	layout->add(m_back);
	
	m_highscoreMenu.setLayout(layout);

	//setting the strings that will be returned on a button input
	m_sortName->setDown("sortScoreButton");
	m_sortName->setA("sortname");

	m_sortScore->setUp("sortNameButton");
	m_sortScore->setDown("sortDateButton");
	m_sortScore->setA("sortscore");

	m_sortDate->setUp("sortScoreButton");
	m_sortDate->setDown("backButton");
	m_sortDate->setA("sortdate");

	m_back->setUp("sortDateButton");
	m_back->setA("mainmenu");


	m_selected = m_back;
	m_selected->select();
}
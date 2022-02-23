#include "StoryScreen.h"



StoryScreen::StoryScreen(Menu & state) :
	m_state(state)
{
	m_transitionTotalTime = sf::seconds(1);

	if (!m_slide1Tex.loadFromFile("ASSETS\\IMAGES\\slide1.png"))
	{
		std::cout << "problem loading splash image" << std::endl;
	}

	if (!m_slide2Tex.loadFromFile("ASSETS\\IMAGES\\slide2.png"))
	{
		std::cout << "problem loading splash image" << std::endl;
	}

	if (!m_slide3Tex.loadFromFile("ASSETS\\IMAGES\\slide3.png"))
	{
		std::cout << "problem loading splash image" << std::endl;
	}

	m_slide1.setTexture(m_slide1Tex);
	m_slide2.setTexture(m_slide2Tex);
	m_slide3.setTexture(m_slide3Tex);

	m_sliderTimer = sf::seconds(2);
}


StoryScreen::~StoryScreen()
{
}

void StoryScreen::update(sf::Time t_deltaTime)
{
	m_sliderTimer -= t_deltaTime;
	if (m_sliderTimer.asSeconds() < 0)
	{
		m_sliderTimer = sf::seconds(1.5);
		m_currentSlide++;
	}

	if (m_currentSlide > 4 && !m_transitionOut)
	{
		transitionOut(Menu::StateSplash);
	}

	double scaler;
	if (m_transitionOut)
	{
		m_transitionTime -= t_deltaTime;
		scaler = t_deltaTime.asSeconds() / m_transitionTotalTime.asSeconds();
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

void StoryScreen::render(sf::RenderWindow & t_window)
{
	if (m_currentSlide > 0)
	{
		t_window.draw(m_slide1, m_renderState);
	}
	if (m_currentSlide > 1)
	{
		t_window.draw(m_slide2, m_renderState);
	}
	if (m_currentSlide > 2)
	{
		t_window.draw(m_slide3, m_renderState);
	}
}

void StoryScreen::transitionOut(Menu t_string)
{
	m_transitionOut = true;
	m_transitionTime = m_transitionTotalTime;

	m_nextState = t_string;
}

bool StoryScreen::getChengeMenu()
{
	return m_changeMenu;
}

void StoryScreen::resetChangeMenu()
{
	m_changeMenu = false;
}

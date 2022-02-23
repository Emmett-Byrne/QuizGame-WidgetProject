#include "SplashScreen.h"

SplashScreen::SplashScreen(Menu & state) :
	m_state(state)
{
	m_transitionTotalTime = sf::seconds(2);

	if (!m_texture.loadFromFile("ASSETS\\IMAGES\\SPLASH.png"))
	{
		std::cout << "problem loading splash image" << std::endl;
	}

	m_splash.setTexture(m_texture);

	m_splash.setScale(1.1f, 1.4f);

	sf::Transform temp;
	temp.translate(0, -1200);
	m_renderState.transform = temp;

}

SplashScreen::~SplashScreen()
{
}

void SplashScreen::processEvents(Xbox360Controller & pad)
{
	if (!m_transitionIn && !m_transitionOut)
	{
		if (pad.m_currentState.A && !pad.m_previousState.A)
		{
			transitionOut(Menu::StateLicense);
		}
	}
}

void SplashScreen::update(sf::Time t_deltaTime)
{

	double scaler;
	if (m_transitionIn || m_transitionOut)
	{
		m_transitionTime -= t_deltaTime;
		scaler = t_deltaTime.asSeconds() / m_transitionTotalTime.asSeconds();
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

void SplashScreen::render(sf::RenderWindow & t_window)
{
	t_window.draw(m_splash, m_renderState);
}

void SplashScreen::transitionIn()
{
	sf::Transform temp;
	temp.translate(0, -1200);
	m_renderState.transform = temp;

	m_transitionIn = true;

	m_transitionTime = m_transitionTotalTime;
}

void SplashScreen::transitionOut(Menu s)
{
	m_transitionOut = true;
	m_transitionTime = m_transitionTotalTime;

	m_nextState = s;
}

bool SplashScreen::getChengeMenu()
{
	return m_changeMenu;
}

void SplashScreen::resetChangeMenu()
{
	m_changeMenu = false;
}

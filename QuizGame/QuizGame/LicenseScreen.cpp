#include "LicenseScreen.h"

LicenseScreen::LicenseScreen(Menu & state) :
	m_state(state)
{
	m_transitionTotalTime = sf::seconds(1);

	if (!m_texture.loadFromFile("ASSETS\\IMAGES\\SFML-LOGO.png"))
	{
		std::cout << "problem loading splash image" << std::endl;
	}

	m_license.setTexture(m_texture);
	m_license.setScale(2.2f, 2.2f);
	m_license.setPosition(600 - m_license.getGlobalBounds().width / 2.0, 0);
	sf::Transform temp;
	temp.translate(0, -1200);
	m_renderState.transform = temp;
}

LicenseScreen::~LicenseScreen()
{
}

void LicenseScreen::processEvents(Xbox360Controller & pad)
{
	if (pad.m_currentState.A && !pad.m_previousState.A ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		transitionOut(Menu::StateMainMenu);
	}
}

void LicenseScreen::update(sf::Time t_deltaTime)
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
			transitionOut(Menu::StateMainMenu);
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

void LicenseScreen::render(sf::RenderWindow & t_window)
{
	t_window.draw(m_license, m_renderState);
}

void LicenseScreen::transitionIn()
{
	sf::Transform temp;
	temp.translate(0, -1200);
	m_renderState.transform = temp;

	m_transitionIn = true;

	m_transitionTime = m_transitionTotalTime;
}

void LicenseScreen::transitionOut(Menu s)
{
	m_transitionOut = true;
	m_transitionTime = m_transitionTotalTime;

	m_nextState = s;
}

bool LicenseScreen::getChengeMenu()
{
	return m_changeMenu;
}

void LicenseScreen::resetChangeMenu()
{
	m_changeMenu = false;
}

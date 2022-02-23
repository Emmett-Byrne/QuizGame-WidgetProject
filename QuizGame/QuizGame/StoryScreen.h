#pragma once
#include <SFML/Graphics.hpp>
#include "XBOX360CONTROLLER.h"
#include "States.h"
class StoryScreen
{
public:
	StoryScreen(Menu & state);
	~StoryScreen();
	void update(sf::Time t_deltaTime);
	void render(sf::RenderWindow & t_window);
	void transitionOut(Menu t_string); //Sets up for transitioning into the menu
	bool getChengeMenu(); //Returns wheather the menu has finished transitioning out
	void resetChangeMenu(); //resets the bool to false

private:
	Menu & m_state; //reference to the state holding the current menu
	Menu m_nextState;

	bool m_transitionOut;
	sf::Time m_transitionTime;
	sf::Time m_transitionTotalTime;
	
	sf::Time m_sliderTimer; //timer until the next slide is shown
	int m_currentSlide{ 0 }; //the current slide the screen is at

	sf::RenderStates m_renderState; //used to position widgets as they are transitioning

	bool m_changeMenu;

	sf::Texture m_slide1Tex;
	sf::Texture m_slide2Tex;
	sf::Texture m_slide3Tex;

	sf::Sprite m_slide1;
	sf::Sprite m_slide2;
	sf::Sprite m_slide3;
};


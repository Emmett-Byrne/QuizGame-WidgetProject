#pragma once

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
#include "LevelLoader.h"

enum GameState
{
	Selection,
	QuizOne,
	QuizTwo,
	Over
};

class GameScreen
{
public:
	/// <summary>
	/// default constructor
	/// </summary>
	/// <param name="t_font">a reference to a font</param>
	/// <param name="t_window">reference to the render window for the frame</param>
	/// <param name="state">reference to the game state</param>
	/// <param name="t_options">a reference to the game settings in the options screen</param>
	GameScreen(sf::Font & t_font, sf::RenderWindow & t_window, Menu & state, Options & t_options);
	~GameScreen();

	/// <summary>
	/// processes game events
	/// </summary>
	/// <param name="pad"> reference to the game controller</param>
	/// <param name="t_event">an event passed in from game.cpp</param>
	void processEvents(Xbox360Controller & pad);

	/// <summary>
	/// updates all objects in this class
	/// </summary>
	/// <param name="t_deltaTime">time since last update</param>
	void update(sf::Time t_deltaTime);

	/// <summary>
	/// function that renders all drawable objects
	/// </summary>
	/// <param name="t_window">reference to the main window</param>
	void render(sf::RenderWindow & t_window);

	/// <summary>
	/// handles messages sent by buttons
	/// </summary>
	/// <param name="s"> message</param>
	void messageHandler(std::string s);

	/// <summary>
	/// handles button in transition
	/// </summary>
	void transitionIn();

	/// <summary>
	/// handles button out transisiton
	/// </summary>
	/// <param name="s">menu to get to next</param>
	void transitionOut(Menu s);

	bool getChangeMenu();
	/// <summary>
	/// resets the m_changeMenu variable
	/// </summary>
	void resetChangeMenu();

private:
	/// <summary>
	/// initilizes the quiz
	/// </summary>
	/// <param name="t_quiz">1 for quiz1, 2 for quiz2</param>
	void initQuiz(int t_quiz);

	/// <summary>
	/// this function loads in questions from yaml
	/// </summary>
	void loadQuestions();

	/// <summary>
	/// checks if the selected answer was correct
	/// </summary>
	/// <param name="t_answer">answer selected</param>
	void checkAnswer(int t_answer);

	int const CHARACTER_SIZE = 16; // initial character size before options font size is set

	/// <summary>
	/// initilises the screen where you select quiz1 or quiz2
	/// </summary>
	void initGui();

	/// <summary>
	/// initilises the game over screen with score
	/// </summary>
	void initOver();

	sf::Font m_arialBlackFont; // font for all text objects

	LevelData m_quizData; // holds quiz data

	Menu & m_state; //reference to the state holding the current menu
	Menu m_nextState;

	Label m_title; // a label in top left used to tell what screen its on
	Label* m_question; // label to display the questions

	TextButton* m_ansOne;
	TextButton* m_ansTwo;
	TextButton* m_ansThree;
	TextButton* m_ansFour;
	TextButton* m_back;

	Frame m_gameMenu;

	Widget* m_selected;

	Options & m_options;

	bool m_transitionIn;
	bool m_transitionOut;
	sf::Time m_transitionTime;
	sf::Time m_transitionTotalTime;

	sf::RenderStates m_renderState;

	bool m_changeMenu;

	GameState m_gameState;

	int m_quizNo = 0;
	int m_questionNo = 0;

	int m_score = 0;
};


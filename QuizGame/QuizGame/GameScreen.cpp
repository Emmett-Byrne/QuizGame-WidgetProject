#include "GameScreen.h"



GameScreen::GameScreen(sf::Font & t_font, sf::RenderWindow & t_window, Menu & state, Options & t_options) :
	m_title("Quiz selection", t_font),
	m_gameMenu(t_window),
	m_state(state),
	m_gameState(GameState::Selection),
	m_options(t_options)
{
	initGui(); // initilise the quiz selection
	m_transitionTotalTime = sf::seconds(2);

	sf::Transform temp;
	temp.translate(0, -500);
	m_renderState.transform = temp;

	// load data from .yaml file
	if (!LevelLoader::load(1, m_quizData))
	{
		return;
	}

	sf::Transform tempTrans;
	temp.translate(0, -1200);
	m_renderState.transform = temp;
}

GameScreen::~GameScreen()
{
}

void GameScreen::processEvents(Xbox360Controller & pad)
{
	if (pad.m_currentState.DpadUp && !pad.m_previousState.DpadUp)
	{
		messageHandler(m_selected->getUp()); //returns a string 
	}
	if (pad.m_currentState.DpadDown && !pad.m_previousState.DpadDown)
	{
		messageHandler(m_selected->getDown());
	}
	if (pad.m_currentState.A && !pad.m_previousState.A)
	{
		messageHandler(m_selected->getA());
	}

	/// <summary>
	/// underneath is a chunk of code that was used for testing
	/// without controller
	/// </summary>

	//if (t_event.type ==  sf::Event::KeyReleased)
	//{
	//	if (t_event.key.code == sf::Keyboard::Up)
	//	{
	//		messageHandler(m_selected->getUp()); //returns a string 
	//	}
	//	if (t_event.key.code == sf::Keyboard::Down)
	//	{
	//		messageHandler(m_selected->getDown());
	//	}
	//	if (t_event.key.code == sf::Keyboard::Space)
	//	{
	//		messageHandler(m_selected->getA());
	//	}
	//}
}

void GameScreen::update(sf::Time t_deltaTime)
{
	// update all text size according to the settings
	m_question->setCharacterSize(m_options.fontSize * 5 + 10);
	m_ansOne->setCharacterSize(m_options.fontSize * 5 + 10);
	m_ansTwo->setCharacterSize(m_options.fontSize * 5 + 10);
	m_ansThree->setCharacterSize(m_options.fontSize * 5 + 10);
	m_ansFour->setCharacterSize(m_options.fontSize * 5 + 10);	
	m_back->setCharacterSize(m_options.fontSize * 5 + 10);

	double scaler;
	if (m_transitionIn || m_transitionOut)
	{
		m_transitionTime -= t_deltaTime;
		scaler = t_deltaTime.asSeconds() / (m_transitionTotalTime.asSeconds() / 100 * m_options.animSpeed);
	}
	if (m_transitionIn)
	{
		m_renderState.transform.translate(sf::Vector2f(0, scaler * 1200));

		// if game was over when transitioning
		// reset it
		if (m_gameState == GameState::Over)
		{
			m_title.setText("Quiz selection");
			initGui();
			m_score = 0;
			m_gameState = GameState::Selection;
			m_quizNo = 0;
			m_questionNo = 0;
		}

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

	if (m_gameState == GameState::Over)
	{
		if (m_selected != m_back)
		{
			m_selected->deselect();
			m_selected = m_back;
			m_selected->select();
		}
	}
}

void GameScreen::render(sf::RenderWindow & t_window)
{
	t_window.draw(m_gameMenu, m_renderState);
	t_window.draw(m_title, m_renderState);
}

void GameScreen::messageHandler(std::string s)
{
	switch (m_gameState)
	{
	case Selection:
		if (s == "quiz1")
		{
			m_selected->deselect(); //changes colour back to default
			m_selected = m_ansOne; //changes the currently selected widget to this
			m_selected->select(); //changes the colour so that it looks like it's selected
		}
		if (s == "quiz2")
		{
			m_selected->deselect();
			m_selected = m_ansTwo;
			m_selected->select();
		}
		if (s == "set1")
		{
			m_title.setText("Quiz 1");
			m_quizNo = 1;
			initQuiz(1);
			m_gameState = GameState::QuizOne;
		}
		if (s == "set2")
		{
			m_title.setText("Quiz 2");
			m_quizNo = 2;
			initQuiz(2);
			m_gameState = GameState::QuizTwo;
		}		
		break;
	case QuizOne:
		if (s == "go1")
		{
			m_selected->deselect();
			m_selected = m_ansOne;
			m_selected->select();
		}
		if (s == "go2")
		{
			m_selected->deselect();
			m_selected = m_ansTwo;
			m_selected->select();
		}
		if (s == "go3")
		{
			m_selected->deselect();
			m_selected = m_ansThree;
			m_selected->select();
		}
		if (s == "go4")
		{
			m_selected->deselect();
			m_selected = m_ansFour;
			m_selected->select();
		}

		if (s == "set1")
		{
			checkAnswer(1);
			m_questionNo++;
			loadQuestions();
			m_selected->deselect();
			m_selected = m_ansOne;
			m_selected->select();
		}
		if (s == "set2")
		{
			checkAnswer(2);
			m_questionNo++;
			loadQuestions();
			m_selected->deselect();
			m_selected = m_ansOne;
			m_selected->select();
		}
		if (s == "set3")
		{
			checkAnswer(3);
			m_questionNo++;
			loadQuestions();
			m_selected->deselect();
			m_selected = m_ansOne;
			m_selected->select();
		}
		if (s == "set4")
		{
			checkAnswer(4);
			m_questionNo++;
			loadQuestions();
			m_selected->deselect();
			m_selected = m_ansOne;
			m_selected->select();
		}
		break;

	case QuizTwo:
		if (s == "go1")
		{
			m_selected->deselect();
			m_selected = m_ansOne;
			m_selected->select();
		}
		if (s == "go2")
		{
			m_selected->deselect();
			m_selected = m_ansTwo;
			m_selected->select();
		}
		if (s == "go3")
		{
			m_selected->deselect();
			m_selected = m_ansThree;
			m_selected->select();
		}
		if (s == "go4")
		{
			m_selected->deselect();
			m_selected = m_ansFour;
			m_selected->select();
		}

		if (s == "set1")
		{
			checkAnswer(1);
			m_questionNo++;
			loadQuestions();
			m_selected->deselect();
			m_selected = m_ansOne;
			m_selected->select();
		}
		if (s == "set2")
		{
			checkAnswer(2);
			m_questionNo++;
			loadQuestions();
			m_selected->deselect();
			m_selected = m_ansOne;
			m_selected->select();
		}
		if (s == "set3")
		{
			checkAnswer(3);
			m_questionNo++;
			loadQuestions();
			m_selected->deselect();
			m_selected = m_ansOne;
			m_selected->select();
		}
		if (s == "set4")
		{
			checkAnswer(4);
			m_questionNo++;
			loadQuestions();
			m_selected->deselect();
			m_selected = m_ansOne;
			m_selected->select();
		}
		break;
	case Over:
		m_selected->deselect();
		m_selected = m_back;
		m_selected->select();
		if (s == "mainmenu")
		{
			transitionOut(Menu::StateMainMenu);
		}
	default:
		break;
	}

	if (s == "back")
	{
		m_selected->deselect();
		m_selected = m_back;
		m_selected->select();
	}
	if (s == "mainmenu")
	{
		transitionOut(Menu::StateMainMenu);
	}

}

void GameScreen::transitionIn()
{
	m_selected->deselect();
	m_selected = m_ansOne;
	m_selected->select();

	sf::Transform temp;
	temp.translate(0, -1200);
	m_renderState.transform = temp;

	m_transitionIn = true;

	m_transitionTime = sf::seconds(m_transitionTotalTime.asSeconds() / 100 * m_options.animSpeed);
}

void GameScreen::transitionOut(Menu s)
{
	m_transitionOut = true;
	m_transitionTime = sf::seconds(m_transitionTotalTime.asSeconds() / 100 * m_options.animSpeed);

	m_nextState = s;
}

bool GameScreen::getChangeMenu()
{
	return m_changeMenu;
}

void GameScreen::resetChangeMenu()
{
	m_changeMenu = false;
}

void GameScreen::initQuiz(int t_quiz)
{
	VLayout* layout = new VLayout;
	layout->setSpace(25);

	m_question = new Label("", m_arialBlackFont);
	m_question->setCharacterSize(CHARACTER_SIZE);
	layout->add(m_question);

	m_ansOne = new TextButton("", m_arialBlackFont, 380);
	m_ansOne->setCharacterSize(CHARACTER_SIZE);
	layout->add(m_ansOne);

	m_ansTwo = new TextButton("", m_arialBlackFont, 380);
	m_ansTwo->setCharacterSize(CHARACTER_SIZE);
	layout->add(m_ansTwo);

	m_ansThree = new TextButton("", m_arialBlackFont, 380);
	m_ansThree->setCharacterSize(CHARACTER_SIZE);
	layout->add(m_ansThree);

	m_ansFour = new TextButton("", m_arialBlackFont, 380);
	m_ansFour->setCharacterSize(CHARACTER_SIZE);
	layout->add(m_ansFour);

	m_back = new TextButton("Back", m_arialBlackFont, 380);
	m_back->setCharacterSize(CHARACTER_SIZE);
	layout->add(m_back);

	//setting the strings that will be returned on a button input
	m_ansOne->setDown("go2");
	m_ansOne->setA("set1");

	m_ansTwo->setUp("go1");
	m_ansTwo->setDown("go3");
	m_ansTwo->setA("set2");

	m_ansThree->setUp("go2");
	m_ansThree->setDown("go4");
	m_ansThree->setA("set3");

	m_ansFour->setUp("go3");
	m_ansFour->setDown("back");
	m_ansFour->setA("set4");

	m_back->setUp("go4");
	m_back->setA("mainmenu");

	m_gameMenu.setLayout(layout);

	// after loading in the buttons for the quiz, load first questions
	if (t_quiz == 1)
	{
		m_question->setText(m_quizData.m_quizOne[0].m_question);
		m_ansOne->setText(m_quizData.m_quizOne[0].m_answerOne);
		m_ansTwo->setText(m_quizData.m_quizOne[0].m_answerTwo);
		m_ansThree->setText(m_quizData.m_quizOne[0].m_answerThree);
		m_ansFour->setText(m_quizData.m_quizOne[0].m_answerFour);
	}
	else
	{
		m_question->setText(m_quizData.m_quizTwo[0].m_question);
		m_ansOne->setText(m_quizData.m_quizTwo[0].m_answerOne);
		m_ansTwo->setText(m_quizData.m_quizTwo[0].m_answerTwo);
		m_ansThree->setText(m_quizData.m_quizTwo[0].m_answerThree);
		m_ansFour->setText(m_quizData.m_quizTwo[0].m_answerFour);
	}

	m_selected = m_ansOne;
	m_selected->select();
}

void GameScreen::loadQuestions()
{
	if (m_questionNo < 3)
	{
		if (m_quizNo == 1)
		{
			m_question->setText(m_quizData.m_quizOne[m_questionNo].m_question);
			m_ansOne->setText(m_quizData.m_quizOne[m_questionNo].m_answerOne);
			m_ansTwo->setText(m_quizData.m_quizOne[m_questionNo].m_answerTwo);
			m_ansThree->setText(m_quizData.m_quizOne[m_questionNo].m_answerThree);
			m_ansFour->setText(m_quizData.m_quizOne[m_questionNo].m_answerFour);
		}
		else if (m_quizNo == 2)
		{
			m_question->setText(m_quizData.m_quizTwo[m_questionNo].m_question);
			m_ansOne->setText(m_quizData.m_quizTwo[m_questionNo].m_answerOne);
			m_ansTwo->setText(m_quizData.m_quizTwo[m_questionNo].m_answerTwo);
			m_ansThree->setText(m_quizData.m_quizTwo[m_questionNo].m_answerThree);
			m_ansFour->setText(m_quizData.m_quizTwo[m_questionNo].m_answerFour);
		}
	}
	else
	{
		m_gameState = GameState::Over;
		initOver();
	}
}

void GameScreen::checkAnswer(int t_answer)
{
	if (m_quizNo == 1)
	{
		switch (m_questionNo)
		{
		case(0):
			if (t_answer == 1)
			{
				// correct answer
				m_score += 10;
			}
		case(1):
			if (t_answer == 2)
			{
				// correct answer
				m_score += 10;
			}
			break;
		case(2):
			if (t_answer == 4)
			{
				// correct answer
				m_score += 10;
			}
			break;
		default:
			break;
		}
	}
	else if (m_quizNo == 2)
	{
		switch (m_questionNo)
		{
		case(0):
			if (t_answer == 4)
			{
				// correct answer
				m_score += 10;
			}
		case(1):
			if (t_answer == 3)
			{
				// correct answer
				m_score += 10;
			}
			break;
		case(2):
			if (t_answer == 1)
			{
				// correct answer
				m_score += 10;
			}
			break;
		default:
			break;
		}
	}
}

void GameScreen::initGui()
{
	if (!m_arialBlackFont.loadFromFile("ASSETS\\FONTS\\ariblk.ttf"))
	{
		std::cout << "problem loading arial black font" << std::endl;
	}

	VLayout* layout = new VLayout;
	layout->setSpace(25);

	m_question = new Label("Choose quiz 1 or 2:", m_arialBlackFont);
	m_question->setCharacterSize(CHARACTER_SIZE);
	layout->add(m_question);

	m_ansOne = new TextButton("Quiz 1", m_arialBlackFont, 380);
	m_ansOne->setCharacterSize(CHARACTER_SIZE);
	layout->add(m_ansOne);
	
	m_ansTwo = new TextButton("Quiz 2", m_arialBlackFont, 380);
	m_ansTwo->setCharacterSize(CHARACTER_SIZE);
	layout->add(m_ansTwo);

	m_ansThree = new TextButton("", m_arialBlackFont, 380);
	m_ansThree->setCharacterSize(CHARACTER_SIZE);

	m_ansFour = new TextButton("", m_arialBlackFont, 380);
	m_ansFour->setCharacterSize(CHARACTER_SIZE);

	m_back = new TextButton("Back", m_arialBlackFont, 380);
	m_back->setCharacterSize(CHARACTER_SIZE);
	layout->add(m_back);

	//setting the strings that will be returned on a button input
	m_ansOne->setDown("quiz2");
	m_ansOne->setA("set1");

	m_ansTwo->setUp("quiz1");
	m_ansTwo->setDown("back");
	m_ansTwo->setA("set2");

	m_back->setUp("quiz2");
	m_back->setA("mainmenu");

	m_gameMenu.setLayout(layout);

	m_selected = m_ansOne;
	m_selected->select();
}

void GameScreen::initOver()
{
	VLayout* layout = new VLayout;
	layout->setSpace(25);

	m_question = new Label("Your score is:", m_arialBlackFont);
	layout->add(m_question);

	m_ansOne = new TextButton(std::to_string(m_score), m_arialBlackFont, 80);
	layout->add(m_ansOne);

	m_ansTwo = new TextButton("", m_arialBlackFont, 380);

	m_ansThree = new TextButton("", m_arialBlackFont, 380);

	m_ansFour = new TextButton("", m_arialBlackFont, 380);

	m_back = new TextButton("Back", m_arialBlackFont, 100);
	layout->add(m_back);

	//setting the strings that will be returned on a button input
	m_back->setA("mainmenu");

	m_gameMenu.setLayout(layout);

	m_selected = m_back;
	m_selected->select();
}

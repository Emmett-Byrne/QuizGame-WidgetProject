#pragma once

#include <SFML/System/Vector2.hpp>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include "yaml-cpp\yaml.h"

struct QuizData
{
	std::string m_question;
	std::string m_answerOne;
	std::string m_answerTwo;
	std::string m_answerThree;
	std::string m_answerFour;
};

struct LevelData
{
	std::vector<QuizData> m_quizOne;
	std::vector<QuizData> m_quizTwo;
};


class LevelLoader
{
public:

	LevelLoader() = default;

	static bool load(int nr, LevelData& level);
};


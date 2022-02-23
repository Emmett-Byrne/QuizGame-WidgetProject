#include "LevelLoader.h"

////////////////////////////////////////////////////////////
void operator >> (const YAML::Node& quizNode, QuizData& quiz)
{
	quiz.m_question = quizNode["question"].as<std::string>();
	quiz.m_answerOne = quizNode["answer1"].as<std::string>();
	quiz.m_answerTwo = quizNode["answer2"].as<std::string>();
	quiz.m_answerThree = quizNode["answer3"].as<std::string>();
	quiz.m_answerFour = quizNode["answer4"].as<std::string>();
}

////////////////////////////////////////////////////////////
void operator >> (const YAML::Node& levelNode, LevelData& level)
{
	const YAML::Node& quizOneNode = levelNode["quizOne"].as<YAML::Node>();

	for (unsigned i = 0; i < quizOneNode.size(); ++i)
	{
		QuizData quiz;
		quizOneNode[i] >> quiz;
		level.m_quizOne.push_back(quiz);
	}

	const YAML::Node& quizTwoNode = levelNode["quizTwo"].as<YAML::Node>();
	for (unsigned i = 0; i < quizTwoNode.size(); ++i)
	{
		QuizData quiz;
		quizTwoNode[i] >> quiz;
		level.m_quizTwo.push_back(quiz);
	}

}


bool LevelLoader::load(int nr, LevelData & level)
{
	std::stringstream ss;
	ss << "./ASSETS/QUESTIONS/quiz";
	ss << nr;
	ss << ".yaml";

	try
	{
		YAML::Node baseNode = YAML::LoadFile(ss.str());
		if (baseNode.IsNull())
		{
			std::string message("file: " + ss.str() + " not found");
			throw std::exception(message.c_str());
		}
		baseNode >> level;
	}
	catch (YAML::ParserException& e)
	{
		std::cout << e.what() << "\n";
		return false;
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << "\n";
		return false;
	}

	return true;
}

#pragma once
#include "Includes.h"
#include "TestResult.h"

class Test
{
public:
	class Question
	{
	private:
		string question;
		vector<string> answers;
		string right_answer;

	public:
		Question(string question, vector<string> answers, string right_answer) : question(question), answers(answers), right_answer(right_answer)
		{

		}

		string getQuestion() { return question; }
		vector<string> getAnswers() { return answers; }
		string getRightAnswer() { return right_answer; }
	};

private:
	string section;
	string name;
	vector<Question> questions;
	TestResult result;

public:
	Test(string section, string name, vector<Question> questions) : section(section), name(name), questions(questions), result(TestResult(1, 1))
	{
		
	}

	Test(string section, string name, vector<Question> questions, int correct, int incorrect) : section(section), name(name), questions(questions), result(TestResult(correct, incorrect))
	{

	}

	string getSection() { return section; }
	string getName() { return name; }
	vector<Question> getQuestions() { return questions; }
	TestResult getResult() { return result; }
};
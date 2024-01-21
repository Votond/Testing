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
	int test_id;
	string section;
	string name;
	vector<Question> questions;

public:

	Test(int test_id, string section, string name, vector<Question> questions) : test_id(test_id), section(section), name(name), questions(questions)
	{

	}

	int getId() { return test_id; }
	string getSection() { return section; }
	string getName() { return name; }
	vector<Question> getQuestions() { return questions; }
};
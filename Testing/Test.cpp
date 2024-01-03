#include "Includes.h"
#include "Test.h"

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
		Question(string question, vector<string> answers, string right_answer) : question(question), answers(answers), right_answer(right_answer) {}
	};

private:
	string section;
	string name;
	vector<Question> questions;

public:
	Test(string section, string name, vector<Question> questions) : section(section), name(name), questions(questions)
	{

	}

	string getSection() { return section; }
	string getName() { return name; }
	vector<Question> getQuestions() { return questions; }
};
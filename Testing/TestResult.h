#pragma once
#include "Includes.h"
#include "TestResult.h"

class TestResult
{
public:
	static enum MARK
	{
		ZERO = 0,
		ONE = 1,
		TWO = 2,
		THREE = 3,
		FOUR = 4,
		FIVE = 5,
		SIX = 6,
		SEVEN = 7,
		EIGHT = 8,
		NINE = 9,
		TEN = 10,
		ELEVEN = 11,
		TWELVE = 12
	};

private:
	MARK mark;
	int correct;
	int incorrect;
	// Процент правильных ответов
	float correct_perc;
	// Процент неправильных ответов
	float incorrect_perc;

public:
	TestResult(int correct, int incorrect);

	MARK getMark() { return mark; }
	int getCorrect() { return correct; }
	int getIncorrect() { return incorrect; }
	float getCorrectPerc() { return correct_perc; }
	float getIncorrectPerc() { return incorrect_perc; }

private:
	MARK intToMarkEnum(int mark);
};
#include "Includes.h"
#include "TestResult.h"

class TestResult
{
public:
	static enum MARK
	{
		ZERO,
		ONE,
		TWO,
		THREE,
		FOUR,
		FIVE,
		SIX,
		SEVEN,
		EIGHT,
		NINE,
		TEN,
		ELEVEN,
		TWELVE
	};

private:
	MARK mark;
	int correct;
	int incorrect;
	// Процент правильных ответов
	float correct_perc;
	// Процент неправильных ответов
	float incorrect_perc;

	TestResult(int correct, int incorrect) : correct(correct), incorrect(incorrect)
	{
		float total = correct + incorrect;

		this->correct_perc = (float)correct / total * 100.f;
		this->incorrect_perc = (float)incorrect / total * 100.f;

		float unit = total / 12;

		this->mark = intToMarkEnum((int)round((float)correct / unit));
	}

	MARK intToMarkEnum(int mark)
	{
		switch (mark)
		{
		case 12:
			return TWELVE;

		case 11:
			return ELEVEN;

		case 10:
			return TEN;

		case 9:
			return NINE;

		case 8:
			return EIGHT;

		case 7:
			return SEVEN;

		case 6:
			return SIX;

		case 5:
			return FIVE;

		case 4:
			return FOUR;

		case 3:
			return THREE;

		case 2:
			return TWO;

		case 1:
			return ONE;

		case 0:
			return ZERO;

		default:

			if (mark > 12)
				return TWELVE;
			
			if (mark < 0)
				return ZERO;
		}

		return ZERO;
	}


};
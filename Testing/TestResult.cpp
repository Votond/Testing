#include "TestResult.h"

TestResult::TestResult(int correct, int incorrect) : correct(correct), incorrect(incorrect)
{
	float total = correct + incorrect;

	this->correct_perc = (float)correct / total * 100.f;
	this->incorrect_perc = (float)incorrect / total * 100.f;

	float unit = total / 12;

	this->mark = intToMarkEnum((int)round((float)correct / unit));
}

TestResult::MARK TestResult::intToMarkEnum(int mark)
{
	switch (mark)
	{
	case 12:
		return TestResult::TWELVE;

	case 11:
		return TestResult::ELEVEN;

	case 10:
		return TestResult::TEN;

	case 9:
		return TestResult::NINE;

	case 8:
		return TestResult::EIGHT;

	case 7:
		return TestResult::SEVEN;

	case 6:
		return TestResult::SIX;

	case 5:
		return TestResult::FIVE;

	case 4:
		return TestResult::FOUR;

	case 3:
		return TestResult::THREE;

	case 2:
		return TestResult::TWO;

	case 1:
		return TestResult::ONE;

	case 0:
		return TestResult::ZERO;

	default:

		if (mark > 12)
			return TestResult::TWELVE;
		
		if (mark < 0)
			return TestResult::ZERO;
	}

	return TestResult::ZERO;
}
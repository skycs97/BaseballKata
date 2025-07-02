#include <stdexcept>
#include <ctype.h>

using namespace std;

struct GuessResult {
	bool solved;
	int strikes;
	int balls;
};

class Baseball {
private:
	string question;
	constexpr static int QUESTION_LEN = 3;

	bool isAnswer(const std::string& guessNumber)
	{
		return question == guessNumber;
	}

	bool isDuplicatedNumber(const std::string& guessNumber)
	{
		return (guessNumber[0] == guessNumber[1]
			|| guessNumber[0] == guessNumber[2]
			|| guessNumber[1] == guessNumber[2]);
	}

	int checkStrikes(const std::string& guessNumber)
	{
		int strikeCnt = 0;

		for (int question_idx = 0; question_idx < QUESTION_LEN; ++question_idx) {
			if (question[question_idx] == guessNumber[question_idx]) {
				strikeCnt++;
			}
		}

		return strikeCnt;
	}

	int checkBalls(const std::string& guessNumber) {
		int ballCnt = 0;

		for (int question_idx = 0; question_idx < QUESTION_LEN; ++question_idx) {
			for (int guess_idx = 0; guess_idx < QUESTION_LEN; ++guess_idx) {
				if (question_idx == guess_idx) continue;

				if (question[question_idx] == guessNumber[guess_idx]) {
					ballCnt++;
				}
			}
		}

		return ballCnt;
	}
public:
	Baseball(const string& question)
		: question(question)
	{
	}
	GuessResult guess(const string& guessNumber) {
		assertIllegalArgument(guessNumber);

		return {
			isAnswer(guessNumber),
			checkStrikes(guessNumber),
			checkBalls(guessNumber),
		};
	}

	void assertIllegalArgument(const std::string& guessNumber)
	{
		if (guessNumber.length() != QUESTION_LEN) {
			throw length_error("Must be three letters.");
		}

		for (char ch : guessNumber) {
			if (isdigit(ch)) continue;
			throw invalid_argument("Must be number");
		}

		if (isDuplicatedNumber(guessNumber)) {
			throw invalid_argument("Mut not have the same number");
		}
	}
};
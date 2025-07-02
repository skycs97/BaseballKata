#include <stdexcept>

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
public:
	Baseball(const string& question)
		: question(question)
	{
	}
	GuessResult guess(const string& guessNumber) {
		assertIllegalArgument(guessNumber);
		
		bool solved = false;
		int strike = 0;
		int ball = 0;

		for (int idx = 0; idx < QUESTION_LEN; ++idx) {
			if (question[idx] == guessNumber[idx]) {
				strike++;
			}
		}

		if (strike == QUESTION_LEN) {
			solved = true;
		}
		else {
			for (int a = 0; a < QUESTION_LEN; ++a) {
				for (int b = 0; b < QUESTION_LEN; ++b) {
					if (a == b) continue;

					if (question[a] == guessNumber[b]) {
						ball++;
					}
				}
			}
		}

		return { solved, strike, ball };

	}
	void assertIllegalArgument(const std::string& guessNumber)
	{
		if (guessNumber.length() != QUESTION_LEN) {
			throw length_error("Must be three letters.");
		}

		for (char ch : guessNumber) {
			if (ch >= '0' && ch <= '9') continue;
			throw invalid_argument("Must be number");
		}

		if (isDuplicatedNumber(guessNumber)) {
			throw invalid_argument("Mut not have the same number");
		}
	}
	bool isDuplicatedNumber(const std::string& guessNumber)
	{
		return (guessNumber[0] == guessNumber[1]
			|| guessNumber[0] == guessNumber[2]
			|| guessNumber[1] == guessNumber[2]);
	}
};
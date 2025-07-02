#include "gmock/gmock.h"
#include "baseball.cpp"

class BaseballFixture : public testing::Test {
public:
	Baseball game{ "123" };
	void assertIllegalArgument(const string& guessNumber) {
		try {
			game.guess(guessNumber);
			FAIL();
		}
		catch (exception e) {

		}
	}

	void checkGuessResult(const GuessResult& expected, const string& guessNumber) {
		GuessResult actual = game.guess(guessNumber);

		EXPECT_EQ(expected.solved, actual.solved);
		EXPECT_EQ(expected.strikes, actual.strikes);
		EXPECT_EQ(expected.balls, actual.balls);
	}
};

TEST_F(BaseballFixture, ThrowExceptionWHenInvalidCase) {
	assertIllegalArgument("12");
	assertIllegalArgument("12s");
	assertIllegalArgument("121");
}

TEST_F(BaseballFixture, ResurnSolvedResultIfMatchedNumber) {
	GuessResult expected = { true, 3, 0 };
	checkGuessResult(expected, "123");
}

TEST_F(BaseballFixture, Check_2_Strike_0_Ball) {
	GuessResult expected = { false, 2, 0 };
	checkGuessResult(expected, "124");
}

TEST_F(BaseballFixture, Check_1_Strike_2_Ball) {
	GuessResult expected = { false, 1, 2 };
	checkGuessResult(expected, "321");
}

int main(void) {
	::testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}
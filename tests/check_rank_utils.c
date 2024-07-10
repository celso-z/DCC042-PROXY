#include <check.h>
#include "../include/rank_utils.h"

START_TEST(test_win_expectation){

	double prob = getWinExpectation(100, 100);
	ck_assert_double_eq(prob, 0.5);

}
END_TEST
int main(void){

	return 0;
}

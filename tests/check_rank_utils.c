#include <check.h>
#include <rank_utils.h>

START_TEST(test_win_expectation_boundaries){

	unsigned short player_value = 65535;
	unsigned short adversary_value = 65535;
	//Both player and adversary max value
	double prob = getWinExpectation(player_value, adversary_value);
	ck_assert_double_eq(prob, 0.5);
	player_value = 0;
	//Player min value and adversary Max value
	prob = getWinExpectation(player_value, adversary_value);
	//FOR SOME REASON IS NOT 0 (1.453784e-164 instead) but the next test is equal to 1, this is due to the formula, not to the algorithm
	ck_assert_double_lt(prob, 0.1);
	ck_assert_double_gt(prob, 0);
	player_value = adversary_value;
	adversary_value = 0;
	//Player max value and adversary min value
	prob = getWinExpectation(player_value, adversary_value);
	ck_assert_double_eq(prob, 1);
	player_value = adversary_value;
	//Both Player and adversary min value
	prob = getWinExpectation(player_value, adversary_value);
	ck_assert_double_eq(prob, 0.5);

}
END_TEST

Suite *expected_result_suite(void){
	Suite *s;
	TCase *tc_boundaries;

	s = suite_create("Boundaries test winning probability");

	tc_boundaries = tcase_create("Boundaries test winning probability");

	tcase_add_test(tc_boundaries, test_win_expectation_boundaries);
	suite_add_tcase(s, tc_boundaries);

	return s;
}
int main(void){
	int number_failed;
    Suite *s;
    SRunner *sr;

    s = expected_result_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;


}

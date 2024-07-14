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

START_TEST(test_match_upper_boundaries){
	//Check match function for upper boundaries overflows
	unsigned short player_value = 65535;
	unsigned short adversary_value = 65535;
	unsigned char result = 1;
	unsigned short *new_values = NULL;

	new_values = match(player_value, adversary_value, result);
	//Test for overflow in the player value
	ck_assert_msg(new_values != NULL && (new_values[0] == 65535 && new_values[1] == 65519), "Match function causing overflow on player value!\nResults = %d %d\n", new_values[0], new_values[1]);
	free(new_values);
	result = 0;
	new_values = match(player_value, adversary_value, result);
	//Test for overflow in the adversary value
	ck_assert_msg(new_values != NULL && (new_values[0] == 65519 && new_values[1] == 65535), "Match function causing overflow on adversary value!\nResults = %d %d\n", new_values[0], new_values[1]);
	free(new_values);
}
END_TEST

START_TEST(test_match_lower_boundaries){
	//Check match function for lower boundaries underflows
	unsigned short player_value = 0;
	unsigned short adversary_value = 0;
	unsigned char result = 0;
	unsigned short *new_values = NULL;

	new_values = match(player_value, adversary_value, result);
	//Test for underflow in the player value
	ck_assert_msg(new_values != NULL && (new_values[0] == 0 && new_values[1] == 16), "Match function causing underflow on player value!\nResults = %d %d\n", new_values[0], new_values[1]);
	free(new_values);
	result = 1;
	new_values = match(player_value, adversary_value, result);
	//Test for underflow in the adversary value
	ck_assert_msg(new_values != NULL && (new_values[0] == 16 && new_values[1] == 0), "Match function causing underflow on adversary value!\nResults = %d %d\n", new_values[0], new_values[1]);
	free(new_values);
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

Suite *match_suite(void){
	Suite *s;
	TCase *tc_match_boundaries;

	s = suite_create("Boundaries test match function");

	tc_match_boundaries = tcase_create("Boundaries test match function");

	tcase_add_test(tc_match_boundaries, test_match_upper_boundaries);
	tcase_add_test(tc_match_boundaries, test_match_lower_boundaries);
	suite_add_tcase(s, tc_match_boundaries);

	return s;
}

int main(void){
	int number_failed;
    Suite *expected_result_s, *match_s;
    SRunner *sr;

    expected_result_s = expected_result_suite();
	match_s = match_suite();
    sr = srunner_create(expected_result_s);
	srunner_add_suite(sr, match_s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

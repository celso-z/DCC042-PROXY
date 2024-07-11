#include <check.h>
#include <rank_utils.h>

START_TEST(test_win_expectation_bounds){

	unsigned short player_value = 100;
	unsigned short adversary_value = 100;
	double prob = getWinExpectation(player_value, adversary_value);
	ck_assert_double_eq(prob, 0.4);

}
END_TEST

Suite *expected_result_suite(void){
	Suite *s;
	TCase *tc_bounds;

	s = suite_create("Expected Results");

	tc_bounds = tcase_create("Bounds tests");

	tcase_add_test(tc_bounds, test_win_expectation_bounds);
	suite_add_tcase(s, tc_bounds);

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

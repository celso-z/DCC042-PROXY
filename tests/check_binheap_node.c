#include <check.h>
#include <binheap_node.h>
#include <remote_ref.h>
#include <string.h>

remote_ref *r;
struct binheap_node *node;

void setup(void){

	r = init_remote_ref("127.0.0.1");
}

void teardown(void){

	free_remote_ref(&r);
	free_binheap_node(&node);

}

START_TEST(test_init_binheap_node){
	node = init_binheap_node(NULL);
	ck_assert_msg(node == NULL, "init_binheap_node should return NULL given an empty address\n");
	free_binheap_node(&node);
	node = init_binheap_node(r);
	ck_assert_msg(node != NULL, "init_binheap_node should return a valid binomial heap node given an valid argument");
	ck_assert_msg(node->value != NULL, "init_binheap_node should return a valid binomial heap node given an valid argument");
	ck_assert_msg(strcmp((node->value)->addr_str, "127.0.0.1") == 0, "init_binheap_node should return a valid binomial heap node given an valid argument");
}
END_TEST

START_TEST(test_get_node_score){
	node = init_binheap_node(r);
	uint16_t score = get_node_score(NULL);
	ck_assert_msg(score == UINT16_MAX, "get_node_score should return an error code after an invalid reference is passed");
	score = get_node_score(node);
	ck_assert_msg(score == 1000, "get_node_score should return the same score as the reference passed for the constructor");
}
END_TEST

Suite *binheap_node_suite(void){
	Suite *s;
	TCase *tc_init_binheap_node;
	TCase *tc_get_node_score;

	s = suite_create("Test init_binheap_node");

	tc_init_binheap_node = tcase_create("Test binheap_node init");
	tc_get_node_score = tcase_create("Test binheap_node get score");

	tcase_add_test(tc_init_binheap_node, test_init_binheap_node);
	tcase_add_test(tc_get_node_score, test_get_node_score);
	tcase_add_checked_fixture(tc_init_binheap_node, setup, teardown);
	tcase_add_checked_fixture(tc_get_node_score, setup, teardown);
	suite_add_tcase(s, tc_init_binheap_node);
	suite_add_tcase(s, tc_get_node_score);

	return s;
}

int main(void){
	int number_failed;
    Suite *init_binheap_node_s;
    SRunner *sr;

    init_binheap_node_s = binheap_node_suite();
    sr = srunner_create(init_binheap_node_s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

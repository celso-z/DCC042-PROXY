#include <check.h>
#include <remote_ref.h>
remote_ref *remote_a, *remote_b;

void setup(void){

	remote_a = init_remote_ref("127.0.0.1");
	remote_b = init_remote_ref("127.0.0.1");
	remote_a->download_rate = remote_b->download_rate = 12.3;
	remote_a->upload_rate = remote_b->upload_rate = 8.4;
	remote_a->connection_hits = remote_b->connection_hits = 129;
}

void teardown(void){

	free_remote_ref(remote_a);
	free_remote_ref(remote_b);
}

START_TEST(test_remote_ref_init){
	remote_ref *r = init_remote_ref("");
	ck_assert_msg(r == NULL, "remote_ref_init should return NULL given an empty address\n");
	free_remote_ref(r);
	r = init_remote_ref("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
	ck_assert_msg(r == NULL, "remote_ref_init should return NULL given an argument over 255 octets long");
	free_remote_ref(r);
	r = init_remote_ref("127.0.0.1");
	ck_assert_msg(r != NULL, "Sanity check");
	free_remote_ref(r);
}
END_TEST

START_TEST(test_remote_confrontation){
	ck_assert_msg(confrontation(remote_a, remote_b) == 0, "In case of a confrontation draw, the second remote should win");
	remote_a->download_rate += 9;
	remote_a->upload_rate += 9;
	ck_assert_msg(confrontation(remote_a, remote_b) == 1, "Confrontation first remote win ERROR");
	ck_assert_msg(confrontation(remote_b, remote_a) == 0, "Confrontation second remote win ERROR");
	ck_assert_msg(confrontation(NULL, remote_b) == UINT8_MAX, "In case of any NULL arguments, the function should return the max integer");
	ck_assert_msg(confrontation(remote_a, NULL) == UINT8_MAX, "In case of any NULL arguments, the function should return the max integer");
	ck_assert_msg(confrontation(NULL, NULL) == UINT8_MAX,  "In case of any NULL arguments, the function should return the max integer");

}
END_TEST

Suite *remote_ref_init_suite(void){
	Suite *s;
	TCase *tc_invalid_address, *tc_confrontation;

	s = suite_create("Test remote_ref_init");

	tc_invalid_address = tcase_create("Test remote_ref invalid address");
	tc_confrontation = tcase_create("Test remote_ref confrontation function");

	tcase_add_test(tc_invalid_address, test_remote_ref_init);
	tcase_add_test(tc_confrontation, test_remote_confrontation);
	tcase_add_checked_fixture(tc_confrontation, setup, teardown);
	suite_add_tcase(s, tc_invalid_address);
	suite_add_tcase(s, tc_confrontation);

	return s;
}

int main(void){
	int number_failed;
    Suite *remote_ref_init_s;
    SRunner *sr;

    remote_ref_init_s = remote_ref_init_suite();
    sr = srunner_create(remote_ref_init_s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

#include <check.h>
#include <remote_ref.h>

START_TEST(test_remote_ref_init){
	remote_ref *r = init_remote_ref("");
	ck_assert_msg(r == NULL, "remote_ref_init should return NULL given an empty address\n");
	free_remote_ref(r);
	r = init_remote_ref("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
	ck_assert_msg(r == NULL, "remote_ref_init should return NULL given an argument over 253 octets long");
	free_remote_ref(r);
	r = init_remote_ref("127.0.0.1");
	ck_assert_msg(r != NULL, "Sanity check");
	free_remote_ref(r);
}
END_TEST

Suite *remote_ref_init_suite(void){
	Suite *s;
	TCase *tc_invalid_address;

	s = suite_create("Test remote_ref_init");

	tc_invalid_address = tcase_create("Test remote_ref invalid address");

	tcase_add_test(tc_invalid_address, test_remote_ref_init);
	suite_add_tcase(s, tc_invalid_address);

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

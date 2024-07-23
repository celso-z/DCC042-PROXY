#include <check.h>
#include <peer_storage.h>
remote_ref *r;

void setup(void){
	r = init_remote_ref("Test");
}

void teardown(void){

	free_remote_ref(r);
}

START_TEST(test_serialization){
	int8_t rc = 0;
	rc = serialize(NULL, "");
	ck_assert_msg(rc == -1, "Serialize should return error when given NULL remote_ref");
	rc = serialize(r, NULL);
	ck_assert_msg(rc == -1, "Serialize should return error when given NULL file_name");
	rc = serialize(NULL, NULL);
	ck_assert_msg(rc == -1, "Serialize should return error when given NULL remote_ref and file_name");
	rc = serialize(r, "");
	ck_assert_msg(rc == 0, "Failed sanity check");
	
}
END_TEST

START_TEST(test_deserialization){

}
END_TEST

Suite *peer_storage_suite(void){
	Suite *s;
	TCase *tc_serialization;

	s = suite_create("Test serialization");

	tc_serialization = tcase_create("Test serialization");

	tcase_add_test(tc_serialization, test_serialization);
	tcase_add_checked_fixture(tc_serialization, setup, teardown);
	suite_add_tcase(s, tc_serialization);

	return s;
}

int main(void){
	int number_failed;
    Suite *remote_storage_s;
    SRunner *sr;

    remote_storage_s = peer_storage_suite();
    sr = srunner_create(remote_storage_s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

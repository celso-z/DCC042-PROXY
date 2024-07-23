#include <check.h>
#include <peer_storage.h>
#include <unistd.h>
remote_ref *r;

void setup(void){
	r = init_remote_ref("Test");
}

void teardown(void){

	free_remote_ref(r);
}

void setup_deserialize(void){
	uint8_t rc = 0;
	r = init_remote_ref("127.0.0.1");
	r->score = 999;
	r->download_rate = 12.5;
	r->upload_rate = 12.5;
	rc = serialize(r, "");
	free_remote_ref(r);
	r = NULL;
}

void teardown_deserialize(void){
	//execl("/bin/sh", "sh", "-c", "rm -f", "./doc/peer_list.bin", (char *) NULL);
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

START_TEST(test_deserialization_args){
	r = deserialize("", -1);
	ck_assert_msg(r == NULL, "Should return NULL after negative offset\n");
	r = deserialize(NULL, 0);
	ck_assert_msg(r == NULL, "Should return NULL after NULL filename\n");
	r = deserialize("", 999999);
	ck_assert_msg(r == NULL, "Should return NULL after overflow in offset\n");
}
END_TEST

START_TEST(test_deserialization){
	r = deserialize("", 1);
	ck_assert_msg(r != NULL, "DESERIALIZATION ERROR\n");
	ck_assert_msg(r->score == 999, "DESERIALIZATION ERROR, remote_ref fields are not stored correctly\n", r->score);
	ck_assert_msg(r->download_rate == 12.5, "DESERIALIZATION ERROR, remote_ref fields are not stored correctly\n");
	ck_assert_msg(r->upload_rate == 12.5, "DESERIALIZATION ERROR, remote_ref fields are not stored correctly\n");
	r = deserialize("", 0);
	ck_assert_msg(r != NULL, "DESERIALIZATION ERROR\n");
	ck_assert_msg(!strcmp(r->addr_str, "Test"), "DESERIALIZATION ERROR, remote_ref fields are not stored correctly %s\n", r->addr_str);
	free_remote_ref(r);
	
}
END_TEST

Suite *peer_storage_suite(void){
	Suite *s;
	TCase *tc_serialization;
	TCase *tc_deserialization_args;
	TCase *tc_deserialization;

	s = suite_create("Test serialization");

	tc_serialization = tcase_create("Test serialization");
	tc_deserialization_args = tcase_create("Test deserialization args");
	tc_deserialization = tcase_create("Test deserialization");

	tcase_add_test(tc_serialization, test_serialization);
	tcase_add_test(tc_deserialization_args, test_deserialization_args);
	tcase_add_test(tc_deserialization, test_deserialization);

	tcase_add_checked_fixture(tc_serialization, setup, teardown);
	tcase_add_checked_fixture(tc_deserialization_args, setup, teardown);
	tcase_add_checked_fixture(tc_deserialization, setup_deserialize, teardown_deserialize);

	suite_add_tcase(s, tc_serialization);
	suite_add_tcase(s, tc_deserialization_args);
	suite_add_tcase(s, tc_deserialization);

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

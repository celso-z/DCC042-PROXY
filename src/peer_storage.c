#include <peer_storage.h>

int8_t serialize(remote_ref *r, const char *file_name){
	if(r == NULL) return -1;
	if(file_name == NULL) return -1;

	FILE *fp;
	int rc = 0;

	if(strlen(file_name)) fp = fopen(file_name, "ab+");
	else fp = fopen(DEFAULT_DESTINATION, "ab+");
	
	if(fp == NULL)  return -2;

	rc = fwrite((void *)r, sizeof(remote_ref), 1, fp);
	fclose(fp);
	if(rc != 1) return -3;

	
	return 0;
}

remote_ref *deserialize(const char *file_name, long offset){
	FILE *fp;
	remote_ref *r = calloc(1, sizeof(remote_ref));
	int file_size = 0;
	uint8_t rc = 0;

	if(r == NULL) return NULL;
	if(strlen(file_name)) fp = fopen(file_name, "rb+");
	else fp = fopen(DEFAULT_DESTINATION, "rb+");

	if(fp == NULL) return NULL;
	fseek(fp, 0, SEEK_END);
	file_size = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	rc = fread((void *)r, sizeof(remote_ref), 1, fp);
	fclose(fp);
	if(rc != 1) return NULL;
	return r;
}

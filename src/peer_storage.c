#include <peer_storage.h>

int8_t serialize(remote_ref *r, const char *file_name){
	if(r == NULL) return -1;

	FILE *fp;
	int rc = 0;

	if(strlen(file_name)) fp = fopen(file_name, "wb+");
	else fp = fopen(DEFAULT_DESTINATION, "wb+");
	
	if(fp == NULL)  return -1;

	rc = fwrite((void *)r, sizeof(remote_ref), 1, fp);
	fclose(fp);
	if(rc != 1) return -1;

	
	return 0;
}

remote_ref *deserialize(const char *file_name){
	FILE *fp;
	remote_ref *r = calloc(1, sizeof(remote_ref));
	uint8_t rc = 0;

	if(r == NULL) return NULL;
	if(strlen(file_name)) fp = fopen(file_name, "rb+");
	else fp = fopen(DEFAULT_DESTINATION, "rb+");

	if(fp == NULL) return NULL;

	rc = fread((void *)r, sizeof(remote_ref), 1, fp);
	fclose(fp);
	if(rc != 1) return NULL;
	return r;
}

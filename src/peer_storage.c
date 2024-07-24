#include <peer_storage.h>

int8_t serialize(remote_ref *r, const char *file_name){
	struct addrinfo *tmp = NULL;

	if(r == NULL) return -1;
	if(file_name == NULL) return -1;

	FILE *fp;
	int rc = 0;

	if(strlen(file_name)) fp = fopen(file_name, "ab+");
	else fp = fopen(DEFAULT_DESTINATION, "ab+");
	
	if(fp == NULL)  return -2;

	tmp = r->addr;
	r->addr = NULL; //addrinfo should not be saved, it will not be useful after the current session
	rc = fwrite((void *)r, sizeof(remote_ref), 1, fp);
	r->addr = tmp;
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
	if(file_name == NULL) return NULL;
	if(offset < 0) return NULL;
	if(strlen(file_name)) fp = fopen(file_name, "rb+");
	else fp = fopen(DEFAULT_DESTINATION, "rb+");

	if(fp == NULL) return NULL;
	rc = fseek(fp, offset * sizeof(remote_ref), SEEK_SET);
	if(rc == -1){
		fclose(fp);
		return NULL;
	}

	rc = fread((void *)r, sizeof(remote_ref), 1, fp);
	fclose(fp);
	if(rc != 1) return NULL;
	return r;
}

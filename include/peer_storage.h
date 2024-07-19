#ifndef PEER_STORAGE_H
#define PEER_STORAGE_H
#include <stdio.h>
#include <stdlib.h>
#include <remote_ref.h>
#include <string.h>

#define DEFAULT_DESTINATION "../doc/peer_list.bin"

int8_t serialize(remote_ref *r, const char* file_name);
remote_ref* deserialize(const char *file_name);

#endif

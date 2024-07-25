#ifndef REMOTE_REF_H
#define REMOTE_REF_H
#include <string.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <stdint.h>

#define ADDR_SIZE 256 //https://datatracker.ietf.org/doc/html/rfc1034

typedef struct remote_ref{
	char addr_str[ADDR_SIZE];
	struct addrinfo *addr;
	uint16_t score;
	float download_rate;
	float upload_rate;
	uint32_t connection_hits;
}remote_ref;

remote_ref *init_remote_ref(const char *addr_str);
void free_remote_ref(remote_ref **r);
uint8_t confrontation(remote_ref *remote_a, remote_ref *remote_b);

#endif

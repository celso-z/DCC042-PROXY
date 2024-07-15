#include <string.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>

typedef struct remote_ref{
	struct addrinfo *addr;
	unsigned short score;
	float download_rate;
	float upload_rate;
}remote_ref;

remote_ref *init_remote_ref(const char *address);
void free_remote_ref(remote_ref *r);
int confrontation(remote_ref *remote_a, remote_ref *remote_b);

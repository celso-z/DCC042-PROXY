#include <remote_ref.h>

#define PORT "5559" //ESSA INFORMAÇÃO SERÁ PASSADA PARA OUTRO PACOTE FUTURAMENTE, ESTÁ AQUI MOMENTANEAMENTE FICARÁ NO PACOTE SOCKET-TOOLS

remote_ref *init_remote_ref(const char *addr_str){
	size_t address_length = strlen(addr_str);
	if(address_length >= ADDR_SIZE || address_length == 0) return NULL; 
	remote_ref *new_ref = malloc(sizeof(remote_ref));

	if(new_ref == NULL) return new_ref;
	strcpy(new_ref->addr_str, addr_str);
	struct addrinfo hints;
	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC; 
	hints.ai_socktype = 0;
	/* TODO=
	 * new_ref->dowload_rate = getDownloadRate(new_ref->addr)
	 * new_ref->upload_rate = getDownloadRate(new_ref->addr)
	 */
	new_ref->connection_hits = new_ref->download_rate = new_ref->upload_rate = 0;
	new_ref->score = 1000;
	int rc = getaddrinfo(addr_str,PORT, &hints, &new_ref->addr);
	if(rc == 0) new_ref->connection_hits = (1 << 31); //Remote host online, update connection_hits, otherwhise do nothing
	
	return new_ref;
}

void free_remote_ref(remote_ref **r){

	if(r == NULL) return;
	if(*r == NULL) return;
	if((*r)->addr != NULL) freeaddrinfo((*r)->addr);
	free(*r);
	*r = NULL;
}

uint8_t confrontation(remote_ref *remote_a, remote_ref *remote_b){

	if(remote_a == NULL || remote_b == NULL) return UINT8_MAX;
	int8_t weights[] = {10, 10, 15};
	int8_t confrontation_score = 0;
	if(remote_a->download_rate > remote_b->download_rate){
		confrontation_score -= weights[0];
	}else confrontation_score += weights[0];
	if(remote_a->upload_rate > remote_b->upload_rate){
		confrontation_score -= weights[1];
	}else confrontation_score += weights[1];
	if(remote_a->connection_hits > remote_b->connection_hits){
		confrontation_score -= weights[2];
	}else confrontation_score += weights[2];

	if(confrontation_score < 0) return 1;
	return 0;
}


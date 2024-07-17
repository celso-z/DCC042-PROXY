#include <rank_utils.h>

// Get the probability of an player with a given score 
// (peer_a_score) winning a match against an adversary 
// with a given score (peer_b_score)
double getWinExpectation(uint16_t peer_a_score, uint16_t peer_b_score){
	double probability = 1 /(1 + (pow(10, ((double)peer_b_score - (double)peer_a_score) / 400.0)));
	return probability;
}

// Get the new score for two peers involved in a match, given 
// the two peers score and the result of the confrontation result
// (confrontation result interpred as : even unsigned short 
// integer if the first peer lost the match and odd unsigned
// integer otherwise, *ADVISED USING 0 FOR AND 1 RESPECTIVELY
// FOR READABILITY REASONS*)
uint16_t *match(uint16_t peer_a_score, uint16_t peer_b_score, uint8_t result){
	uint16_t *result_vector = calloc(2, sizeof(short));
	double expected_result[2] = { getWinExpectation(peer_a_score, peer_b_score), getWinExpectation(peer_b_score, peer_a_score)};

	if(result_vector == NULL) return result_vector;
	for(int i = 0; i < 2; i++){
		uint16_t current_score = 0;
		double exact_score = 0.0;

		if(i == 0) current_score = peer_a_score;
		else current_score = peer_b_score;
		exact_score = (double)current_score + K * (((i + result) % 2) - expected_result[i]);
		if(exact_score > 65535) exact_score = 65535;
		else if(exact_score < 0) exact_score = 0;
		result_vector[i] = floor(exact_score);
	}
	return result_vector;
}


#include "../include/rank_utils.h"

float getWinExpectation(unsigned short player_score, unsigned short adversary_score){
	float probability = 1 /(1 + (pow(10, ((float)adversary_score - (float)player_score) / 400)));
	return probability;
}

unsigned short *match(unsigned short score_a, unsigned short score_b, unsigned char result){
	unsigned short *result_vector = calloc(2, sizeof(short));
	float expected_result[2] = { getWinExpectation(score_a, score_b), getWinExpectation(score_b, score_a)};

	if(result_vector == NULL) return result_vector;
	for(int i = 0; i < 2; i++){
		unsigned short current_score;

		if(i == 0) current_score = score_a;
		else current_score = score_b;
		result_vector[i] = current_score + K * (((i + result) % 2) - expected_result[i]);
	}
	return result_vector;
}


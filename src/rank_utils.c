#include <rank_utils.h>

double getWinExpectation(unsigned short player_score, unsigned short adversary_score){
	double probability = 1 /(1 + (pow(10, ((double)adversary_score - (double)player_score) / 400.0)));
	return probability;
}

unsigned short *match(unsigned short score_a, unsigned short score_b, unsigned char result){
	unsigned short *result_vector = calloc(2, sizeof(short));
	double expected_result[2] = { getWinExpectation(score_a, score_b), getWinExpectation(score_b, score_a)};

	if(result_vector == NULL) return result_vector;
	for(int i = 0; i < 2; i++){
		unsigned short current_score;
		double exact_score = 0.0;

		if(i == 0) current_score = score_a;
		else current_score = score_b;
		exact_score = (double)current_score + K * (((i + result) % 2) - expected_result[i]);
		result_vector[i] = floor(exact_score);
	}
	return result_vector;
}

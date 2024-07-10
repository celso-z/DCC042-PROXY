#ifndef RANK_UTILS_H
#define RANK_UTILS_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define K 32

double getWinExpectation(unsigned short player_score, unsigned short adversary_score);

unsigned short *match(unsigned short score_a, unsigned short score_b, unsigned char result);

#endif

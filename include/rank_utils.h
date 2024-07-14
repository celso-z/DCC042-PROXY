#ifndef RANK_UTILS_H
#define RANK_UTILS_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define K 32

double getWinExpectation(unsigned short peer_a_score, unsigned short peer_b_score);

unsigned short *match(unsigned short peer_a_score, unsigned short peer_b_score, unsigned char result);

#endif

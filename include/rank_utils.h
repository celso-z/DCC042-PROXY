#ifndef RANK_UTILS_H
#define RANK_UTILS_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdint.h>

#define K 32

double getWinExpectation(uint16_t peer_a_score, uint16_t peer_b_score);

uint16_t *match(uint16_t peer_a_score, uint16_t peer_b_score, uint8_t result);

#endif

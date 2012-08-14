/*
 * Info.c
 *
 *  Created on: 13.08.2012
 *      Author: Mircea
 */

#include "Info.h"



void verify_overflow_16_bits(uint64_t x)
{
	if ((x>=128*256)||(x<-128*256))
	{
		set_overflow(CURRENT_ERR);
	}else{
		reset_overflow(CURRENT_ERR);
	}
}

void verify_overflow_32_bits(uint64_t x)
{
	int64_t m = 1LL<<31;
	if ((x>=m)||(x<-m))
	{
		set_overflow(CURRENT_ERR);
	}else{
		reset_overflow(CURRENT_ERR);
	}
}

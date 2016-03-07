#include "util.h"
#include "m_bit_set.h"

size_t
size_t_min(size_t a, size_t b)
{
	return (a < b) ? a : b;
}

size_t
compute_size(uint32_t max)
{
	return ((size_t)(max/8) + (max % 8 > 0));
}

void
cut_off(m_bit_set* bs)
{
	uint8_t mask;
	uint8_t tail;

	tail = bs->max % 8;

	if (tail == 0)
		return;

	mask = 255;
	mask >>= (8 - tail);
	mask <<= (8 - tail);

	bs->data[bs->size-1] &= mask; 
}


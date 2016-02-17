#include <stddef.h>

#include "m_bit_set.h"

static size_t
size_t_min(size_t a, size_t b)
{
	return (a < b) ? a : b;
}

int
m_bit_set_union(struct m_bit_set* bs_a, struct m_bit_set* bs_b)
{
	size_t i;

	if (bs_a == NULL || bs_a->data == NULL
	 || bs_b == NULL || bs_b->data == NULL)
		return M_BIT_SET_E_NULL;

	for (i = 0; i < size_t_min(bs_a->size, bs_b->size); i++)
		bs_a->data[i] |= bs_b->data[i];

	return M_BIT_SET_OK;
}

int
m_bit_set_intersect(struct m_bit_set* bs_a, struct m_bit_set* bs_b)
{
	size_t i;

	if (bs_a == NULL || bs_a->data == NULL
	 || bs_b == NULL || bs_b->data == NULL)
		return M_BIT_SET_E_NULL;

	for (i = 0; i < size_t_min(bs_a->size, bs_b->size); i++)
		bs_a->data[i] &= bs_b->data[i];

	return M_BIT_SET_OK;
}

int
m_bit_set_complement(struct m_bit_set* bs)
{
	size_t i;

	if (bs == NULL || bs->data == NULL)
		return M_BIT_SET_E_NULL;

	for (i = 0; i < bs->size; i++)
		bs->data[i] = ~bs->data[i];

	return M_BIT_SET_OK;
}


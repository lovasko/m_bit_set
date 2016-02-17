#include <stddef.h>
#include <string.h>

#include "m_bit_set.h"

int
m_bit_set_test(struct m_bit_set* bs, uint32_t value)
{
	if (bs == NULL || bs->data == NULL)
		return M_BIT_SET_E_NULL;

	if (value >= bs->max)
		return M_BIT_SET_E_RANGE;

	return !!(bs->data[value / 8] & (1 << (value % 8)));
}

int
m_bit_set_add(struct m_bit_set* bs, uint32_t value)
{
	if (bs == NULL || bs->data == NULL)
		return M_BIT_SET_E_NULL;

	if (value >= bs->max)
		return M_BIT_SET_E_RANGE;

	bs->data[value/8] |= (1 << (value % 8));
	return M_BIT_SET_OK;
}

int
m_bit_set_add_all(struct m_bit_set* bs)
{
	if (bs == NULL || bs->data == NULL)
		return M_BIT_SET_E_NULL;

	memset(bs->data, 0xff, bs->size);

	return M_BIT_SET_OK;
}

int
m_bit_set_remove(struct m_bit_set* bs, uint32_t value)
{
	if (bs == NULL || bs->data == NULL)
		return M_BIT_SET_E_NULL;

	if (value >= bs->max)
		return M_BIT_SET_E_RANGE;

	bs->data[value/8] &= 0xff ^ (1 << (value % 8));

	return M_BIT_SET_OK;
}

int
m_bit_set_remove_all(struct m_bit_set* bs)
{
	if (bs == NULL || bs->data == NULL)
		return M_BIT_SET_E_NULL;

	memset(bs->data, 0, bs->size);

	return M_BIT_SET_OK;
}


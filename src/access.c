#include <stddef.h>
#include <string.h>

#include "m_bit_set.h"
#include "util.h"

int
m_bit_set_test(m_bit_set* bs, uint32_t value)
{
	if (bs == NULL || bs->data == NULL)
		return M_BIT_SET_E_NULL;

	if (value >= bs->max)
		return M_BIT_SET_E_RANGE;

	return !!(bs->data[value / 8] & (1 << (value % 8)));
}

int
m_bit_set_add(m_bit_set* bs, uint32_t value)
{
	if (bs == NULL || bs->data == NULL)
		return M_BIT_SET_E_NULL;

	if (value >= bs->max)
		return M_BIT_SET_E_RANGE;

	bs->data[value/8] |= (1 << (value % 8));
	return M_BIT_SET_OK;
}

int
m_bit_set_add_all(m_bit_set* bs)
{
	if (bs == NULL || bs->data == NULL)
		return M_BIT_SET_E_NULL;

	memset(bs->data, 0xff, bs->size);
	cut_off(bs);

	return M_BIT_SET_OK;
}

int
m_bit_set_remove(m_bit_set* bs, uint32_t value)
{
	if (bs == NULL || bs->data == NULL)
		return M_BIT_SET_E_NULL;

	if (value >= bs->max)
		return M_BIT_SET_E_RANGE;

	bs->data[value/8] &= 0xff ^ (1 << (value % 8));

	return M_BIT_SET_OK;
}

int
m_bit_set_remove_all(m_bit_set* bs)
{
	if (bs == NULL || bs->data == NULL)
		return M_BIT_SET_E_NULL;

	memset(bs->data, 0, bs->size);
	cut_off(bs);

	return M_BIT_SET_OK;
}


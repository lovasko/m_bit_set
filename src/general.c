#include <stdlib.h>
#include <string.h>

#include "m_bit_set.h"
#include "util.h"

int
m_bit_set_init(m_bit_set* bs, uint32_t max, uint8_t fill, uint8_t* data)
{
	if (bs == NULL)
		return M_BIT_SET_E_NULL;

	if (max == 0)
		return M_BIT_SET_E_SIZE;

	if (fill != M_BIT_SET_TRUE && fill != M_BIT_SET_FALSE)
		return M_BIT_SET_E_VALUE;

	bs->size = compute_size(max);
	bs->max = max;

	if (data == NULL) {
		bs->data = malloc(bs->size);
		bs->own_memory = 1;
	}
	else {
		bs->data = data;
		bs->own_memory = 0;
	}

	memset(bs->data, fill == M_BIT_SET_TRUE ? 255 : 0, bs->size);
	cut_off(bs);

	return M_BIT_SET_OK;
}

int
m_bit_set_free(m_bit_set* bs)
{
	if (bs == NULL)
		return M_BIT_SET_E_NULL;

	if (bs->own_memory)
		free(bs->data);

	return M_BIT_SET_OK;
}

int
m_bit_set_copy(m_bit_set* bs_dst, m_bit_set* bs_src)
{
	if (bs_src == NULL || bs_src->data == NULL
	 || bs_dst == NULL || bs_dst->data == NULL)
		return M_BIT_SET_E_NULL;

	memcpy(bs_dst->data, bs_src->data,
	       size_t_min(bs_src->size, bs_dst->size));

	return M_BIT_SET_OK;
}

int
m_bit_set_dup(m_bit_set* bs_dup, m_bit_set* bs_orig, uint8_t* data)
{
	if (bs_dup == NULL || bs_dup->data == NULL
	 || bs_orig == NULL || bs_orig->data == NULL)
	 	return M_BIT_SET_E_NULL;

	if (data == NULL) {
		bs_dup->data = malloc(bs_orig->size);
		bs_dup->own_memory = 0;
	} else {
		bs_dup->data = data;
		bs_dup->own_memory = 1;
	}

	bs_dup->size = bs_orig->size;
	bs_dup->max = bs_orig->max;
	memcpy(bs_dup->data, bs_orig->data, bs_orig->size);

	return M_BIT_SET_OK;
}

int
m_bit_set_resize(m_bit_set* bs, uint32_t new_max, uint8_t fill)
{
	uint32_t new_size;
	uint8_t mask;

	if (bs == NULL)
		return M_BIT_SET_E_NULL;

	if (new_max == 0)
		return M_BIT_SET_E_COUNT;

	if (fill != M_BIT_SET_TRUE && fill != M_BIT_SET_FALSE)
		return M_BIT_SET_E_VALUE;

	if (bs->max == new_max)
		return M_BIT_SET_OK;

	new_size = compute_size(new_max);

	if (bs->own_memory)
		bs->data = realloc(bs->data, bs->size);

	if (bs->max < new_max) {
		if (bs->max % 8 != 0) {
			mask = (uint8_t)(1 << (8 - bs->max % 8)) - 1;

			if (fill == M_BIT_SET_TRUE)
				bs->data[bs->size - 1] |= ~mask;
			else
				bs->data[bs->size - 1] &= mask;
		}

		memset(bs->data + bs->size,
		       fill == M_BIT_SET_TRUE ? 255 : 0,
		       new_size - bs->size);
		cut_off(bs);
	}

	bs->size = compute_size(new_max);
	bs->max = new_max;

	return M_BIT_SET_OK;
}

int
m_bit_set_error_string(int code, char** out_error_string)
{
	char* error_strings[] = {
		"False",
		"True",
		"OK",
		"One of the objects is NULL",
		"Size of the memory is zero",
		"Value out of range",
		"I/O error",
		"Unknown return code",
		"Magic number mismatch"
	};

	if (out_error_string == NULL)
		return M_BIT_SET_E_NULL;

	if (code < 0 || code > M_BIT_SET_E_MAX) {
		*out_error_string = NULL;
		return M_BIT_SET_E_UNKNOWN_CODE;
	}

	*out_error_string = error_strings[code];
	return M_BIT_SET_OK;
}


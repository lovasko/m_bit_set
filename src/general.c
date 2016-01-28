#include <stdlib.h>
#include <string.h>

#include "m_smallintset.h"

int
m_smallintset_init(struct m_smallintset* sis, uint64_t max, uint8_t* data)
{
	if (sis == NULL)
		return M_SMALLINTSET_E_NULL;

	if (max == 0)
		return M_SMALLINTSET_E_SIZE;

	sis->size = (size_t)(max/8) + 1;

	if (data == NULL) {
		sis->data = malloc(sis->size);
		sis->own_memory = 1;
	}
	else {
		sis->data = data;
		sis->own_memory = 0;
	}

	return M_SMALLINTSET_OK;
}

int
m_smallintset_free(struct m_smallintset* sis)
{
	if (sis == NULL)
		return M_SMALLINTSET_E_NULL;

	if (sis->own_memory)
		free(sis->data);

	return M_SMALLINTSET_OK;
}

static size_t
size_t_min(size_t a, size_t b)
{
	return (a < b) ? a : b;
}

int
m_smallintset_copy(struct m_smallintset* sis_src,
                   struct m_smallintset* sis_dst)
{
	if (sis_src == NULL || sis_src->data == NULL
	 || sis_dst == NULL || sis_dst->data == NULL)
		return M_SMALLINTSET_E_NULL;

	memcpy(sis_dst->data,
	       sis_src->data,
	       size_t_min(sis_src->size, sis_dst->size));

	return M_SMALLINTSET_OK;
}

int
m_smallintset_error_string(int code, char** out_error_string)
{
	char* error_strings[] = {
		"False",
		"True",
		"OK",
		"One of the objects is NULL",
		"Size of the memory is zero",
		"Unknown return code"
	};

	if (out_error_string == NULL)
		return M_SMALLINTSET_E_NULL;

	if (code < 0 || code > M_SMALLINTSET_E_MAX) {
		*out_error_string = NULL;
		return M_SMALLINTSET_E_UNKNOWN_CODE;
	}

	*out_error_string = error_strings[code];
	return M_SMALLINTSET_OK;
}

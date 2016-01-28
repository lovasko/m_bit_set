#include <stddef.h>

#include "m_smallintset.h"

static size_t
size_t_min(size_t a, size_t b)
{
	return (a < b) ? a : b;
}

int
m_smallintset_union(struct m_smallintset* sis_a,
                    struct m_smallintset* sis_b)
{
	size_t i;

	if (sis_a == NULL || sis_a->data == NULL
	 || sis_b == NULL || sis_b->data == NULL)
		return M_SMALLINTSET_E_NULL;

	for (i = 0; i < size_t_min(sis_a->size, sis_b->size); i++)
		sis_a->data[i] |= sis_b->data[i];

	return M_SMALLINTSET_OK;
}

int
m_smallintset_intersect(struct m_smallintset* sis_a,
                        struct m_smallintset* sis_b)
{
	size_t i;

	if (sis_a == NULL || sis_a->data == NULL
	 || sis_b == NULL || sis_b->data == NULL)
		return M_SMALLINTSET_E_NULL;

	for (i = 0; i < size_t_min(sis_a->size, sis_b->size); i++)
		sis_a->data[i] &= sis_b->data[i];

	return M_SMALLINTSET_OK;
}

int
m_smallintset_complement(struct m_smallintset* sis)
{
	size_t i;

	if (sis == NULL || sis->data == NULL)
		return M_SMALLINTSET_E_NULL;

	for (i = 0; i < sis->size; i++)
		sis->data[i] = ~sis->data[i];

	return M_SMALLINTSET_OK;
}


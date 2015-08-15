#include <stddef.h>
#include <string.h>

#include "m_smallintset.h"

int
m_smallintset_contains(struct m_smallintset* sis, uint16_t value)
{
	if (sis == NULL || sis->data == NULL)
		return M_SMALLINTSET_E_NULL;

	return !!(sis->data[value / 8] & (1 << (value % 8)));
}

int
m_smallintset_add(struct m_smallintset* sis, uint16_t value)
{
	if (sis == NULL || sis->data == NULL)
		return M_SMALLINTSET_E_NULL;

	sis->data[value/8] |= (1 << (value % 8));
	return M_SMALLINTSET_OK;
}

int
m_smallintset_add_all(struct m_smallintset* sis)
{
	if (sis == NULL || sis->data == NULL)
		return M_SMALLINTSET_E_NULL;

	memset(sis->data, 0xff, 8192);
	return M_SMALLINTSET_OK;
}

int
m_smallintset_remove(struct m_smallintset* sis, uint16_t value)
{
	if (sis == NULL || sis->data == NULL)
		return M_SMALLINTSET_E_NULL;

	sis->data[value/8] &= 0xff ^ (1 << (value % 8));
	return M_SMALLINTSET_OK;
}

int
m_smallintset_remove_all(struct m_smallintset* sis)
{
	if (sis == NULL || sis->data == NULL)
		return M_SMALLINTSET_E_NULL;

	memset(sis->data, 0, 8192);
	return M_SMALLINTSET_OK;
}


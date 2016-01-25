#include <stdlib.h>
#include <string.h>

#include "m_smallintset.h"

int
m_smallintset_init(struct m_smallintset* sis)
{
	if (sis == NULL)
		return M_SMALLINTSET_E_NULL;

	sis->data = malloc(8192);

	return M_SMALLINTSET_OK;
}

int
m_smallintset_copy(struct m_smallintset* sis_src,
                   struct m_smallintset* sis_dst)
{
	if (sis_src == NULL || sis_src->data == NULL
	 || sis_dst == NULL || sis_dst->data == NULL)
		return M_SMALLINTSET_E_NULL;

	memcpy(sis_dst->data, sis_src->data, 8192);
	return M_SMALLINTSET_OK;
}


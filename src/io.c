#include <unistd.h>

#include "m_smallintset.h"

int
m_smallintset_read(struct m_smallintset* sis, int fd)
{
	if (sis == NULL)
		return M_SMALLINTSET_E_NULL;
		
	read(fd, sis->data, 0x2000);
	return M_SMALLINTSET_OK;
}

int
m_smallintset_write(struct m_smallintset* sis, int fd)
{
	if (sis == NULL)
		return M_SMALLINTSET_E_NULL;
		
	write(fd, sis->data, 0x2000);
	return M_SMALLINTSET_OK;
}


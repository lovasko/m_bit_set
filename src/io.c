#include <unistd.h>

#include "m_smallintset.h"

int
m_smallintset_read(struct m_smallintset* sis, int fd)
{
	uint64_t size;

	if (sis == NULL)
		return M_SMALLINTSET_E_NULL;
		
	read(fd, &size, sizeof(uint64_t));
	read(fd, sis->data, (size_t)size);

	return M_SMALLINTSET_OK;
}

int
m_smallintset_write(struct m_smallintset* sis, int fd)
{
	uint64_t size;

	if (sis == NULL)
		return M_SMALLINTSET_E_NULL;
		
	size = (uint64_t)sis->size;
	write(fd, &size, sizeof(uint64_t));
	write(fd, sis->data, sis->size);

	return M_SMALLINTSET_OK;
}


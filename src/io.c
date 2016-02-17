#include <sys/endian.h>
#include <unistd.h>

#include "m_bit_set.h"

int
m_bit_set_read(struct m_bit_set* bs, int fd)
{
	uint32_t size;

	if (bs == NULL)
		return M_BIT_SET_E_NULL;
		
	read(fd, &size, sizeof(uint32_t));
	bs->size = 

	read(fd, bs->data, (size_t)size);

	return M_BIT_SET_OK;
}

int
m_bit_set_write(struct m_bit_set* bs, int fd)
{
	uint32_t size;

	if (bs == NULL)
		return M_BIT_SET_E_NULL;
		
	size = (uint32_t)bs->size;
	write(fd, &size, sizeof(uint32_t));
	write(fd, bs->data, bs->size);

	return M_BIT_SET_OK;
}


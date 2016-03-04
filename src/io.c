#include <sys/endian.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#include "m_bit_set.h"

int
m_bit_set_read(m_bit_set* bs, int fd)
{
	uint32_t size;
	uint32_t max;

	if (bs == NULL)
		return M_BIT_SET_E_NULL;

	errno = 0;
	if (read(fd, &size, sizeof(uint32_t)) != 4)
		return M_BIT_SET_E_IO;

	if (read(fd, &max, sizeof(uint32_t)) != 4)
		return M_BIT_SET_E_IO;

	bs->size = be32toh(size);
	bs->max = be32toh(max);
	bs->data = malloc(bs->size);
	bs->own_memory = 1;


	if (read(fd, bs->data, bs->size) != (ssize_t)bs->size) {
		free(bs->data);
		return M_BIT_SET_E_IO;
	}

	return M_BIT_SET_OK;
}

int
m_bit_set_write(m_bit_set* bs, int fd)
{
	uint32_t max;
	uint32_t size;

	if (bs == NULL)
		return M_BIT_SET_E_NULL;

	max = htobe32(bs->max);
	size = htobe32(bs->size);

	errno = 0;
	if (write(fd, &size, sizeof(uint32_t)) != 4)
		return M_BIT_SET_E_IO;

	if (write(fd, &max, sizeof(uint32_t)) != 4)
		return M_BIT_SET_E_IO;

	if (write(fd, bs->data, (size_t)bs->size) != (ssize_t)bs->size)
		return M_BIT_SET_E_IO;

	return M_BIT_SET_OK;
}


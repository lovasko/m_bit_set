#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#include <m_bit_set.h>

int
main(void)
{
	m_bit_set primes;
	int fd;
	int ret;
	unsigned int query;

	fd = open("primes.mbs", O_RDONLY);
	if (fd < 0) {
		perror("open");
		return EXIT_FAILURE;
	}

	m_bit_set_read(&primes, fd, NULL);

	while (1) {
		printf("> ");
		fflush(stdout);
		scanf("%u", &query);

		ret = m_bit_set_test(&primes, (uint32_t)query);

		if (ret == M_BIT_SET_TRUE)
			printf("%u is a prime!\n", query);

		if (ret == M_BIT_SET_FALSE)
			printf("%u is not a prime.\n", query);

		if (ret == M_BIT_SET_E_RANGE)
			printf("ERROR: input number too large for the database.\n");
	}

	return EXIT_SUCCESS;
}


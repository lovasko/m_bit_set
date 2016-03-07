#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <math.h>

#include <m_bit_set.h>

int
main(int argc, char* argv[])
{
	m_bit_set bs;
	uint32_t i;
	uint32_t k;
	uint32_t n;
	int fd;

	if (argc < 2) {
		fprintf(stderr, "Expected one argument.\n");
		return EXIT_FAILURE;
	}

	n = (uint32_t)atol(argv[1]);
	m_bit_set_init(&bs, n, M_BIT_SET_TRUE, NULL);
	m_bit_set_remove(&bs, 0);
	m_bit_set_remove(&bs, 1);

	for (i = 2; i < sqrt(n); i++) {
		if (m_bit_set_test(&bs, i) == M_BIT_SET_FALSE)
			continue;

		for (k = i+1; k < n; k++)
			if (k % i == 0)
				m_bit_set_remove(&bs, k);
	}

	printf("Prime numbers up to %d are:\n", n);	
	for (i = 2; i < n; i++)
		if (m_bit_set_test(&bs, i) == M_BIT_SET_TRUE)
			printf("%d\n", i);

	fd = open("primes.mbs", O_WRONLY | O_CREAT);
	if (fd < 0) {
		perror("open");
		return EXIT_FAILURE;
	}

	m_bit_set_write(&bs, fd);
	close(fd);

	return EXIT_SUCCESS;
}


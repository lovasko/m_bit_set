#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include <m_bit_set.h>

int
main(void)
{
	m_bit_set fizz;
	m_bit_set buzz;
	m_bit_set fizz_buzz;
	uint32_t i;

	m_bit_set_init(&fizz, 0xff, M_BIT_SET_FALSE, NULL);
	m_bit_set_init(&buzz, 0xff, M_BIT_SET_FALSE, NULL);

	for (i = 0; i < 0xff; i++)
		if (i % 3 == 0)
			m_bit_set_add(&fizz, i);

	for (i = 0; i < 0xff; i++)
		if (i % 5 == 0)
			m_bit_set_add(&buzz, i);

	m_bit_set_dup(&fizz_buzz, &fizz, NULL);
	m_bit_set_intersect(&fizz_buzz, &buzz);

	for (i = 0; i < 0xff; i++) {
		if (m_bit_set_test(&fizz_buzz, i) == M_BIT_SET_TRUE)
			printf("Fizz buzz!");
		else if (m_bit_set_test(&fizz, i) == M_BIT_SET_TRUE)
			printf("Fizz!");
		else if (m_bit_set_test(&buzz, i) == M_BIT_SET_TRUE)
			printf("Buzz!");
		else
			printf("%d", i);

		printf("\n");
	}

	m_bit_set_free(&fizz);
	m_bit_set_free(&buzz);
	m_bit_set_free(&fizz_buzz);

	return EXIT_SUCCESS;
}


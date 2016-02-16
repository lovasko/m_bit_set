#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include "../src/m_smallintset.h"

int
main(void)
{
	struct m_smallintset fizz;
	struct m_smallintset buzz;
	struct m_smallintset fizz_buzz;
	uint16_t i;

	m_smallintset_init(&fizz, 65536, NULL);
	m_smallintset_init(&buzz, 65536, NULL);
	m_smallintset_init(&fizz_buzz, 65536, NULL);

	for (i = 0; i < 0xffff; i++)
		if (i % 3 == 0)
			m_smallintset_add(&fizz, i);

	for (i = 0; i < 0xffff; i++)
		if (i % 5 == 0)
			m_smallintset_add(&buzz, i);

	m_smallintset_copy(&fizz, &fizz_buzz);
	m_smallintset_intersect(&fizz_buzz, &buzz);

	for (i = 0; i < 0xffff; i++)
		if (m_smallintset_contains(&fizz_buzz, i) == M_SMALLINTSET_TRUE)
			printf("Fizz buzz! %d\n", i);

	m_smallintset_free(&fizz);
	m_smallintset_free(&buzz);
	m_smallintset_free(&fizz_buzz);

	return EXIT_SUCCESS;
}


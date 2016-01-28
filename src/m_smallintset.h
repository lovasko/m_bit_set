#ifndef M_SMALLINTSET_H
#define M_SMALLINTSET_H

#include <stdint.h>

#define M_SMALLINTSET_FALSE  0
#define M_SMALLINTSET_TRUE   1
#define M_SMALLINTSET_OK     2
#define M_SMALLINTSET_E_NULL 3
#define M_SMALLINTSET_E_SIZE 4
#define M_SMALLINTSET_E_MAX  4

struct m_smallintset {
	uint8_t* data;
	size_t size;
	int own_memory;
};

int m_smallintset_init(struct m_smallintset* sis, uint64_t max, uint8_t* data);
int m_smallintset_free(struct m_smallintset* sis);
int m_smallintset_copy(struct m_smallintset* sis_src, struct m_smallintset* sis_dst);
int m_smallintset_read(struct m_smallintset* sis, int fd);
int m_smallintset_write(struct m_smallintset* sis, int fd);
int m_smallintset_add(struct m_smallintset* sis, uint64_t value);
int m_smallintset_add_all(struct m_smallintset* sis);
int m_smallintset_remove(struct m_smallintset* sis, uint64_t value);
int m_smallintset_remove_all(struct m_smallintset* sis);
int m_smallintset_contains(struct m_smallintset* sis, uint64_t value);
int m_smallintset_union(struct m_smallintset* sis_a, struct m_smallintset* sis_b);
int m_smallintset_intersect(struct m_smallintset* sis_a, struct m_smallintset* sis_b);
int m_smallintset_complement(struct m_smallintset* sis);

#endif


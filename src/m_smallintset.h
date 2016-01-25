#ifndef M_SMALLINTSET_H
#define M_SMALLINTSET_H

#include <stdint.h>

#define M_SMALLINTSET_OK     0
#define M_SMALLINTSET_FALSE  0
#define M_SMALLINTSET_TRUE   1
#define M_SMALLINTSET_E_NULL 2

struct m_smallintset {
	uint8_t* data;
};

int m_smallintset_init(struct m_smallintset* sis);
int m_smallintset_copy(struct m_smallintset* sis_src, struct m_smallintset* sis_dst);
int m_smallintset_read(struct m_smallintset* sis, int fd);
int m_smallintset_write(struct m_smallintset* sis, int fd);
int m_smallintset_add(struct m_smallintset* sis, uint16_t value);
int m_smallintset_add_all(struct m_smallintset* sis);
int m_smallintset_remove(struct m_smallintset* sis, uint16_t value);
int m_smallintset_remove_all(struct m_smallintset* sis);
int m_smallintset_contains(struct m_smallintset* sis, uint16_t value);
int m_smallintset_union(struct m_smallintset* sis_a, struct m_smallintset* sis_b);
int m_smallintset_intersect(struct m_smallintset* sis_a, struct m_smallintset* sis_b);
int m_smallintset_complement(struct m_smallintset* sis);

#endif


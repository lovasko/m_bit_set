#ifndef M_BIT_SET_H
#define M_BIT_SET_H

#include <stdint.h>

#define M_BIT_SET_FALSE          0
#define M_BIT_SET_TRUE           1
#define M_BIT_SET_OK             2
#define M_BIT_SET_E_NULL         3
#define M_BIT_SET_E_SIZE         4
#define M_BIT_SET_E_RANGE        5
#define M_BIT_SET_E_COUNT        6
#define M_BIT_SET_E_VALUE        7
#define M_BIT_SET_E_IO           8
#define M_BIT_SET_E_UNKNOWN_CODE 9
#define M_BIT_SET_E_MAX          9

typedef struct m_bit_set {
	uint8_t* data;
	uint32_t size;
	uint32_t max;
	int own_memory;
} m_bit_set;

int m_bit_set_init(m_bit_set* bs, uint32_t max, uint8_t* data);
int m_bit_set_free(m_bit_set* bs);
int m_bit_set_copy(m_bit_set* bs_dst, m_bit_set* bs_src);
int m_bit_set_dup(m_bit_set* bs_dup, m_bit_set* bs_orig, uint8_t* data);
int m_bit_set_resize(m_bit_set* bs, uint32_t new_max, uint8_t fill);
int m_bit_set_read(m_bit_set* bs, int fd);
int m_bit_set_write(m_bit_set* bs, int fd);
int m_bit_set_add(m_bit_set* bs, uint32_t value);
int m_bit_set_add_all(m_bit_set* bs);
int m_bit_set_remove(m_bit_set* bs, uint32_t value);
int m_bit_set_remove_all(m_bit_set* bs);
int m_bit_set_test(m_bit_set* bs, uint32_t value);
int m_bit_set_union(m_bit_set* bs_a, m_bit_set* bs_b);
int m_bit_set_intersect(m_bit_set* bs_a, m_bit_set* bs_b);
int m_bit_set_complement(m_bit_set* bs);
int m_bit_set_error_string(int code, char** out_error_string);

#endif


#ifndef M_BIT_SET_H
#define M_BIT_SET_H

#include <stdint.h>

#define M_BIT_SET_FALSE          0
#define M_BIT_SET_TRUE           1
#define M_BIT_SET_OK             2
#define M_BIT_SET_E_NULL         3
#define M_BIT_SET_E_SIZE         4
#define M_BIT_SET_E_RANGE        5
#define M_BIT_SET_E_IO           6
#define M_BIT_SET_E_UNKNOWN_CODE 7
#define M_BIT_SET_E_MAX          7

struct m_bit_set {
	uint8_t* data;
	uint32_t size;
	uint32_t max;
	int own_memory;
};

int m_bit_set_init(struct m_bit_set* bs, uint32_t max, uint8_t* data);
int m_bit_set_free(struct m_bit_set* bs);
int m_bit_set_copy(struct m_bit_set* bs_src, struct m_bit_set* bs_dst);
int m_bit_set_read(struct m_bit_set* bs, int fd);
int m_bit_set_write(struct m_bit_set* bs, int fd);
int m_bit_set_add(struct m_bit_set* bs, uint32_t value);
int m_bit_set_add_all(struct m_bit_set* bs);
int m_bit_set_remove(struct m_bit_set* bs, uint32_t value);
int m_bit_set_remove_all(struct m_bit_set* bs);
int m_bit_set_test(struct m_bit_set* bs, uint32_t value);
int m_bit_set_union(struct m_bit_set* bs_a, struct m_bit_set* bs_b);
int m_bit_set_intersect(struct m_bit_set* bs_a, struct m_bit_set* bs_b);
int m_bit_set_complement(struct m_bit_set* bs);
int m_bit_set_error_string(int code, char** out_error_string);

#endif


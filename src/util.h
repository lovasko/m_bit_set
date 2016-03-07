#ifndef M_BIT_SET_UTIL_H
#define M_BIT_SET_UTIL_H

#include <stdlib.h>
#include <stdint.h>

#include "m_bit_set.h"

size_t size_t_min(size_t a, size_t b);
size_t compute_size(uint32_t max);
void cut_off(m_bit_set* bs);

#endif


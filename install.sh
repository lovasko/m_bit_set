#!/bin/sh

INC_DIR=/usr/include
LIB_DIR=/usr/lib

cp -v bin/libmbitset.so "${LIB_DIR}"
cp -v src/m_bit_set.h "${INC_DIR}"


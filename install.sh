#!/bin/sh

INC_DIR=/usr/include
LIB_DIR=/usr/lib

cp -v bin/libm_smallintset.so "${LIB_DIR}"
cp -v src/m_smallintset.h "${INC_DIR}"


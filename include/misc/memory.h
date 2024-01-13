#pragma once

#include <types.h>

void * memcpy(void * restrict dest, const void * restrict src, size_t count);
int memcmp(const void * s1, const void * s2, size_t n);
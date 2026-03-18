#pragma once
#include <stdlib.h>

#define xnew(type, count) (malloc(sizeof(type) * count))
#define zero(n) (memset(&n, 0, sizeof(n)))

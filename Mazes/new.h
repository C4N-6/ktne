#pragma once
#include <stdlib.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

#define MOD(a, n) ((((a) % (n)) + (n)) % (n))

#define xnew(type, count) (malloc(sizeof(type) * count))
#define zero(n) (memset(&n, 0, sizeof(n)))

#include <stdio.h>
#define LIFE_DBG(str, args...) printf("[LIFE][%s][line: %d] "str"\n", __func__, __LINE__, ##args)

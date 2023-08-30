#ifndef MEMORY_H_INCLUDED
#define MEMORY_H_INCLUDED
#include <stdlib.h>

unsigned long get_available_memory(void);

size_t get_fillable(size_t available);

void fill_memory(size_t fillable);
#endif /* MEMORY_H_INCLUDED */

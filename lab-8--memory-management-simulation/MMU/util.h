#ifndef MMU_H
#define MMU_H

#include <stdbool.h>
#include "list.h"

extern node_t *free_list;
extern node_t *allocated_list;

void allocate_memory(int pid, int block_size, char *policy);
void deallocate_memory(int pid, char *policy);
void list_coalese_nodes(node_t **list);

#endif

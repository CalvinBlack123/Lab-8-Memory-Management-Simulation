#ifndef LIST_H
#define LIST_H

#include <stdbool.h>

// Structures
typedef struct block {
    int pid;        // Process ID
    int start;      // Start address
    int end;        // End address
} block_t;

typedef struct node {
    block_t *blk;       // Pointer to the block
    struct node *next;  // Pointer to the next node
} node_t;

// Function prototypes
void list_add_ascending_by_blocksize(node_t **list, node_t *new_node);
void list_add_ascending_by_address(node_t **list, node_t *new_node);
void list_add_descending_by_blocksize(node_t **list, node_t *new_node);

#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mmu.h"
#include "list.h"

void allocate_memory(int pid, int block_size, char *policy) {
    node_t *current = free_list;
    node_t *previous = NULL;

    while (current) {
        int block_size_available = current->blk->end - current->blk->start + 1;

        if (block_size_available >= block_size) {
            // Remove from Free List
            if (previous) {
                previous->next = current->next;
            } else {
                free_list = current->next;
            }

            // Allocate the block
            int start = current->blk->start;
            int end = start + block_size - 1;

            node_t *allocated_block = malloc(sizeof(node_t));
            allocated_block->blk = malloc(sizeof(block_t));
            allocated_block->blk->pid = pid;
            allocated_block->blk->start = start;
            allocated_block->blk->end = end;
            list_add_ascending_by_address(&allocated_list, allocated_block);

            // Handle Fragmentation
            if (block_size_available > block_size) {
                int fragment_start = end + 1;
                int fragment_end = current->blk->end;

                node_t *fragment = malloc(sizeof(node_t));
                fragment->blk = malloc(sizeof(block_t));
                fragment->blk->pid = 0;
                fragment->blk->start = fragment_start;
                fragment->blk->end = fragment_end;

                if (strcmp(policy, "FIRST_FIT") == 0) {
                    list_add_to_back(&free_list, fragment);
                } else if (strcmp(policy, "BEST_FIT") == 0) {
                    list_add_ascending_by_blocksize(&free_list, fragment);
                } else if (strcmp(policy, "WORST_FIT") == 0) {
                    list_add_descending_by_blocksize(&free_list, fragment);
                }
            }

            free(current->blk);
            free(current);
            return;
        }

        previous = current;
        current = current->next;
    }

    printf("Error: Not Enough Memory\n");
}

void deallocate_memory(int pid, char *policy) {
    node_t *current = allocated_list;
    node_t *previous = NULL;

    while (current) {
        if (current->blk->pid == pid) {
            // Remove from Allocated List
            if (previous) {
                previous->next = current->next;
            } else {
                allocated_list = current->next;
            }

            // Add to Free List
            if (strcmp(policy, "FIRST_FIT") == 0) {
                list_add_to_back(&free_list, current);
            } else if (strcmp(policy, "BEST_FIT") == 0) {
                list_add_ascending_by_blocksize(&free_list, current);
            } else if (strcmp(policy, "WORST_FIT") == 0) {
                list_add_descending_by_blocksize(&free_list, current);
            }

            return;
        }

        previous = current;
        current = current->next;
    }

    printf("Error: PID %d not found in Allocated List\n", pid);
}

void list_coalese_nodes(node_t **list) {
    if (*list == NULL || (*list)->next == NULL) return;

    node_t *current = *list;

    while (current && current->next) {
        if (current->blk->end + 1 == current->next->blk->start) {
            // Merge the two nodes
            current->blk->end = current->next->blk->end;

            node_t *temp = current->next;
            current->next = current->next->next;

            free(temp->blk);
            free(temp);
        } else {
            current = current->next;
        }
    }
}
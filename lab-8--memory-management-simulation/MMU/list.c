#include "list.h"
#include <stdlib.h>

void list_add_ascending_by_blocksize(node_t **list, node_t *new_node) {
    if (*list == NULL || new_node->blk->end - new_node->blk->start + 1 < (*list)->blk->end - (*list)->blk->start + 1) {
        new_node->next = *list;
        *list = new_node;
        return;
    }

    node_t *current = *list;
    while (current->next && (current->next->blk->end - current->next->blk->start + 1) < (new_node->blk->end - new_node->blk->start + 1)) {
        current = current->next;
    }

    new_node->next = current->next;
    current->next = new_node;
}

void list_add_ascending_by_address(node_t **list, node_t *new_node) {
    if (*list == NULL || new_node->blk->start < (*list)->blk->start) {
        new_node->next = *list;
        *list = new_node;
        return;
    }

    node_t *current = *list;
    while (current->next && current->next->blk->start < new_node->blk->start) {
        current = current->next;
    }

    new_node->next = current->next;
    current->next = new_node;
}

void list_add_descending_by_blocksize(node_t **list, node_t *new_node) {
    if (*list == NULL || new_node->blk->end - new_node->blk->start + 1 > (*list)->blk->end - (*list)->blk->start + 1) {
        new_node->next = *list;
        *list = new_node;
        return;
    }

    node_t *current = *list;
    while (current->next && (current->next->blk->end - current->next->blk->start + 1) > (new_node->blk->end - new_node->blk->start + 1)) {
        current = current->next;
    }

    new_node->next = current->next;
    current->next = new_node;
}

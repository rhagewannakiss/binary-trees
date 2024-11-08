#include "trees.h"

#include <stdio.h>

int main() {
    elem_t root_val = 56;
    elem_t arr[] = {13, 94, 34, 63, 25, 74, 8};

    node_t* root = Ctor(&root_val);
    if (root == nullptr) {
        fprintf(stderr, "Failed to create root node\n");
        return 1;
    }

    for (size_t i = 0; i < sizeof(arr) / sizeof(elem_t); i++) {
        fprintf(stderr, "Inserting %d\n", arr[i]);

        if (InsertNode(root, arr[i]) == FAILURE) {
            fprintf(stderr, "Failed to merge at index %zu, value %d\n", i, arr[i]);
        }
    }

    Print(root);
    printf("\n");

    Dtor(root);
    return 0;
}

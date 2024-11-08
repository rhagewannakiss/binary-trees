#include "trees.h"
#include "tree_dump.h"

#include <stdio.h>

int main() {
    elem_t root_val = 56;
    elem_t arr[] = {13, 94, 34, 63, 25, 74, 8, 674, 34, 56, 3425, 245, 23, 45, 23, 357, 34, 234, 346, 4};

    node_t* root = Ctor(&root_val);
    if (root == nullptr) {
        fprintf(stderr, "Error: failed to create root node.\n");
        return 1;
    }

    for (size_t i = 0; i < sizeof(arr) / sizeof(elem_t); i++) {
        fprintf(stderr, "Inserting: %d", arr[i]);

        if (InsertNode(root, arr[i]) == FAILURE) {
            fprintf(stderr, "\nError: failed to insert at index %zu, value %d\n", i, arr[i]);
        }
        else fprintf(stderr, " --> SUCCESS\n");
    }

    Print(root);
    printf("\n\n");

    TreeDump(root);

    Dtor(root);
    return 0;
}

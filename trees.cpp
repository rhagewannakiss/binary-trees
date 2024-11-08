#include "trees.h"

#include <stdio.h>
#include <assert.h>

#include <cstdint>
#include <cstdlib>

static node_t* FindFreeNode(node_t* node);

//-------------------------- NODE CTOR --------------------------
node_t* Ctor(elem_t* val) {
    assert(val != nullptr);

    node_t* new_node = (node_t*)calloc(1, sizeof(node_t));
    if (!new_node) {
        fprintf(stderr, "Memory allocation failed in Ctor.\n");
        return nullptr;
    }

    new_node->value = *val;
    new_node->right = nullptr;
    new_node->left = nullptr;

    return new_node;
}

//------------------- DTOR (OF THE WHOLE TREE) --------------------
Status Dtor(node_t* root) {
    if (root == nullptr) {
        return SUCCESS;
    }

    Dtor(root->left);
    Dtor(root->right);

    free(root);
    return SUCCESS;
}
//-------------------------- INSERT NODE ---------------------------
Status InsertNode(node_t* root, elem_t val) {
    assert(root != nullptr);

    node_t* val_node = Ctor(&val);
    if (!val_node) {
        return FAILURE;
    }

    if (val < root->value) {
        if (root->left == nullptr) {root->left = val_node;}
        else {
            return InsertNode(root->left, val);
        }
    }
    else {
        if (root->right == nullptr) {root->right = val_node;}
        else {
            return InsertNode(root->right, val);
        }
    }

    return SUCCESS;
}

//---------------------------  PRINT  -----------------------------
void_sex Print(node_t* node) {
    if (node == nullptr) {
        return;
    }

    printf("( ");
    printf(" %d ", node->value);
    if (node->left) { Print(node->left); }
    if (node->right) { Print(node->right); }
    printf(" )");
}


//============================ STATIC =============================
//------------------------ FIND FREE NODE -------------------------
static node_t* FindFreeNode(node_t* node) {
    assert(node != nullptr);

    if (node->left == nullptr) {
        return node;
    }
    if (node->right == nullptr) {
        return node;
    }

    node_t* left_free = FindFreeNode(node->left);
    if (left_free != nullptr) {
        return left_free;
    }

    return FindFreeNode(node->right);
}

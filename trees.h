#ifndef TREES_H_
#define TREES_H_

#include <stdio.h>
#include <assert.h>
#include <cstdint>

static const uint32_t kMinCapacity = 8;

typedef int elem_t;
typedef void void_sex;

typedef enum TreeError {
	TreeError_kOk =                    0x00,
	TreeError_kMemoryAllocationError = 0x01,
	TreeError_kMergeError =            0x02
} TreeError;

typedef struct node_t {
	elem_t  value;

	node_t* right;
	node_t* left;
} node_t;

typedef enum Status {
    SUCCESS = 0x00,
    FAILURE = 0x01
} Status;

//---------------------------- PUBLIC ----------------------------
node_t*  Ctor(elem_t* val);
Status   Dtor(node_t* root);

Status   InsertNode(node_t* root, elem_t val);

void_sex Print(node_t* node);

#endif //TREES_H_
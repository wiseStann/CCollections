/* Insides of Binary Search Tree data structure */

#include "basic.h"

#ifndef BIN_SEARCH_TREE_H_
#define BIN_SEARCH_TREE_H_

#define MAXSIZE 256
#define bstreeSize(x) (x->size)

typedef struct Node_type {
    void* data;
    struct Node_type* left;
    struct Node_type* right;
} Node_t;

typedef struct Tree_type {
    size_t size;
    Node_t* root;
} BSTree;

// New BST creation
BSTree* bstreeNew();

// New node creation
Node_t* treeNodeNew(void* value);

// Append an element to the tree
void bstreeAppend(BSTree* tree, void* value);

// Helper insert function
extern void _bstreeAppendNewNode__(Node_t* root, void* value);

// Deleting an element from a tree
void bstreeDelete(Node_t* root, void* value);

// Checking if a given tree contains a value or not
bool bstreeSearch(BSTree* tree, void* value);

// Helped search function
extern bool _bstreeSearch__(Node_t* root, void* value);

// Traverse a given tree in preorder
int* bstreePreorderTraversal(Node_t* root);

// Traverse a given tree in postorder
int* bstreePostorderTraversal(Node_t* root);

// Traverse a given tree in inorder
int* bstreeInorderTraversal(Node_t* root);

// Traverse a given tree in levelorder
int* bstreeLevelorderTraversal(Node_t* root);

// Finding a minimum depth of a given tree
int bstreeMinDepth(Node_t* root);

// Finding a maximum depth of a given tree
int bstreeMaxDepth(Node_t* root);

// Checking if a given tree is empty or not
bool bstreeIsEmpty(BSTree* tree);

// Checking if a given tree is full or not
bool bstreeIsFull(BSTree* tree);


#endif // BIN_SEARCH_TREE_H_
/*

-> Binary Search Tree collection <-

This software is free and can be used and modifyied by anyone
under the terms of the GNU Lesser General Public License as
published by the Free Software Foundation, either version 3
of the License, or any later version.

[Development period] -> 25/12/19 - 27/12/19
[Author] -> Stacey Kerr
[Github] -> https://github.com/wiseStann


-> Structure <-

typedef struct Node_type {
    void* data;
    struct Node_type* left;
    struct Node_type* right;
} Node;

typedef struct Tree_type {
    size_t size;
    Node* root;
} BSTree;


-> Macroses <-

Check Error macroses in "include/basic.h" header file.

A short description of all:
 -> [_EMPTY_TREE_ERROR], a macros for notification about empty given list
 -> [_MEMORY_ALLOCATION_ERROR], a macros for notification about memory allocation error
 -> [_INDEX_ERROR], a macros for notification about wrong given index
 -> [_VALUE_ERROR], a macros for notification about value, which is not in list

*/

#include "../include/binsearchtree.h"

/*
    Features which will be appended soon:
   - int* bstreeLevelorderTraversal(Node_t* root); 
*/


/*

A new binary search tree creating.
> Complex time - const.

 Parameters [in]:
    -> NULL

 Parameters [out]:
    -> [new_tree], a new created binary search tree

*/
BSTree* bstreeNew()
{
    BSTree* new_tree = (BSTree*)malloc(sizeof(BSTree));
    if (!new_tree) {
        _MEMORY_ALLOCATION_ERROR;
        free(new_tree);
        exit(1);
    }

    new_tree->size = 0;
    new_tree->root = NULL;
    return new_tree;
}

/*

A new node creating.
> Complex time - const.

 Parameters [in]:
    -> [value], a value which this node should keep

 Parameters [out]:
    -> [new_node], a new created node

*/
Node_t* treeNodeNew(void* value)
{
    Node_t* new_node = (Node_t*)malloc(sizeof(Node_t));
    if (!new_node) {
        _MEMORY_ALLOCATION_ERROR;
        free(new_node);
        exit(1);
    }

    new_node->data = value;
    new_node->left = NULL;
    new_node->right = NULL;

    return new_node;
}

/*

Insertion a new value in the tree.

 Parameters [in]:
    -> [tree], a tree, which should be appended
    -> [value], a value, which should be inserted in the tree

 Parameters [out]:
    -> NULL
*/
void bstreeAppend(BSTree* tree, void* value)
{
    if (tree->size >= MAXSIZE) {
        panic("in '%s': max size of nodes exceeded");
        exit(1);
    } if (!tree->root) {
        tree->root = treeNodeNew(value);
    } else {
        _bstreeAppendNewNode__(tree->root, value);
    }
    tree->size++;
}

/*

Main function of insertion the node in the binary tree.

 Parameters [in]:
    -> [rott], root of the tree, which should be appended
    -> [value], a value, which should be appended in the tree

 Parameters [out]:
    -> NULL
*/
extern void _bstreeAppendNewNode__(Node_t* root, void* value)
{
    if (value < root->data) {
        if (!root->left) {
            root->left = treeNodeNew(value);
        } else {
            _bstreeAppendNewNode__(root->left, value);
        }
    } else if (value > root->data) {
        if (!root->right) {
            root->right = treeNodeNew(value);
        } else {
            _bstreeAppendNewNode__(root->right, value);
        }
    } else {
        panic("in 'bstreeAppend': the value is already in the tree");
    }
}

/*

Deleting of a given value from the tree.

 Parameters [in]:
    -> [tree], a tree the value of which should be deleted
    -> [value], a value which should be deleted from the tree

 Parameters [out]:
    -> NULL
*/
void bstreeDelete(Node_t* root, void* value)
{
    if (!root) {
        _EMPTY_TREE_ERROR;
    } else {

    }
}

/*

Checking if a given tree contains a given value.

 Parameters [in]:
    -> [tree], a tree the node of which should be seached
    -> [value], a value which should be searched

 Parameters [out]:
    -> [bool], the result of searching a given value
*/
bool bstreeSearch(BSTree* tree, void* value)
{
    if (!tree->root) {
        _EMPTY_TREE_ERROR;
        return false;
    }
    
    return _bstreeSearch__(tree->root, value);
}

/*

Main function of searching a node with a given value.

 Parameters [in]:
    -> [root], a root of tree which should be searched
    -> [value], a value, which should be searched in tree

 Parameters [out]:
    -> [bool], the result of searching a node

*/
extern bool _bstreeSearch__(Node_t* root, void* value)
{
    if (root->data == value) {
        return true;
    } else if (value < root->data && root->left) {
        return _bstreeSearch__(root->left, value);
    } else if (value > root->data && root->right) {
        return _bstreeSearch__(root->right, value);
    }
    return false;
}

/*

Preorder tree traverse.
* I.e. firstly we check the root then left child and
 then right child of the tree *

 Parameters [in]:
    -> [root], root of the tree that should be traversed

 Parameters [out]:
    -> [traversal], an array of nodes
    
*/
int* bstreePreorderTraversal(Node_t* root)
{
    static int index = 0;
    static int traversal[MAXSIZE];
    if (root) {
        traversal[index] = toInteger(root->data);
        index++;
        bstreePreorderTraversal(root->left);
        bstreePreorderTraversal(root->right);
    }

    return traversal;
}

/*

Postorder tree traverse.
* I.e. firstly we check left child then the root and
 then right child of the tree *

 Parameters [in]:
    -> [root], root of the tree that should be traversed

 Parameters [out]:
    -> [traversal], an array of nodes
    
*/
int* bstreePostorderTraversal(Node_t* root)
{
    static int index = 0;
    static int traversal[MAXSIZE];
    if (root) {
        bstreePostorderTraversal(root->left);
        bstreePostorderTraversal(root->right);
        traversal[index] = toInteger(root->data);
        index++;
    }
    
    return traversal;
}

/*

Inorder tree traverse.
* I.e. firstly we check left child then the root and
 then right child of the tree *

 Parameters [in]:
    -> [root], root of the tree that should be traversed

 Parameters [out]:
    -> [traversal], an array of nodes

*/
int* bstreeInorderTraversal(Node_t* root)
{
    static int index = 0;
    static int traversal[MAXSIZE];
    if (root) {
        bstreeInorderTraversal(root->left);
        traversal[index] = toInteger(root->data);
        index++;
        bstreeInorderTraversal(root->right);
    }

    return traversal;
}

/*

Finding the minimum depth of a given tree.
* For example if the tree looks like
*                10
*               / \
*              5   11
*             / \
*            3   7
* The minimum depth would be 2 and the node would be 11

 Parameters [in]:
    -> [root], the root of the tree the min depth of which should be found

 Parameters [out]:
    -> [min_height], the minimum height of the tree

*/
int bstreeMinDepth(Node_t* root)
{
    if (!root) {
        return 1;
    }
    if (!root->right && !root->left) {
        return 2;
    }
    int left_height = bstreeMinDepth(root->left);
    int right_height = bstreeMinDepth(root->right);

    int min_height = left_height ? (left_height < right_height) : right_height;
    return 1 + min_height;
}

/*

Finding the maximum depth of a given tree.
* For example if the tree looks like
*                9
*               / \
*              4   13
*                 /  \
*                12   19
*                    /
*                   16  
* The maximum depth would be 4 and the node would be 16

 Parameters [in]:
    -> [root], the root of the tree the max depth of which should be found

 Parameters [out]:
    -> [max_height], the maximum height of the tree
    
*/
int bstreeMaxDepth(Node_t* root)
{
    if (!root) {
        return 0;
    }

    int left_height = bstreeMaxDepth(root->left);
    int right_height = bstreeMaxDepth(root->right);

    int max_height = left_height ? (left_height > right_height) : right_height;
    return 1 + max_height;
}

/*

Checking if a given tree has the size 0 or not.
> Complex time - const.

 Parameters [in]:
    -> [tree], the tree the size of which should be checked

 Parameters [out]:
    -> [bool], the result of checking if the tree is empty

*/
bool bstreeIsEmpty(BSTree* tree)
{
    if (!tree->root)
        return true;
    return false;
}

/*

Checking if a given tree has the size is MAXSIZE or not.
> Complex time - const.

 Parameters [in]:
    -> [tree], the tree the size of which should be checked

 Parameters [out]:
    -> [bool], the result of checking if the tree is full
    
*/
bool bstreeIsFull(BSTree* tree)
{
    if (bstreeSize(tree) == MAXSIZE)
        return true;
    return false;
}

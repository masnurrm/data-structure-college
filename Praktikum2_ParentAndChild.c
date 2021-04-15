/**
 * Implementasi Binary Search Tree (ADT: BST)
 * yakni BST yang tidak menyimpan key duplikat (unique key)
 * 
 * Dibuat dan ditulis oleh Bayu Laksana
 * -- tanggal 29 Februrari 2019
 * Struktur Data 2020
 * 
 * Implementasi untuk Bahasa C
 */

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

/**
 * Node structure and
 * uniqueBST structure
 */

typedef struct bstnode_t {
    int key;
    char nama[11];
    struct bstnode_t \
        *left, *right, *parent;
} BSTNode;

typedef struct bst_t {
    BSTNode *_root;
    unsigned int _size;
} BST;

/**
 * !!! WARNING UTILITY FUNCTION !!!
 * Recognized by prefix "__bst__"
 * ---------------------------------------------
 * Note that you better never access these functions, 
 * unless you need to modify or you know how these functions work.
 */

BSTNode* __bst__createNode(BSTNode *parent, int value, char nama[]) {
    BSTNode *newNode = (BSTNode*) malloc(sizeof(BSTNode));
    newNode->key = value;
    strcpy(newNode->nama, nama);
    // newNode->nama = nama;
    newNode->left = newNode->right = NULL;
    newNode->parent = parent;
    return newNode;
}

BSTNode* __bst__insert(BSTNode *root, BSTNode *parent, int value, char nama[]) {
    if (root == NULL) 
        return __bst__createNode(parent, value, nama);

    if (value < root->key)
        root->left = __bst__insert(root->left, root, value, nama);
    else if (value > root->key)
        root->right = __bst__insert(root->right, root, value, nama);
    
    return root;
}


BSTNode* __bst__search(BSTNode *root, int value) {
    while (root != NULL) {
        if (value < root->key)
            root = root->left;
        else if (value > root->key)
            root = root->right;
        else
            return root;
    }
    return root;
}

BSTNode* __bst__findMinNode(BSTNode *node) {
    BSTNode *currNode = node;
    while (currNode && currNode->left != NULL)
        currNode = currNode->left;
    
    return currNode;
}

BSTNode* __bst__remove(BSTNode *root, int value) {
    if (root == NULL) return NULL;

    if (value > root->key) 
        root->right = __bst__remove(root->right, value);
    else if (value < root->key) 
        root->left = __bst__remove(root->left, value);
    else {
        
        if (root->left == NULL) {
            BSTNode *rightChild = root->right;
            free(root);
            return rightChild;
        }
        else if (root->right == NULL) {
            BSTNode *leftChild = root->left;
            free(root);
            return leftChild;
        }

        BSTNode *temp = __bst__findMinNode(root->right);
        root->key     = temp->key;
        root->right   = __bst__remove(root->right, temp->key);
    }
    return root;
}

void __bst__inorder(BSTNode *root) {
    if (root) {
        __bst__inorder(root->left);
        printf("%d ", root->key);
        __bst__inorder(root->right);
    }
}

void __bst__postorder(BSTNode *root) {
    if (root) {
        __bst__postorder(root->left);
        __bst__postorder(root->right);
        printf("%d ", root->key);
    }
}

void __bst__preorder(BSTNode *root) {
    if (root) {
        printf("%d ", root->key);
        __bst__preorder(root->left);
        __bst__preorder(root->right);
    }
}

/**
 * PRIMARY FUNCTION
 * ---------------------------
 * Accessible and safe to use.
 */

void bst_init(BST *bst) {
    bst->_root = NULL;
    bst->_size = 0u;
}

bool bst_isEmpty(BST *bst) {
    return bst->_root == NULL;
}

bool bst_find(BST *bst, int value) {
    BSTNode *temp = __bst__search(bst->_root, value);
    if (temp == NULL)
        return false;
    
    if (temp->key == value)
        return true;
    else
        return false;
}

void bst_insert(BST *bst, int value, char nama[]) {
    if (!bst_find(bst, value)) {
        bst->_root = __bst__insert(bst->_root, NULL, value, nama);
        bst->_size++;
    }
}

void bst_remove(BST *bst, int value) {
    if (bst_find(bst, value)) {
        bst->_root = __bst__remove(bst->_root, value);
        bst->_size--;
    }
}

/**
 * Binary search tree traversal
 * - Inorder
 * - Postorder
 * - Preorder
 */

void bst_inorder(BST *bst) {
    __bst__inorder(bst->_root);
}

void bst_postorder(BST *bst) {
    __bst__postorder(bst->_root);
}

void bst_preorder(BST *bst) {
    __bst__preorder(bst->_root);
}

void childFinder(BSTNode *x){
    if(x->left != NULL) {
        printf("%s ", x->left->nama);
    }
    else {
        printf("NULL ");
    }


    if(x->right != NULL) {
        printf("%s", x->right->nama);
        puts("");
    }
    else {
        printf("NULL");
        puts(""); 
    }
}

void parentFinder(BSTNode *x){
    if(x->parent != NULL) {
        printf("%s", x->parent->nama);
        puts("");
    }
    else {
        printf("NULL");
        puts("");
    }
}


void bst_findChild(BST *bst, int value) {
    BSTNode *temp = __bst__search(bst->_root, value);
    childFinder(temp);
}

void bst_findParent(BST *bst, int value) {
    BSTNode *temp = __bst__search(bst->_root, value);
    parentFinder(temp);
}


int main()
{
    BST set;
    bst_init(&set);

    int N, id;
    char cmd[10], member[10];
    scanf("%d", &N);
    for(int i = 0; i < N; i++) {
        scanf("%s", cmd);
        if(strcmp("add", cmd) == 0) {
            scanf("%d %s", &id, member);
            if(bst_find(&set, id)){
                printf("NomorID udah ada");
                puts("");
            }
            else{
                bst_insert(&set, id, member);
            }
        }
        if(strcmp("child", cmd) == 0){
            scanf("%d", &id);
            if(bst_find(&set, id)){
                bst_findChild(&set, id);
            }
            else{
                printf("hmmm");
                puts("");
            }
        }
        if(strcmp("parent", cmd) == 0){
            scanf("%d", &id);
            if(bst_find(&set, id)){
                bst_findParent(&set, id);
            }
            else{
                printf("hmmm");
                puts("");
            }
        }
    }

    return 0;
}
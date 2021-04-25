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

/**
 * Node structure and
 * uniqueBST structure
 */

typedef struct bstnode_t {
    long long key;
    struct bstnode_t \
        *left, *right;
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

BSTNode* __bst__createNode(long long  value) {
    BSTNode *newNode = (BSTNode*) malloc(sizeof(BSTNode));
    newNode->key = value;
    newNode->left = newNode->right = NULL;
    return newNode;
}

BSTNode* __bst__insertAscending(BSTNode *root, long long  value) {
    if (root == NULL) 
        return __bst__createNode(value);

    if (value < root->key)
        root->left = __bst__insertAscending(root->left, value);
    else if (value > root->key)
        root->right = __bst__insertAscending(root->right, value);
    
    return root;
}

BSTNode* __bst__insertDescending(BSTNode *root, long long  value) {
    if (root == NULL) 
        return __bst__createNode(value);

    if (value > root->key)
        root->left = __bst__insertDescending(root->left, value);
    else if (value > root->key)
        root->right = __bst__insertDescending(root->right, value);
    
    return root;
}

BSTNode* __bst__search(BSTNode *root, long long  value) {
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

BSTNode* __bst__remove(BSTNode *root, long long  value) {
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
        printf("%lld ", root->key);
        __bst__inorder(root->right);
    }
}

void __bst__postorder(BSTNode *root) {
    if (root) {
        __bst__postorder(root->left);
        __bst__postorder(root->right);
        printf("%lld ", root->key);
    }
}

void __bst__preorder(BSTNode *root) {
    if (root) {
        printf("%lld ", root->key);
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

bool bst_find(BST *bst, long long  value) {
    BSTNode *temp = __bst__search(bst->_root, value);
    if (temp == NULL)
        return false;
    
    if (temp->key == value)
        return true;
    else
        return false;
}

void bst_insertAscending(BST *bst, long long  value) {
    if (!bst_find(bst, value)) {
        bst->_root = __bst__insertAscending(bst->_root, value);
        bst->_size++;
    }
}

void bst_insertDescending(BST *bst, long long  value) {
    if (!bst_find(bst, value)) {
        bst->_root = __bst__insertDescending(bst->_root, value);
        bst->_size++;
    }
}

void bst_remove(BST *bst, long long  value) {
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
 
void midAscending(BST *bst, long long arr[], int start, int end){
    int mid;
    if(end<start){
        return;
    }

    if((start+end)%2==0) {
        mid = (start+end)/2;
    }
    else{
        mid = (start+end)/2;
    }
    bst_insertAscending(bst, arr[mid]);

    midAscending(bst, arr, start, mid-1);
    midAscending(bst, arr, mid+1, end);
}


void midDescending(BST *bst, long long arr[], int start, int end){
    int mid;
    if(end<start){
        return;
    }
        
    if((start+end)%2==0) {
        mid = (start+end)/2;
    }
    else{
        mid = (start+end)/2;
    }
    bst_insertDescending(bst, arr[mid]);

    midAscending(bst, arr, start, mid-1);
    midAscending(bst, arr, mid+1, end);
}

bool cek = false;
void cekJenis(long long arr[], int start, int end){
    for(int i = start; i<end; i++) {
        if(arr[i] < arr[i+1]){
            cek = true;
            break;
        }
        else if(arr[i] > arr[i+1]){
            cek = false;
            break;
        }
    }
}

int main()
{
    BST set;
    bst_init(&set);
    int N;
    scanf("%d", &N);
    long long arr[N];
    for(int i = 1; i <= N; i++) {
        scanf("%lld", &arr[i]);
    }
    cekJenis(arr, 0, N);
    if(cek){
        midAscending(&set, arr, 1, N);
    }
    else{
        midDescending(&set, arr, 1, N);
    }


    bst_preorder(&set);
    puts("");
    bst_postorder(&set);
    puts("");
    
    return 0;
}
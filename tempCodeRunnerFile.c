
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
    char nama[12];
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

BSTNode* __bst__createNode(BSTNode*parent, int value, char nama[]) {
    BSTNode *newNode = (BSTNode*) malloc(sizeof(BSTNode));
    newNode->key = value;
    strcpy(newNode->nama, nama);
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

BSTNode *bst_find2(BST *bst, int value) {
    BSTNode *temp = __bst__search(bst->_root, value);
    return temp;
}


int main()
{
    BST set;
    bst_init(&set);
    BSTNode *temp; // buat store node yang telah dicari
    int n, key;
    scanf("%d",&n);
    char command[10], nama[10];
    while(n--){
        scanf("%s", command);
        if(command[0] == 'a'){
            scanf("%d %s", &key, nama);
            if(bst_find(&set, key) == 1){
                printf("NomorID udah ada\n");
            }
            else bst_insert(&set, key, nama);
        }
        else if(command[0] == 'c'){
            scanf("%d",&key);
            temp = bst_find2(&set, key);
            if(temp == NULL){
                printf("hmmm\n");
                continue;
            }
            if(temp->left == NULL) {
                printf("NULL ");
            }
            else {
                printf("%s ", temp->left->nama);
            }
            if(temp->right == NULL){
                printf("NULL\n");
            }
            else {
                printf("%s\n",temp->right->nama);
            }
        }
        else{
            scanf("%d", &key);
            temp = bst_find2(&set, key);
            if(temp == NULL){
                printf("hmmm\n");
                continue;
            }
            if(temp->parent == NULL){
                printf("NULL\n");
            }
            else{
                printf("%s\n", temp->parent->nama);
            }
        }
    }
    return 0;
}


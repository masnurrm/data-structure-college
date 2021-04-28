// ========[AVL Tree]======== //
/*
    Dibuat dan ditulis oleh ABDUR ROCHMAN
    28-03-2020
    Struktur Data 2020
    For C
*/

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

typedef struct AVLNode_t {
    int data;
    struct AVLNode_t *left,*right;
    int height;
} AVLNode;

typedef struct AVL_t {
    AVLNode *_root;
    unsigned int _size;
} AVL;

AVLNode* _avl_createNode(int value) {
    AVLNode *newNode = (AVLNode*) malloc(sizeof(AVLNode));
    newNode -> data = value;
    newNode -> height = 1;
    newNode -> left = newNode -> right = NULL;
    return newNode;
}

AVLNode* _search(AVLNode *root, int value) {
    while (root != NULL) {
        if (value < root -> data) {
            root = root -> left;
        }
        else if (value > root -> data) {
            root = root -> right;
        }
        else {
            return root;
        }
    }
    return root;
}

int _getHeight(AVLNode* node) {
    if(node == NULL) {
        return 0;
    } 
    return node -> height;
}

int _max(int a, int b) {
    return (a > b) ? a : b;
}

AVLNode* _rightRotate(AVLNode* pivotNode) {

    AVLNode* newParrent = pivotNode -> left;
    pivotNode -> left = newParrent -> right;
    newParrent -> right = pivotNode;

    pivotNode -> height = _max(_getHeight(pivotNode -> left),
                      _getHeight(pivotNode -> right)) + 1;
    newParrent -> height=_max(_getHeight(newParrent -> left),
                       _getHeight(newParrent -> right)) + 1;
    
    return newParrent;
}

AVLNode* _leftRotate(AVLNode* pivotNode) {
    AVLNode* newParrent = pivotNode -> right;
    pivotNode -> right = newParrent -> left;
    newParrent -> left = pivotNode;

    pivotNode->height = _max(_getHeight(pivotNode -> left),
                      _getHeight(pivotNode -> right)) + 1;
    newParrent->height = _max(_getHeight(newParrent -> left),
                       _getHeight(newParrent -> right)) + 1;

    return newParrent;
}

AVLNode* _leftCaseRotate(AVLNode* node) {
    return _rightRotate(node);
}

AVLNode* _rightCaseRotate(AVLNode* node) {
    return _leftRotate(node);
}

AVLNode* _leftRightCaseRotate(AVLNode* node) {
    node -> left = _leftRotate(node -> left);
    return _rightRotate(node);
}

AVLNode* _rightLeftCaseRotate(AVLNode* node) {
    node -> right = _rightRotate(node -> right);
    return _leftRotate(node);
}

int _getBalanceFactor(AVLNode* node) {
    if(node == NULL) {
        return 0;
    }
    return _getHeight(node -> left)-_getHeight(node -> right);
}

AVLNode* _insert_AVL(AVL *avl, AVLNode* node, int value) {
    
    if(node == NULL) // udah mencapai leaf
        return _avl_createNode(value);
    if(value < node -> data) {
        node -> left = _insert_AVL(avl, node -> left, value);
    }
    else if(value > node -> data) {
        node -> right = _insert_AVL(avl, node -> right, value);
    }

    node->height= 1 + _max(_getHeight(node->left),_getHeight(node->right));

    int balanceFactor = _getBalanceFactor(node);
    
    if(balanceFactor > 1 && value < node -> left -> data) // skewed kiri (left-left case)
        return _leftCaseRotate(node);
    if(balanceFactor > 1 && value > node -> left -> data) // 
        return _leftRightCaseRotate(node);
    if(balanceFactor < -1 && value > node -> right -> data)
        return _rightCaseRotate(node);
    if(balanceFactor < -1 && value < node -> right -> data)
        return _rightLeftCaseRotate(node);
    
    return node;
}

AVLNode* _findMinNode(AVLNode *node) {
    AVLNode *currNode = node;
    while (currNode && currNode -> left != NULL)
        currNode = currNode -> left;
    return currNode;
}

void avl_init(AVL *avl) {
    avl -> _root = NULL;
    avl -> _size = 0u;
}

bool avl_isEmpty(AVL *avl) {
    return avl -> _root == NULL;
}

bool avl_find(AVL *avl, int value) {
    AVLNode *temp = _search(avl -> _root, value);
    if (temp == NULL)
        return false;
    
    if (temp -> data == value)
        return true;
    else
        return false;
}

void avl_insert(AVL *avl, int value) {
    if(!avl_find(avl, value)){
        avl -> _root = _insert_AVL(avl, avl -> _root, value);
        avl -> _size++;
    }

}

long long sum;
void helpMe(AVLNode *root, int value) {
    if(root == NULL) {
        return;
    }

    if(value == 0) {
        sum += root -> data;
        return;
    }
    
    else {
        value = value - 1;
        helpMe(root -> left, value);
        helpMe(root -> right, value);
    }
}

void bruh(AVLNode *root, int value) {
    if(root == NULL) {
        return;
    }

    if(value == 0) {
        printf("%d ", root -> data);
        return;
    }
    
    else {
        value = value - 1;
        bruh(root -> left, value);
        bruh(root -> right, value);
    }
}

int main() {
    AVL avlku;
    avl_init(&avlku);

    int Q, cmd;
    int x;
    
    scanf("%d", &Q);
    for(int i = 0; i < Q; i++) {
        scanf("%d", &cmd);
        if(cmd == 1) {
            scanf("%d", &x);
            avl_insert(&avlku, x);
        }
        else if(cmd == 2) {
            scanf("%d", &x);
            x = x - 1;
            bruh(avlku._root, x);
            puts("");
        }
        else if(cmd == 3) {
            scanf("%d", &x);
            x = x - 1;
            helpMe(avlku._root, x);
            printf("%lld", sum);
            puts("");
        }
        sum = 0;
    }
}
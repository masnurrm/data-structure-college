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
    long long data;
    struct AVLNode_t *left,*right;
    int height;
} AVLNode;

typedef struct AVL_t {
    AVLNode *_root;
    unsigned int _size;
} AVL;

AVLNode* _avl_createNode(long long value) {
    AVLNode *newNode = (AVLNode*) malloc(sizeof(AVLNode));
    newNode -> data = value;
    newNode -> height = 1;
    newNode -> left = newNode -> right = NULL;
    return newNode;
}

AVLNode* _search(AVLNode *root, long long value) {
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
    return _getHeight(node -> left) - _getHeight(node -> right);
}

AVLNode* _insert_AVL(AVL *avl, AVLNode* node, long long value) {
    
    if(node == NULL) // udah mencapai leaf
        return _avl_createNode(value);
    if(value < node -> data)
        node -> left = _insert_AVL(avl, node -> left, value);
    else if(value > node -> data)
    	node -> right = _insert_AVL(avl, node -> right, value);
    
    node->height= 1 + _max(_getHeight(node -> left), _getHeight(node -> right)); 

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

AVLNode* _remove_AVL(AVLNode* node, long long value) {
    if(node == NULL)
        return node;
    if(value > node->data)
    	node -> right = _remove_AVL(node -> right, value);
    else if(value < node -> data)
    	node -> left = _remove_AVL(node -> left, value);
    else{
        AVLNode *temp;
        if((node -> left == NULL) || (node -> right == NULL)) {
            temp = NULL;
            if(node -> left == NULL) temp = node -> right;  
            else if(node -> right == NULL) temp = node -> left;
            
            if(temp == NULL){
                temp = node;
                node = NULL;
            }
            else
                *node = *temp;   
            
            free(temp);
        }
        else{
            temp = _findMinNode(node -> right);
            node -> data = temp -> data;
            node -> right = _remove_AVL(node -> right, temp -> data);
        }    
    }

	if(node == NULL) return node;
    
    node -> height=_max(_getHeight(node->left), _getHeight(node->right)) + 1;

    int balanceFactor = _getBalanceFactor(node);
    
    if(balanceFactor > 1 && _getBalanceFactor(node -> left) >= 0) 
        return _leftCaseRotate(node);

    if(balanceFactor > 1 && _getBalanceFactor(node -> left) < 0) 
        return _leftRightCaseRotate(node);
  
    if(balanceFactor < -1 && _getBalanceFactor(node -> right) <= 0) 
        return _rightCaseRotate(node);

    if(balanceFactor < -1 && _getBalanceFactor(node -> right) > 0) 
        return _rightLeftCaseRotate(node);
    
    return node;
}

void avl_init(AVL *avl) {
    avl -> _root = NULL;
    avl -> _size = 0u;
}

bool avl_isEmpty(AVL *avl) {
    return avl -> _root == NULL;
}

bool avl_find(AVL *avl, long long value) {
    AVLNode *temp = _search(avl -> _root, value);
    if (temp == NULL)
        return false;
    
    if (temp -> data == value)
        return true;
    else
        return false;
}

void avl_insert(AVL *avl, long long value) {
    if(!avl_find(avl, value)){
        avl -> _root = _insert_AVL(avl, avl -> _root, value);
        avl -> _size++;
    }

}

void avl_remove(AVL *avl, long long value) {
    if(avl_find(avl, value)){
        avl -> _root = _remove_AVL(avl -> _root, value);
        avl -> _size--;
    }

}

void preorder(AVLNode *root) {
    if (root) {
        printf("%lld ", root -> data);
        preorder(root -> left);
        preorder(root -> right);
    }
}

void postorder(AVLNode *root) {
    if (root) {
        postorder(root -> left);
        postorder(root -> right);
        printf("%lld ", root -> data);
    }
}

void inorder(AVLNode *root) {
    if (root) {
        inorder(root -> left);
        if(root -> height == 1) {
             printf("%lld ", root -> data);
        }
        inorder(root -> right);
    }
}

int main() {
    AVL avlku;
    avl_init(&avlku);
    avl_insert(&avlku,1);
    avl_insert(&avlku,2);
    avl_insert(&avlku,3);
    avl_insert(&avlku,4);
	avl_insert(&avlku,5);
	avl_insert(&avlku,7);
	// avl_insert(&avlku,99);
	// avl_insert(&avlku,12);
	// avl_insert(&avlku,31);
    // preorder(avlku._root);
    // puts("");
    // postorder(avlku._root);
    // puts("");
    inorder(avlku._root);
	puts("");
    printf("%d", _getHeight(avlku._root));

    // avl_remove(&avlku,1);
	// avl_remove(&avlku,99);
	// avl_remove(&avlku,4);
	// avl_remove(&avlku,12);
	// avl_remove(&avlku,31);

}
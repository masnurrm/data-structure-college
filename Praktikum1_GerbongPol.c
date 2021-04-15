#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

typedef struct snode_t {
    int data;
    struct snode_t *next;
} SListNode;

typedef struct slist_t {
    unsigned _size;
    SListNode *_head;
} SinglyList;

int lighter = 0;

void slist_init(SinglyList *list) 
{
    list -> _head = NULL;
    list -> _size = 0;
}

bool slist_isEmpty(SinglyList *list) {
    return (list -> _head == NULL);
}

void slist_pushBack(SinglyList *list, int value)
{   
    SListNode *newNode = (SListNode*) malloc(sizeof(SListNode));
    if (newNode) {
        list -> _size++;
        newNode -> data = value;
        newNode -> next = NULL;
        
        if (slist_isEmpty(list)) {
            list -> _head = newNode;
        }
        else {
            SListNode *temp = list->_head;
            while (temp -> next != NULL) {
                temp = temp -> next;
            }
            temp -> next = newNode;
        }
    }
}

void slist_popFront(SinglyList *list)
{
    if (!slist_isEmpty(list)) {
        SListNode *temp = list -> _head;
        list -> _head = list -> _head -> next;
        free(temp);
        list -> _size--;
    }
}

int slist_front(SinglyList *list)
{
    if (!slist_isEmpty(list)) {
        return list->_head->data;
    }
    return 0;
}


int main() {
    SinglyList myList;
    slist_init(&myList);
    int n, k, gerbong, min = 0, total = 0;
    scanf("%d %d", &n, &k);
    for(int i = 1; i <= n; i++){
        scanf("%d", &gerbong);
        if (i <= k){
            slist_pushBack(&myList, gerbong);
            total = total + gerbong;
            min = total;
        }
        else if (i > k) {
            slist_pushBack(&myList, gerbong);
            total = total + gerbong;
            int popped = slist_front(&myList);
            slist_popFront(&myList);
            total = total - popped;
            if (total <= min) {
                min = total;
            }
        }      
    }

    // data masuk, cari gerbong
    // slist_gerbongPair(&myList, n, k);
    printf("%d\n", min);
    puts("");
    return 0;
}
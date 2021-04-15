#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

typedef struct stackNode_t {
    int data;
    int max;
    int min;
    struct stackNode_t *next;
} StackNode;

typedef struct stack_t {
    StackNode *_top;
    unsigned _size;
} Stack;


void stack_init(Stack *stack) {
    stack -> _size = 0;
    stack -> _top = NULL;
}

bool stack_isEmpty(Stack *stack) {
    return (stack -> _top == NULL);
}

void stack_push(Stack *stack, int value){
    StackNode *newNode = (StackNode*) malloc(sizeof(StackNode));
    if (newNode) {
        stack -> _size++;
        if (stack_isEmpty(stack)){
            newNode -> next = NULL;
            newNode -> max = value;
            newNode -> min = value;
        }
        else {
            if (value >= stack -> _top -> max) {
                newNode -> max = value;
            }
            if (value <= stack -> _top -> max) {
                newNode -> min = value;
            }
            if (value < stack -> _top -> max) {
                newNode -> max = stack -> _top -> max;
            }
            if (value > stack -> _top -> min) {
                newNode -> min = stack -> _top -> min;
            }
            newNode -> next = stack -> _top;
        }
        newNode -> data = value;
        stack -> _top = newNode;
    }
}

int stack_pop(Stack *stack) {
    if (!stack_isEmpty(stack)) {
        StackNode *temp = stack -> _top;
        stack -> _top = stack -> _top -> next;
        free(temp);
        stack -> _size--;
    }
    return 0;
}

unsigned stack_size(Stack *stack) {
    return stack -> _size;
}

int stack_top(Stack *stack) {
    if(!stack_isEmpty(stack)) {
        return stack -> _top -> data;
    }
    return 0;
}

int stack_greater(Stack *stack) {
    StackNode *temp = stack -> _top;
    int current = temp -> data;
    while (temp -> next != NULL) {
        if (temp -> next -> data > current) {
            current = temp -> next -> data;
            break;
        }
        temp = temp -> next;
    }
    return current;
}

int main() {
    Stack myStack;
    stack_init(&myStack);   
    int n, num;
    scanf("%d", &n);    
    for (int i = 1; i<= n; i++){
        scanf("%d", &num);
        stack_push(&myStack, num);
    }

    for (int i = 1; i< n; i++){
        if(stack_greater(&myStack) > stack_top(&myStack)) {
            printf("%d ", stack_greater(&myStack));
            stack_pop(&myStack);
        }
        else {
            printf("-1 ");
            stack_pop(&myStack);
        }   
    }
    printf("-1\n");

    puts("");
    return 0;
}
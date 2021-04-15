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

void stack_init(Stack *stack);
bool stack_isEmpty(Stack *stack);
void stack_push(Stack *stack, int);
int stack_pop(Stack *stack);
unsigned stack_size(Stack *stack);
int stack_top(Stack *stack);

int main() {
    Stack myStack;
    stack_init(&myStack);
    int i, n, num;
    char str[100];
    scanf("%d", &n);

    for(i=0; i<n; i++){
        scanf("%s", str);
        if (strcmp(str, "push")==0){
            scanf("%d", &num);
            stack_push(&myStack, num);
        }
        else if (strcmp(str, "pop")==0){
            stack_pop(&myStack);
        }
        else if (strcmp(str, "top")==0){
            printf("%d\n", myStack._top -> data);
        }
        else if (strcmp(str, "max")==0){
            printf("%d\n", myStack._top -> max);
        }
        else if (strcmp(str, "min")==0){
            printf("%d\n", myStack._top -> min);
        }
        else if (strcmp(str, "difference")==0){
            int diff;
            diff = myStack._top -> max - myStack._top -> min;
            printf("%d\n", diff);
        }
    }
}


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
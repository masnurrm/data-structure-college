#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

typedef struct stackNode_t {
    char data;
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

void stack_push(Stack *stack, char value) {
    StackNode *newNode = (StackNode*) malloc(sizeof(StackNode));
    if (newNode) {
        stack -> _size++;
        newNode - >data = value;
        
        if (stack_isEmpty(stack)) newNode -> next = NULL;
        else newNode -> next = stack -> _top;

        stack -> _top = newNode;
    }
}

void stack_pop(Stack *stack) {
    if (!stack_isEmpty(stack)) {
        StackNode *temp = stack -> _top;
        stack -> _top = stack -> _top -> next;
        free(temp);
        stack -> _size--;
    }
}

int stack_top(Stack *stack) {
    if (!stack_isEmpty(stack)) {
        return stack -> _top -> data;
    }
    return 0;
}

unsigned stack_size(Stack *stack) {
    return stack -> _size;
}

int main(int argc, char const *argv[]) {
    Stack myStack;
    stack_init(&myStack);
    char sentence[10001], tmp;
    scanf("%s", sentence);

    for (int i = 0; i < strlen(sentence); i++) {
        if(sentence[i] == 'T' || sentence[i] == '1' || sentence[i] == '2') {
            stack_push(&myStack, sentence[i]);
        }    

        if (sentence[i] == 'C') {
            tmp = stack_top(&myStack);
            stack_pop(&myStack);
            if(tmp == 'T')             {
                stack_pop(&myStack);
            }
            else {
                continue;
            }
        }

        else if (sentence[i] == '9') {
            tmp = stack_top(&myStack);
            stack_pop(&myStack);
            if(tmp == '1')             {
                stack_pop(&myStack);
            }
            else {
                continue;
            }
        }

        else if (sentence[i] == '0') {
            tmp = stack_top(&myStack);
            stack_pop(&myStack);
            if(tmp == '2')             {
                stack_pop(&myStack);
            }
            else {
                continue;
            }
        }        
    }

    int size = stack_size(&myStack);
    if (size == 0){    
        printf("DOPEBASEDLIT");
    }
    else {
        printf("No way!");
    }
    
    puts("");
    return 0;
}
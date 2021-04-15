#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct stackarray{
    char *_element, _topIndex;
    unsigned int _size, _capacity;
} StackArray;

void stackArray_init(StackArray *stack, unsigned stackSize);
bool stackArray_isEmpty(StackArray *stack);
void stackArray_push(StackArray *stack, int value);
void stackArray_pop(StackArray *stack);
int  stackArray_top(StackArray *stack);

void stackArray_init(StackArray *stack, unsigned int stackSize){
    stack->_element  = (char*) malloc(sizeof(char) * stackSize);
    stack->_size     = 0;
    stack->_topIndex = -1;
    stack->_capacity = stackSize;
}

bool stackArray_isEmpty(StackArray *stack){
    return (stack->_topIndex == -1);
}

void stackArray_push(StackArray *stack, int value){
    if (stack->_size + 1 <= stack->_capacity){
        stack->_element[++stack->_topIndex] = value;
        stack->_size++;
    }
}

void stackArray_pop(StackArray *stack){
    if (!stackArray_isEmpty(stack)) {
        stack->_topIndex--;
        stack->_size--;
    }
}

int stackArray_top(StackArray *stack){
    if (!stackArray_isEmpty(stack)) {
        return stack->_element[stack->_topIndex];
    }
    return 0;
}

int main(){
    StackArray myStack;
    char str[101];
    gets(str);
    stackArray_init(&myStack, 101);
    int index, tf;
    index=strlen(str)/2;
    
    for(int i=index; i<strlen(str); i++){
        stackArray_push(&myStack, str[i]);
    }

    for(int i=0; i<index; i++){
        char temp=stackArray_top(&myStack);
        stackArray_pop(&myStack);
        if(temp!=str[i]){
            tf=0;
            printf("mahal, eh bukan palindrom deh\n");
            break;
        }else{
            tf=1;
        }
    }

    if(tf==1){
        printf("palindrom\n");
    }
    return 0;
}
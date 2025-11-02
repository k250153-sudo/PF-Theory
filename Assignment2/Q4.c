#include <stdio.h>

void push(int stack[], int *top, int maxSize) {
    if (*top == maxSize-1) {
        printf("Stack Overflow!\n");
    }
    else {
        (*top) ++;
        printf("Enter the item you want to add in the stack:");
        scanf("%d",&stack[*top]);
    }
}
void pop(int stack[], int *top) {
    if (*top == -1) {
        printf("Stack Underflow!\n");
    }
    else {
        printf("The value popped is %d\n",stack[*top]);
        (*top) --;
    }
}
void peek(int stack[], int top) {
    if (top == -1) {
        printf("Stack is empty!\n");
    } else {
        printf("The value at top is %d\n", stack[top]);
    }
}
void display(int stack[], int top) {
    if (top == -1) {
        printf("Stack is empty!\n");
    }
    else {
        printf("The current stack is:\n");
        for (int i = top; i >= 0; i--) {
            printf("%d\n---\n ", stack[i]);
        }
    }
}
int main() {
    printf("Enter the size of the stack:");
    int maxsize,option;
    int top = -1;
    scanf("%d",&maxsize);
    int stack[maxsize];
    do {
        printf("What function would you like to perform:\n 1.Push\n 2.Pop\n 3.Peek\n 4.Display\n 5.Exit\n"
               "Please enter the option number:");
        scanf("%d",&option);
        switch (option) {
            case 1:
                push(stack, &top, maxsize);
                break;
            case 2:
                pop(stack, &top);
                break;
            case 3:
                peek(stack, top);
                break;
            case 4:
                display(stack, top);
                break;
            case 5:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid option! Try again.\n");
        }
    }
    while (option != 5);
    return 0;
}


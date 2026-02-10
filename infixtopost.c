#include <stdio.h>
#include <ctype.h> // Required for isalnum()

#define MAX 50

// Stack Structure
struct Stack {
    char s[MAX];
    int top;
};

void init(struct Stack *st) {
    st->top = -1;
}

int isEmpty(struct Stack *st) {
    return st->top == -1;
}

int isFull(struct Stack *st) {
    return st->top == MAX - 1;
}

void push(struct Stack *st, char x) {
    if (!isFull(st)) {
        st->s[++st->top] = x;
    }
}

char pop(struct Stack *st) {
    if (!isEmpty(st)) {
        return st->s[st->top--];
    }
    return -1;
}

char peek(struct Stack *st) {
    if (!isEmpty(st)) {
        return st->s[st->top];
    }
    return -1;
}

// Priority Function
int priority(char x) {
    if (x == '+' || x == '-')
        return 1;
    if (x == '*' || x == '/')
        return 2;
    if (x == '^')
        return 3;
    return 0;
}

// Main Conversion Logic
void infixToPostfix(char infix[]) {
    struct Stack st;
    init(&st);
    int i = 0;
    char symbol;

    while (infix[i] != '\0') {
        symbol = infix[i];

        if (isalnum(symbol)) {
            printf("%c", symbol);
        } 
        else if (symbol == '(') {
            push(&st, symbol);
        } 
        else if (symbol == ')') {
            while (peek(&st) != '(') {
                printf("%c", pop(&st));
            }
            pop(&st); // Pop the '('
        } 
        else {
            // Operator encountered
            while (!isEmpty(&st) && priority(peek(&st)) >= priority(symbol)) {
                printf("%c", pop(&st));
            }
            push(&st, symbol);
        }
        i++;
    }

    // Pop remaining operators from stack
    while (!isEmpty(&st)) {
        printf("%c", pop(&st));
    }
    printf("\n");
}

int main() {
    char infix[MAX];
    printf("Enter Infix: ");
    scanf("%s", infix); // Replaced shorthand 'S' and 'P'
    
    printf("Postfix Expression: ");
    infixToPostfix(infix);
    
    return 0;
}
#ifndef FOO_H_
#define FOO_H_
typedef struct Stack Stack;
typedef struct Item Item;
int str_ln(char* c_str);
char* mmc(char*s1, char* s2, int n);
char* input(int *len);
Stack* stack_new();
void freet(Stack* s);
void stack_push(Stack *stack, int value);
int pop(Stack *stack);
void stack_delete(Stack* s);
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include<string.h>
#include <ctype.h>
#include"head.h"
int str_ln(char* str)
{
    int count=0;
    while(*str++) ++count;
    return count;
}
char* mmc(char*s1, char* s2, int n)
{
        for ( int i =0; i<n; i++)
        {
                s1[i]=s2[i];
        }
        return s1;

}
char* input(int *len)
{
    char buf[81] = { 0 };
    char* res = (char*)malloc(1);
    *len = 0;
    int n;
    *res = '\0';
    do {
        n = scanf("%80[^\n]", buf);
        if (n < 0)
        {
            free(res);
            return NULL;
        }
        else if (n > 0)
        {
            int chunk_len = str_ln(buf);
            //printf("%d\n", chunk_len);
            int str_len = *len + chunk_len;
            res = (char*)realloc(res, str_len + 1);
            mmc(res + *len, buf, chunk_len);
            *len = str_len;
        }
        else
        {
            scanf("%*c");
        }
    } while (n > 0);
    if (*len > 0)
    {
        res[*len] = '\0';
        *len=*len+1;
    }
    else
    {
//        res = (char*)calloc(1, sizeof(char));
        *len=1;
    }
    return res;
}
typedef struct Stack {
    int *data;
    size_t size;
    size_t top;
} Stack;
Stack* stack_new() {
    Stack *s = NULL;
    s = malloc(sizeof(Stack));
    if (s == NULL) {
	return NULL;
    }
    s->size = 10;
    s->data = malloc(s->size * sizeof(int));
    if (s->data == NULL) {
        free(s);
	return NULL;
    }
    s->top = 0;
    return s;
}
void freet(Stack* s){
    free(s->data);
    free(s);
    s = NULL;
}
void stack_push(Stack *stack, int value) {
    if (stack->top >= stack->size) {
            stack->size *= 2;
	    stack->data = realloc(stack->data, stack->size * sizeof(int));
    	    if (stack->data == NULL) {
       		 return;
    	    }

    }
    stack->data[stack->top] = value;
    stack->top++;
}

int pop(Stack *stack) {
    if (stack->top == 0) {
        printf("Error\n");
        return 2;
    }
    stack->top--;
    return stack->data[stack->top];
}
void stack_delete(Stack* s){
    free(s->data);
    free(s);
    s = NULL;
}

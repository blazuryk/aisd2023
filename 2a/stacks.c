#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include<string.h>
#include <ctype.h>
#include"head.h"
int str_ln(char* c_str)
{
    int count=0;
    while(*c_str++) ++count;
    return count;
}
char* mmc(char*s1, char* s2, int n)\
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

typedef struct Item {
    int data;
    struct Item *next;
} Item;

typedef struct Stack {
    Item *head;
} Stack;


Stack *stack_new() {
    return (Stack *) calloc(1, sizeof(Stack));
}
void stack_delete(Stack *stack) {
    Item *ptr = stack->head, *ptr_prev;
    while (ptr) {
        ptr_prev = ptr;
        ptr = ptr->next;
        free(ptr_prev);
    }
    free(stack);
}

void stack_push(Stack *stack, int data) {
    Item *new = (Item *) malloc(sizeof(Item));
    if (!new) {
//        return 1;
	exit(0);
    }
    new->data = data;
    new->next = stack->head;
    stack->head = new;
//    return 0;
}

int pop(Stack* s) {
    if (s->head == NULL) {
        printf("Stack underflow\n");
        return 2;
    }
    Item* node = s->head;
    int value = node->data;
    s->head = node->next;
    free(node);
    return value;
}
void freet(Stack* s){
        free(s);
}


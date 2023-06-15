#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include<string.h>
#include <ctype.h>
#include"head.h"
int main() {
    while(1){
    int len=1;
    int counter1=0;
    int counter2=0;
    printf("Enter the string\n");
    char* res=input(&len);
    while(len==1){
        free(res);
        printf("Enter the string\n");
        res=input(&len);
    }
    if(res==NULL){
        exit(0);
    }
    Stack* s= stack_new();
    char* el=res;
    int flag=0;
    el=el+strlen(res)-1;
    int k=strlen(res)-1;
    while(k>=0){
        if((*el=='0') || (*el=='1')){
            stack_push(s,(*el-'0'));
            counter1++;
        }
        else  if (*el == '&')
        {
            int a = pop(&(*s));
            int b = pop(&(*s));
            if (a==2 || b==2){
                free(res);
                freet(&(*s));
                flag=1;
                break;
            }
            counter2++;
            stack_push(&(*s), a && b);
        }
        else if ((*el == '|') && (*(el-1)=='|'))
        {
            int a = pop(&(*s));
            int b = pop(&(*s));
            if (a==2 || b==2){
                free(res);
                freet(&(*s));
                flag=1;
                break;
            }
            stack_push(&(*s), a || b);
            k--;
            el=el-1;
            counter2++;
        }
        else if (*el == '!') {
            int a = pop(&(*s));
            if (a==2){
                free(res);
                freet(&(*s));
                flag=1;
                break;
            }
            stack_push(&(*s), !a);
        }
        else{
            printf("Error\n");
            stack_delete(&(*s));
            free(res);
            flag=1;
            break;

        }
        k--;
        el=el-1;
    }
    if (flag==1){
        continue;
    }
    if(counter2!=(counter1-1)){
        printf("Error\n");
        stack_delete(&(*s));
        free(res);
        continue;
    }
    printf("result= %d\n", pop(&(*s)));
    stack_delete(&(*s));
    free(res);
    }
    return 0;

}

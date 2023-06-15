#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<string.h>
#include<readline/readline.h>
#include<readline/history.h>
#include"func.h"
static const char* msgs[]={"0.Quit", "1.Add", "2.Find", "3.Delete", "4.Show", "5.Import", "6.Indtask"};
static const int Nmsgs=sizeof(msgs)/sizeof(msgs[0]);
static const char *errmsgs[]={"OK", "Duplicate key", "Table overflow", "Table empty", "Error in file"};
static int (*fptr[])(Table*)={NULL, D_Add, D_Find, D_Delete, D_Show, D_Import, D_Indtask};

int main()
{
    Table* table=init();
    int rc;
    while(rc=dialog(msgs, Nmsgs)){
        if(!fptr[rc](table)){
            break;
        }
    }
    printf("Thx, Bye!\n");
    deleteTable(table);
}

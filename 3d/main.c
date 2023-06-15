#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<readline/readline.h>
#include<readline/history.h>
#include <unistd.h>
#include <sys/types.h>
#include"func.h"
static const char* msgs[]={"0.Quit", "1.Add", "2.Find", "3.Delete", "4.Show", "5.Import"};
static const int Nmsgs=sizeof(msgs)/sizeof(msgs[0]);
static const char *errmsgs[]={"OK", "Duplicate key", "Table overflow", "Table empty", "Error in file", "Not found"};
static int (*fptr[])(Table*)={NULL, D_Add, D_Find, D_Delete, D_Show, D_Import};
int main()
{
    Table* table=init();
    int rc;
    if(D_Load(table)==0){
                return 1;
        }
    while(rc=dialog(msgs, Nmsgs)){
        if(!fptr[rc](table)){
            break;
        }
    }
    save(table);
    printf("Thx, Bye!\n");
    deleteTable(table);
}
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<string.h>
#include<readline/readline.h>
#include<readline/history.h>
#include"func.h"
static const char* msgs[]={"0.Quit", "1.Add", "2.Find", "3.Delete", "4.Show", "5.Import"};
static const int Nmsgs=sizeof(msgs)/sizeof(msgs[0]);
static const char *errmsgs[]={"OK", "Duplicate key", "Table overflow", "Table empty", "Error in file","Not found"};
int getInt(int* b){
    int k;
    int r =scanf("%d", &k);
    if(r==1){
        if(k>=0){
        *b=k;
         scanf("%*[^\n]");
         scanf("%*c");
        return 1;
        }
        else{
            return 0;
        }
    }
    if (r==0){
         scanf("%*[^\n]");
         scanf("%*c");
        return 0;
    }
    if (r==-1){
        scanf("%*[^\n]");
        scanf("%*c");
        return -1;
    }
}
int recsr(int a, int b) {
    if (b == 0) {
        return a;
    }
    return recsr(b, a % b);
}

int vzpr(int n) {
    int prost = 2;
    while (1) {
        if (recsr(n, prost) == 1) {
            return prost;
        }
        prost++;
    }
}
int dialog(const char * msgs[], int N){
    char *errmsg="";
    int rc;
    int i, n;
    do{
        puts(errmsg);
        errmsg="You are wrong.Repeat please!";
        for(i =0; i<N; i++){
            puts(msgs[i]);
        }
        puts("Make your choise: -->");
        n=getInt(&rc);
        if(n==-1){
            rc=0;
        }
        if(n==0){
            rc=-1;
        }
    }while(rc<0 || rc >=N);
    return rc;
}
unsigned long long hash(unsigned char *str)
{
    unsigned long h = 5381;

    for(int i=0; str[i]; i++){
        h=23*h*str[i];
    }

    return h;
}
int D_Show(Table* table){
    if(table==NULL){
        return 0;
    }
    if(table->data==NULL){
        printf("Table if empty\n");
        return 1;
    }
    for(int i=0; i<table->capacity; i++){
        if(table->data[i].busy==1){
        printf("key: %s  info : %s \n", table->data[i].key,table->data[i].info);
        }
    }
    return 1;
}
int insert(Table* table, char* key, char* info);
int impttb(Table* table, char* name){
        FILE *file;
        char* key;
        char str[50];
        char str1[50];
        int records=0;
        char* info;
        int rc;
        int k=0;
        file=fopen(name, "r");
        free(name);
        if(file==NULL){
                return 4;
        }
        int read=0;
        while(read=fscanf(file, "%50[^,]%*c%50[^\n]%*c", str,str1)!=EOF){
                if(read!=1 && feof(file)){
                        return 4;
                }
/*        table->csize++;
        if(table->csize>table->maxsize){
                table->csize=k;
                fclose(file);
                return 2;
        }
        table->csize--;*/
        key=strdup(str);
        info=strdup(str1);
        printf("key = %s, info= %s\n", key, info);
        rc=insert(table, key, info);
        free(key);
        free(info);
        k++;
        printf("%s:  %d\n", errmsgs[rc], k);
        if(rc==2){
            return 0;
            break;
        }
        if(read==1) records++;
        }while(!feof(file));
         fclose(file);
        return 0;
}
int D_Import(Table* table){
        char* name=readline("Enter th name of file\n");
        if(name==NULL){
            return 0;
        }
        int rc=impttb(table, name);
        printf("%s\n", errmsgs[rc]);
        return 1;
}
Item finder(Table* table, char* key);
int insert(Table* table, char* key, char* info){
    if(table == NULL){
        return 2;
    }
    int index=hash(key)%table->capacity;
    Item rc=finder(table, key);
    if(rc.info!=NULL){
        return 1;
    }
    printf("%d\n", index);
    for (int i = 0; i < table->capacity; i++) {
        if (table->data[index].busy == 0 || table->data[index].busy == 2) {
            table->data[index].key = strdup(key);
            table->data[index].info = strdup(info);
            table->data[index].busy = 1;
            return 0;
        } else if (strcmp(table->data[index].key, key) == 0) {
            return 1;
        }
        index = (index + table->step) % table->capacity;
    }
    return 2;
}
int D_Add(Table *ptab){
    int rc, n, p, t;
    char* key;
    char* info;
 //   printf("Enter Key:-->\n");
//    scanf("%*[^\n]");
//    scanf("%*c");
    key=readline("Enter Key:-->\n");
    if(key==NULL){
        return 0;
    }
//    scanf("%*[^\n]");
//    scanf("%*c");
    info=readline("Enter info:-->\n");
    if(info==NULL){
        return 0;
    }
//    scanf("%*[^\n]");
//    scanf("%*c");

    rc=insert(ptab, key, info);
    printf("%s: %s\n:", errmsgs[rc], key);
    free(key);
    free(info);
    return 1;
}
Item finder(Table* table, char* key){
    int index=hash(key)%table->capacity;
    for(int i=0; i<table->capacity; i++){
        if (table->data[index].busy == 0){
  //          printf("key not found\n");
            Item sk;
            sk.busy=0;
            sk.info=NULL;
            sk.key=NULL;
            return sk;
        }
        else if(table->data[index].busy == 1){
            if(strcmp(key, table->data[index].key)==0){
                return table->data[index];
            }
        }
        index = (index + table->step) % table->capacity;
    }
             Item sk;
             sk.busy=0;
             sk.info=NULL;
             sk.key=NULL;
             return sk;

}
int D_Find(Table* table){
    if(table==NULL){
        return 0;
    }
 //   printf("Enter the key,wich you want to find\n");
    char* key=readline("Enter the key, wich you want to find\n");
    Item rc=finder(table, key);
    if (rc.info==NULL){
        printf("Key not found");
        free(key);
        return 1;
    }
    printf("key= %s, info = %s", rc.key, rc.info);
    free(key);
    return 1;
}
int deletekey(Table* table, char* key){
    if(table==NULL){
        return 0;
    }
    int index=hash(key)%table->capacity;
    for(int i=0; i<table->capacity; i++){
        if(table->data[index].busy==0){
 //           printf("key not found\n");
            return 5;
        }
        else if(table->data[index].busy==1){
            if(strcmp(key, table->data[index].key)==0){
                table->data[index].busy=2;
                free(table->data[index].key);
                free(table->data[index].info);
                return 0;
            }
        }
        index=(index+table->step)%table->capacity;
    }
    return 5;
}
int D_Delete(Table* table){
    if(table==NULL){
        return 0;
    }
    char* key=readline("Enter the key, wich you want to delete\n");
    if(key==NULL){
        return 0;
    }
    int rc=deletekey(table, key);
    free(key);
    printf("%s\n", errmsgs[rc]);
    return 1;
}
int deleteTable(Table* table){
    if(table->data!=NULL){
        for(int index=0; index<table->capacity; index++){
                if(table->data[index].busy==1){
                        free(table->data[index].info);
                        free(table->data[index].key);
                }
        }
        free(table->data);
    }
    free(table);
}
Table* init(){
    Table* table=malloc(sizeof(Table));
    table->data=NULL;
    int rc;
//    table->step=1;
    printf("Enter maxsize\n");
    int t= getInt(&rc);
    while((t!=1) || (rc<=0)){
        if(t==-1){
            return NULL;
        }
        printf("Error maxsize, try again\n");
        t=getInt(&rc);
    }
    table->step=vzpr(rc);
    table->capacity=rc;
    table->data=calloc(rc,sizeof(Item));
    return table;
}

static int (*fptr[])(Table*)={NULL, D_Add, D_Find, D_Delete, D_Show, D_Import};


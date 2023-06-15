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
int insert(Table* table, char* key, char* info);
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

unsigned long long hash(unsigned char *str)
{
    unsigned long hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
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
int deleteTable(Table* table){
    if(table->data!=NULL){
        free(table->data);
    }
    free(table);
}
int D_Show(Table* table){
        if(table==NULL){
                return 0;
        }
        if(table->csize==0){
                printf("Empty table\n");
                return 1;
        }
        char* info;
        char* key;
        fseek(table->fd, 0, SEEK_SET);
        for(int i=0; i<table->capacity; i++){
                if(table->data[i].busy==1){
                fseek(table->fd, table->data[i].offsetinfo, SEEK_SET);
                info=(char*)malloc(table->data[i].leninfo);
                fread(info, sizeof(char), table->data[i].leninfo, table->fd);
                fseek(table->fd, table->data[i].offsetkey, SEEK_SET);
                key=(char*)malloc(table->data[i].lenkey);
                fread(key, sizeof(char), table->data[i].lenkey, table->fd);
                printf("key= %s  info=%s \n", key, info);
                free(info);
                free(key);
                }
        }
        return 1;
}
int create(Table* table, char* fname, int maxsize){
        table->capacity=maxsize;
//      printf("maxsiz = %d\n", table->maxsize);
        table->csize=0;
        table->step=vzpr(maxsize);;
        table->fd=fopen(fname, "w+b");
//      if(fopen_s(&(table->fd), fname, "w+b")!=0){
        if(table->fd==NULL){
                table->data=NULL;
                return 0;
        }
//      table->fd=fname;
//      printf("name= %s\n", table->fd);
        table->data=(Item*)calloc(table->capacity, sizeof(Item));
        fwrite(&table->capacity, sizeof(int), 1, table->fd);
        fwrite(&table->csize, sizeof(int), 1, table->fd);
        fwrite(&table->step, sizeof(int), 1, table->fd);
        fwrite(table->data, sizeof(Item), table->capacity, table->fd);
        return 1;
}
int save(Table *table){
        fseek(table->fd, sizeof(int), SEEK_SET);
        fwrite(&table->csize, sizeof(int), 1, table->fd);
        fwrite(&table->step, sizeof(int), 1, table->fd);
        fwrite(table->data, sizeof(Item), table->capacity, table->fd);//try
        fclose(table->fd);
        table->fd=NULL;
        return 1;
}
int impttb(Table* table, char* name){
        FILE *file;
        char* key;
 //       unsigned int par;
        int records=0;
        char* info;
        int rc;
        char str[50];
        char str1[50];
        int k=table->csize;
        file=fopen(name, "r");
        free(name);
        if(file==NULL){
                return 4;
        }
        int read=0;
        while(read=fscanf(file, "%50[^,]%*c%50[^\n]%*c", str, str1)!=EOF){
                if(read!=1 && feof(file)){
                        return 4;
                }
        table->csize++;
        if(table->csize>table->capacity){
                table->csize=k;
                fclose(file);
                return 2;
        }
        table->csize--;
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


Table* init(){
        Table* table=malloc(sizeof(Table));
        table->capacity=0;
        table->csize=0;
        table->data=NULL;
        table->fd=NULL;
}
int load(Table* table, char* fname){
        table->fd=fopen(fname, "r+b");
        if(table->fd==NULL){
                return 0;
        }
        fread(&table->capacity, sizeof(int), 1, table->fd);
        table->data=(Item*)calloc(table->capacity, sizeof(Item));
        fread(&table->csize, sizeof(int), 1, table->fd);
        fread(&table->step, sizeof(int), 1, table->fd);
        fread(table->data, sizeof(Item), table->capacity, table->fd);
        return 1;
}
int D_Load(Table* table){
        int maxsize;
        char* fname=NULL;
        int n;
        fname=readline("Enter the name of the file\n");
        if(fname==NULL){
                return 0;
        }
        if(load(table,fname)==0){
                printf("Enter possible vector size: -->");
                n=getInt(&maxsize);
                while(n!=1){
                        if(n==-1){
                        return 0;
                        }
                        printf("Error\n");
                        n=getInt(&maxsize);
                }
                printf("maxsize = %d\n", maxsize);
                create(table,fname,maxsize);
        }
        free(fname);
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
            free(key);
            return 5;
        }
        else if(table->data[index].busy==1){
            fseek(table->fd, table->data[index].offsetkey, SEEK_SET);
            char* k=(char*)malloc(table->data[index].lenkey);
            fread(k, sizeof(char), table->data[index].lenkey, table->fd);
            if(strcmp(key, k)==0){
                table->csize--;
                free(key);
                free(k);
                table->data[index].busy=2;
                return 1;
            }
            //free(key);
            free(k);
        }
        index=(index+table->step)%table->capacity;
    }
    return 2;
    free(key);
}
int D_Delete(Table* table){
        if(table==NULL){
                return 0;
        }
        int rc;
        char* key=readline("Enter the key, wich you want to delete\n");
        if(key==NULL){
                return 0;
        }
        rc=deletekey(table, key);
        printf("%s\n", errmsgs[rc]);
        return 1;
}
char* findInfo(Table*table, char* k){
    char* key;
    int index=hash(k)%table->capacity;
        for(int i=0; i<table->capacity; i++){
        if (table->data[index].busy == 0){
//            printf("key not found\n");
            return NULL;
//            return {0, 0, NULL};
        }
        else if(table->data[index].busy == 1){
            fseek(table->fd, table->data[index].offsetkey, SEEK_SET);
            key=(char*)malloc(table->data[index].lenkey);
            fread(key, sizeof(char), table->data[index].lenkey, table->fd);
            if(strcmp(key, k)==0){
                free(key);
                fseek(table->fd, table->data[index].offsetinfo, SEEK_SET);
                char* info=(char*)malloc(table->data[index].leninfo);
                fread(info, sizeof(char), table->data[index].leninfo, table->fd);
                return info;
            }
            free(key);
        }
        index = (index + table->step) % table->capacity;
    }
    return NULL;
}
int D_Find(Table* table){
        char* info;
        char* k;
        int i,j;
 //       puts("Enter key:-->");
        k=readline("Enter the key\n");
        if(k==NULL){
            return 0;
        }
 /*       n=getInt(&k);
        while(n!=1){
                if(n==-1){
                return 0;
                }
                printf("Error\n");
                n=getInt(&k);
        }*/
        info= findInfo(table,k);
        if(info==NULL){
            printf("Not found\n");
            free(k);
            return 1;
        }
/*        if(info>0){
                j=find(table,k);
                printf("key = %d, par= %d, info =%d \n", k, table->ks[j].par, info);
        }
        else{
                printf("Item %d was not found\n", k);
        }*/
        printf("key=%s, info = %s\n", k, info);
        free(k);
        free(info);
        return 1;
}
int insert(Table* table, char* key, char* info){
    if(table == NULL){
        return 2;
    }
        char* info1=findInfo(table, key);
        if(info1!=NULL){
                free(info1);
                return 1;
        }
    int index=hash(key)%table->capacity;
    for (int i = 0; i < table->capacity; i++) {
        if (table->data[index].busy == 0 || table->data[index].busy == 2) {
            table->csize++;
            table->data[index].busy=1;
            // insert the new element

            table->data[index].lenkey=strlen(key)+1;
            table->data[index].leninfo=strlen(info)+1;
            fseek(table->fd, 0,SEEK_END);
            table->data[index].offsetkey = ftell(table->fd);
            fwrite(key, sizeof(char),table->data[index].lenkey, table->fd);
           fseek(table->fd, 0,SEEK_END);
           table->data[index].offsetinfo = ftell(table->fd);
            fwrite(info, sizeof(char),table->data[index].leninfo, table->fd);
            //table->data[index].info = strdup(info);
            //free(key);
            //free(info);
            //table->data[index].busy = 1;
            return 0;
        } else if (table->data[index].busy == 1) {
            fseek(table->fd, table->data[index].offsetkey, SEEK_SET);
            char* k=(char*)malloc(table->data[index].lenkey);
            fread(k, sizeof(char), table->data[index].lenkey, table->fd);
            if(strcmp(key, k)==0){
  //              free(key);
                free(k);
                return 1;
            }
//            free(key);
            free(k);
            // key already exists in the table
        }
        index = (index + table->step) % table->capacity;
    }
    return 2;
}
int D_Add(Table* table){
        int rc, n;
        char* k;
        char* info;
        k=readline("Enter the key:\n");
        if (k==NULL){
            return 0;
        }
        info=readline("Enter the info\n");
        if(info==NULL){
            free(k);
            return 0;
        }

        rc=insert(table, k, info);
        printf("%s:  %s\n", errmsgs[rc], k);
        free(k);
        free(info);
        return 1;
}
static int (*fptr[])(Table*)={NULL, D_Add, D_Find, D_Delete, D_Show, D_Import};

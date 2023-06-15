#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<readline/readline.h>
#include<readline/history.h>
#include <unistd.h>
#include <sys/types.h>
#include<time.h>
#include"func.h"
static const char* msgs[]={"0.Quit", "1.Add", "2.Find", "3.Delete", "4.Show", "5.Import","6.Indtask","7.Traversal","8.Timerf","9.TimerInsr","10.Timerdel"};
static const int Nmsgs=sizeof(msgs)/sizeof(msgs[0]);
static const char *errmsgs[]={"OK", "Duplicate key", "Table overflow", "Table empty","Not found"};
int getInt(int* b){
    int k;
    int r =scanf("%d", &k);
    if(r==1){
        if(k>=0){
        *b=k;
  //       scanf("%*[^\n]");
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
Node* insert(Node* root, int key, int info);
int impttb(Node** table, char* name){
        FILE *file;
        int key;
        int records=0;
        int info;
        int rc=0;
        int k=0;
        file=fopen(name, "r");
        free(name);
        if(file==NULL){
                return 4;
        }
        int read=0;
        while(read=fscanf(file, "%d%*c%d%*c", &key,&info)!=EOF){
                if(read!=1 && feof(file)){
                        return 4;
                }
        printf("key = %d, info= %d\n", key, info);
        *table=insert(*table, key, info);
   //    free(key);
    //    free(info);
        k++;
//        printf("%s:  %d\n", errmsgs[rc], k);
        printf("OK:  %d\n", k);
        if(rc==2){
            return 0;
            break;
        }
        if(read==1) records++;
        }while(!feof(file));
         fclose(file);
        return 0;
}
int D_Import(Node** root){
        char* name=readline("Enter th name of file\n");
        if(name==NULL){
            return 0;
        }
        int rc=impttb(root, name);
        printf("%s\n", errmsgs[rc]);
        return 1;
    return 0;
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
Node* createNode(int key, int info) {
    Node* node = malloc(sizeof(Node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->par = NULL;
    node->data = (int*)malloc(sizeof(int));
    node->data[0] = info;
    node->size = 1;
    return node;
}
Node* insert(Node* root, int key, int info){
    if(root==NULL){
        root=createNode(key, info);
        return root;
    }
    else if(root->key==key){
        root->data=realloc(root->data, (root->size+1)*sizeof(int));
        root->data[root->size]=info;
        root->size++;
    }
    else if(root->key<key){
        Node* right=insert(root->right, key, info);
        root->right=right;
        right->par=root;

    }
    else{
        Node* left=insert(root->left, key, info);
        root->left=left;
        left->par=root;

    }
    return root;
}
Node* find(Node* root, int key) {
    if (root == NULL || root->key == key) {
        return root;
    }
    if (key < root->key) {
        return find(root->left, key);
    } else {
        return find(root->right, key);
    }
}
Node* minimum(Node* temp) {
    while (temp->left != NULL) {
        temp = temp->left;
    }
    return temp;
}
void trans(struct Node* h, struct Node* g) {
    if (h->par == NULL) {
        g->par=NULL;
        return;
    }
    if (h == h->par->left) {
        h->par->left = g;
    } else {
        h->par->right = g;
    }
    if (g != NULL) {
        g->par = h->par;
    }
}
Node* findClosest(Node* root, unsigned int val) {
    Node* clos = NULL;
    int minDiff = 99999;
    Node* cur = root;

    while (cur != NULL) {
        int diff = abs((int)cur->key - (int)val);
        if (diff < minDiff && cur->key != val) {
            minDiff = diff;
            clos = cur;
        }

        if (cur->key < val) {
            cur = cur->right;
        } else {
            cur = cur->left;
        }
    }

    return clos;
}
void print_reversed(Node* node, unsigned int max_key) {
    if (node == NULL) {
        return;
    }
    if (node->key > max_key) {
        print_reversed(node->left, max_key);
    } else {
        print_reversed(node->right, max_key);
        if (node->key <= max_key) {
            printf("%u ", node->key);
        }
        print_reversed(node->left, max_key);
    }
}
int deleteel(Node** root, int key, int value){
    Node* temp=find(*root, key);
    if(temp==NULL){
        return 5;
    }
    if(temp->size>1){
//      printf("%d  %d asd\n",temp->size, value);
        if((value > temp->size) || (value==0)){
//          printf("keads\n");
            return 5;
        }
        for (int i = value-1; i < temp->size - 1; i++) {
                temp->data[i] = temp->data[i + 1];
        }
        temp->size--;
        temp->data = (int*)realloc(temp->data, sizeof(int) * temp->size);
        return 0;
    }
     else if((temp->size==1) && (value>1) && (value==0)){
                return 5;
        }
       Node* parent=temp->par;
     if(temp->right==NULL && temp->left==NULL){
        if(parent==NULL){
   //         free(temp->key);
            free(temp->data);
            free(temp);
            *root=NULL;
            return 0;
        }
        if(parent->left==temp){
            parent->left=NULL;
 //           free(temp->key);
            free(temp->data);
            free(temp);
            return 0;
        }
    }
    else if(temp->right==NULL){
        if(parent==NULL){
            *root=temp->left;
//            free(temp->key);
            temp->left->par=NULL;
            free(temp->data);
            free(temp);
            return 0;
        }
        if(parent->left==temp){
            parent->left=temp->left;
            temp->left->par=parent;
//            free(temp->key);
            free(temp->data);
            free(temp);
            return 0;
        }
        else{
            parent->right=temp->left;
            temp->left->par=parent;
//            free(temp->key);
            free(temp->data);
            free(temp);
            return 0;
        }
    }
    else if(temp->left==NULL){
        if(parent==NULL){
            *root=temp->right;
             temp->right->par=NULL;
//            free(temp->key);
            free(temp->data);
            free(temp);
            return 0;
        }
        if(parent->left==temp){
            parent->left=temp->right;
            temp->right->par=parent;
//            free(temp->key);
            free(temp->data);
            free(temp);
            return 0;
        }
        else{
            parent->right=temp->right;
            temp->right->par=parent;
//            free(temp->key);
            free(temp->data);
            free(temp);
            return 0;
        }
    }
    else{
        Node* min=temp->right;
        while(min->left!=NULL){
            min=min->left;
        }
        Node* ch= min->par;
        if(ch->left==min){
            ch->left=min->right;
//          min->right->par=ch;
        }
        else{
            ch->right=min->right;
//          min->right->par=ch;
        }
        if(parent==NULL){
               *root=min;
               min->right=temp->right;
               temp->right->par=min;
               min->left=temp->left;
               temp->left->par=min;
               min->par=NULL;
 //              free(temp->key);
               free(temp->data);
               free(temp);
               return 0;
        }
        Node * glav=temp->par;
        if(glav->right==temp){
            glav->right=min;
            min->par=glav;//
            min->right=temp->right;
            if(temp->right!=NULL){
            temp->right->par=min;
            }
            min->left=temp->left;
            if(temp->left!=NULL){
            temp->left->par=min;
            }
//            free(temp->key);
            free(temp->data);
            free(temp);
            return 0;
        }
        else{
            glav->left=min;
            min->par=glav;
            min->right=temp->right;
            if(temp->right!=NULL){
            temp->right->par=min;
            }
            min->left=temp->left;
            if(temp->left!=NULL){
            temp->left->par=min;
                }
 //           free(temp->key);
            free(temp->data);
            free(temp);
            return 0;

        }

    }
}
void deleteTree(Node *node) {
    if (node == NULL) {
        return;
    }
    deleteTree(node->left);
    deleteTree(node->right);
    free(node->data);
    free(node);
}
void printTree(Node* root, int lvl) {
    if (root == NULL) {
        return;
    }

    printTree(root->right, lvl + 1);

    for (int i = 0; i < lvl; i++) {
        printf("  ");
    }

    int count = 0;
    Node* node = root;
    while (node != NULL && node->key == root->key) {
        count++;
        node = node->left;
    }

    printf("%u", root->key);
    if (root->size > 1) {
        printf(" (x%d)", root->size);
    }
    printf("\n");

    printTree(root->left, lvl + 1);
}
int D_Show(Node** root){
    if(*root==NULL){
        printf("Tree is empty\n");
        return 1;
    }
    printTree(*root, 0);
    return 1;

}
int D_Traversal(Node** root){
       if(*root==NULL){
        printf("Tree is empty\n");
        return 1;
    }


        int key;
 //   int info;
    int t= getInt(&key);
    printf("Enter the maxkey\n");
    while(t!=1){
        if(t==-1){
            return 0;
        }
        printf("Error\n");
        t=getInt(&key);
    }
    print_reversed(*root, key);
    return 1;
}
int D_Indtask(Node** root){
    if(*root==NULL){
        printf("Tree is empty\n");
        return 1;
    }


        int key;
 //   int info;
 printf("Enter the key, which you whant to find\n");
    int t= getInt(&key);
 //   printf("Enter the key, which you whant to find\n");
    while(t!=1){
        if(t==-1){
            return 0;
        }
        printf("Error\n");
        t=getInt(&key);
    }
    Node* temp=findClosest(*root, key);
//    printTree(temp, 0);
    if(temp==NULL){
                printf("Not found\n");
                return 1;
        }
    if (temp->size>1){
    printf("Enter the ver, which you whant to find\n");
            int ver;
            t= getInt(&ver);
        while(t!=1){
                if(t==-1){
                        return 0;
                }
                printf("Error\n");
                t=getInt(&ver);
        }
        if((ver>temp->size) || (ver<=0)){
                printf("Not found\n");
                return 1;
        }
        printf("key= %d info= %d \n", temp->key, temp->data[ver-1]);
         return 1;
        }
    else{
                 printf("key= %d info= %d \n", temp->key, temp->data[0]);
                return 1;
        }
}
int D_Add(Node** root){
    int rc, ver, p;
    int key;
    int info;
    printf("Enter the key,wich you want to insert\n");
    int t= getInt(&key);

    while(t!=1){
        if(t==-1){
            return 0;
        }
        printf("Error\n");
        t=getInt(&key);
    }
    printf("Enter the info,wich you want to insert\n");
    t= getInt(&info);
    while(t!=1){
        if(t==-1){
            return 0;
        }
        printf("Error\n");
        t=getInt(&info);
    }

    *root=insert(*root, key, info);

    return 1;
}
int D_Find(Node** root){
    if(*root==NULL){
        printf("Tree is empty\n");
        return 1;
    }
    printf("Enter the key,wich you want to find\n");
    int key, ver;
    int t= getInt(&key);
    while(t!=1){
        if(t==-1){
            return 0;
        }
        printf("Error\n");
        t=getInt(&key);
    }
    printf("Enter the version,wich you want to find\n");
    t= getInt(&ver);
    while(t!=1){
        if(t==-1){
            return 0;
        }
        printf("Error\n");
        t=getInt(&ver);
    }
    Node* terk=*root;
/*    terk=terk->right;
    printf("point =%d\n", terk->key);*/
 //   char* key=readline("Enter the key, wich you want to find\n");
    Node* temp=find(*root, key);
    if(temp==NULL){
        printf("Not found\n");
        return 1;
    }
    if(temp->size<=ver-1){
        printf("Not found this version\n");
        return 1;
    }
    printf("key=%d info=%d\n", temp->key, temp->data[ver-1]);
 //   printf("key= %s, info = %s", rc.key, rc.info);
    //free(key);
    return 1;
}
int D_Timing(Node**){
    Node *root=NULL;
    int n=10, key[10000], k, cnt=100000, i, m, info=3;
    clock_t first, last;
    srand(time(NULL));
    while(n-->0){
        for(i=0; i<10000; ++i)
            key[i]=rand()*rand();
        for(i=0; i<cnt;){
            k=rand()*rand();
            root=insert(root, k, info);
            ++i;
        }
        m=0;
        first=clock();
        for(i=0; i<10000; ++i)
        if(find(root,key[i]))
        ++m;
        last=clock();
//      printf("%d tm\n", last);
        printf("%d items was found\n", m);
        printf("test #%d, number of nodes = %d, time = %lf\n", 10-n, (10-n)*cnt, (double)(last-first)/CLOCKS_PER_SEC);
    }
        deleteTree(root);
        return 1;
    }
int D_Tidelete(Node**){
    Node *root=NULL;
    int n=10, key[10000], k, cnt=100000, i, m, info=3;
    clock_t first, last;
    srand(time(NULL));
    while(n-->0){
        for(i=0; i<10000; ++i)
            key[i]=rand()*rand();
        for(i=0; i<cnt;){
            k=rand()*rand();
            root=insert(root, k, info);
            ++i;
        }
        m=0;
        first=clock();
        for(i=0; i<10000; ++i)
        if(deleteel(&root,key[i],1)==0)
        ++m;
        for(i=0; i<m; i++){
                k=rand()*rand();
                root=insert(root,k,info);
        }
        last=clock();
//      printf("%d tm\n", last);
        printf("%d deleted was found\n", m);
        printf("test #%d, number of nodes = %d, time = %lf\n", 10-n, (10-n)*cnt, (double)(last-first)/CLOCKS_PER_SEC);
    }
        deleteTree(root);
        return 1;
    }
int D_TInsrt(Node**){
            Node *root=NULL;
    int n=10, key[10000], k, cnt=100000,ktm=100000, i, m, info=3;
    double temp=0;
    clock_t first, last;
    srand(time(NULL));
    while(n-->0){
        for(i=0; i<10000; ++i)
            key[i]=rand()*rand();
        first=clock();
        for(i=0; i<ktm;){
            k=rand()*rand();
            root=insert(root, k, info);
            ++i;
        }
        last=clock();
        deleteTree(root);
        root=NULL;
        ktm+=100000;
//      temp+=(double)(last-first)/CLOCKS_PER_SEC;
        m=0;
/*        first=clock();
        for(i=0; i<10000; ++i)
        if(find(root,key[i]))
        ++m;
        last=clock();*/
//      printf("%d tm\n", last);
//        printf("%d items was found\n", m);
        printf("test #%d, number of nodes = %d, time = %lf\n", 10-n, (10-n)*cnt, (double)(last-first)/CLOCKS_PER_SEC);
    }
      //  deleteTree(root);
        return 1;
    }
int D_Delete(Node** root){
    if(*root==NULL){
        printf("Tree is free\n");
        return 1;
    }
    printf("Enter the key, wich you whant to delete\n");
    int key;
    int t= getInt(&key);
    while(t!=1){
        if(t==-1){
            return 0;
        }
    printf("Error maxsize, try again\n");
        t=getInt(&key);
    }
    int ver;
    printf("Enter the version\n");
    t= getInt(&ver);
    while(t!=1){
        if(t==-1){
            return 0;
        }
        printf("Error\n");
        t=getInt(&ver);
    }
	if(ver==0){
		printf("Error in version\n");
		return 1;
	}
    int rc=deleteel(root, key, ver);
    printf("%s:  %d\n", errmsgs[rc], key);
    return 1;
}
static int (*fptr[])(Node**)={NULL, D_Add, D_Find, D_Delete, D_Show, D_Import, D_Indtask, D_Traversal, D_Timing, D_TInsrt, D_Tidelete};

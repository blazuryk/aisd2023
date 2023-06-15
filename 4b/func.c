#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<readline/readline.h>
#include<readline/history.h>
#include <unistd.h>
#include <sys/types.h>
#include"func.h"
static const char* msgs[]={"0.Quit", "1.Add", "2.Find", "3.Delete", "4.Show", "5.Import","6.Indtask", "7. Traversal", "8.TiIns", "9.Tidel", "10.Tisc"};
static const int Nmsgs=sizeof(msgs)/sizeof(msgs[0]);
static const char *errmsgs[]={"OK", "Duplicate key", "Table overflow", "Table empty", "Error in file", "Not found"};
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
void uphe(Node* node){
    int right=0;
    if(node->right!=NULL){
        right=node->right->h;
    }
    int left=0;

    if(node->left!=NULL){
        left=node->left->h;
    }

    if(right > left){
        node->h=right+1;

    }
    else{
        node->h=left+1;
    }
}
int bf(Node* node){
    int right=0;
    if(node->right!=NULL){
        right=node->right->h;
    }
    int left=0;

    if(node->left!=NULL){
        left=node->left->h;
    }
    return right-left;
}
Node* turnr(Node* node){
    Node* temp=node->left;
    node->left=temp->right;
    temp->right=node;
    uphe(node);
    uphe(temp);
    return temp;
}Node* turnl(Node* node){
    Node* temp=node->right;
    node->right=temp->left;
    temp->left=node;
    uphe(node);
    uphe(temp);
    return temp;
}
Node* balance(Node* node) 
{
	uphe(node);
	if( bf(node)==2 )
	{
		if( bf(node->right) < 0 ){
			node->right = turnr(node->right);
        }
		return turnl(node);
	}
	if( bf(node)==-2 )
	{
		if( bf(node->left) > 0  ){
			node->left = turnl(node->left);
        }
		return turnr(node);
	}
	return node;
}
Node* find(Node* root, char* key) {
    if ((root == NULL) || (strcmp(root->key,key)==0)) {
        return root;
    }
    if (strcmp(key,root->key)<0) {
        return find(root->left, key);
    } else {
        return find(root->right, key);
    }
}



Node *createNode(char *key, char *info) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->key = (char *)malloc((strlen(key) + 1) * sizeof(char));
    node->size=1; 
    node->data =malloc(sizeof(char*));
    node->data[0]=malloc((strlen(info)+1)*sizeof(char));
    strcpy(node->key, key);
    strcpy(node->data[0], info);
    node->h = 1;
    node->left = NULL;
    node->right = NULL;
    return node;
}
Node* minimum(Node* temp) {
    Node* prev;
    while (temp->left != NULL) {
        temp = temp->left;
    }
    return temp;
}
Node* delmin(Node* temp){
    if(temp->left==NULL){
        return temp->right;
    }
    temp->left=delmin(temp->left);
    return balance(temp);
}
Node* deleteel(Node* root, char* key, int ver){
    if(root==NULL){
        printf("Not found\n");
        return NULL;
    }

    else if(strcmp(key, root->key)<0){
        root->left=deleteel(root->left, key, ver);
    }
    else if(strcmp(key, root->key)>0){
        root->right=deleteel(root->right,key,ver);
    }
    else{
            if((root->size>1) || (ver<=0)){
                if(root->size < ver){
                    printf("Not found\n");
                    return root;
                }
                else{
                            free(root->data[ver-1]);
                            for (int i = ver-1; i < root->size - 1; i++) {
				root->data[i]=strdup(root->data[i+1]);
                                free(root->data[i+1]);
                            }
                            root->size--;
                            root->data=realloc(root->data, sizeof(char*)*root->size);
                            return root;
                    }
            }
	    else if((root->size==1) && (ver>1) && (ver!=0)){
			printf("Not this version\n");
			return root;
		}
            else{
                Node* right=root->right;
                Node* left=root->left;
		free(root->key);
                free(root->data[0]);
                free(root->data);
                free(root);
                if(right==NULL){
                    return left;
                }
                Node* temp=minimum(right);
                temp->right=delmin(right);
                temp->left=left;
                return balance(temp);
            }
    }
    return balance(root);
}
void deleteTree(Node *node) {
    if (node == NULL) {
        return;
    }
    deleteTree(node->left);
    deleteTree(node->right);
    for(int i=0; i<node->size; i++){
	free(node->data[i]);
}
    free(node->key);
    free(node->data);
    free(node);
}

Node* insert(Node* root, char* key, char* info){
    if(root==NULL){
        return createNode(key, info);
    }

    else if(strcmp(key, root->key)<0){
        root->left=insert(root->left, key, info);
    }
    else if(strcmp(key, root->key)>0){
        root->right=insert(root->right,key,info);
    }
    else{
        root->data=realloc(root->data, (root->size+1)*sizeof(char*));
        root->data[root->size]=malloc((strlen(info)+1)*sizeof(char));
        strcpy(root->data[root->size], info);
        root->size++;
    }
    return balance(root);


}
void printTree(Node* root, int lvl) {
    if (root == NULL) {
        return;
    }

    printTree(root->right, lvl + 1);

    for (int i = 0; i < lvl; i++) {
        printf("  ");
    }
    printf("%s", root->key);
    if (root->size > 1) {
        printf(" (x%d)", root->size);
    }
    printf("\n");

    printTree(root->left, lvl + 1);
}
void print_reversed(Node* node, char* max_key) {
    if (node == NULL) {
        return;
    }
    if (node->key > max_key) {
        print_reversed(node->left, max_key);
    } else {
        print_reversed(node->right, max_key);
        if (node->key <= max_key) {
            printf("%s ", node->key);
        }
        print_reversed(node->left, max_key);
    }
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

    
        char* key;
        key=readline("Enter the maxkey\n");
        if(key==NULL){
            return 0;
        }
 //   int info;
 /*   int t= getInt(&key);
    printf("Enter the maxkey\n");
    while(t!=1){
        if(t==-1){
            return 0;
        }
        printf("Error\n");
        t=getInt(&key);
    }
    */
    print_reversed(*root, key);
    free(key);
    return 1;
}
Node* findClosest(Node* root, char* val) {
    Node* closest = NULL;
    Node* cur = root;
    while (cur != NULL) {
        if(((strcmp(cur->key, val)<=0) && (closest==NULL)) || ((strcmp(cur->key, val)<=0) && (strcmp(cur->key,closest->key)>0))){
                closest=cur;
        }
        if (strcmp(cur->key,val)<0) {
            cur = cur->right;
        } else {
            cur = cur->left;
        }
    }

    return closest;
}
int D_Indtask(Node** root){
    if(*root==NULL){
        printf("Tree is empty\n");
        return 1;
    }

    
    char* key;
    key=readline("Enter the key, which you whant to find\n");
    if(key==NULL){
        return 0;
    }
/*        int key;
 //   int info;
    int t= getInt(&key);
    printf("Enter the key, which you whant to find\n");
    while(t!=1){
        if(t==-1){
            return 0;
        }
        printf("Error\n");
        t=getInt(&key);
    }*/
    Node* temp=findClosest(*root, key);
    if(temp==NULL){
        printf("Not found\n");
	free(key);
        return 1;
    }
    printTree(temp, 0);
    free(key);
    return 1;
}
int D_Add(Node** root){
    int rc, ver, p;
//    int key;
    char* info;
    char* key;
    key=readline("Enter the key, which you whant to add\n");
    if(key==NULL){
        return 0;
    }
    info=readline("Enter the info,wich you want to insert\n");
    if(info==NULL){
        free(key);
        return 0;
    }
    *root=insert(*root, key, info);
    free(key);
    free(info);
    return 1;
}


int D_Find(Node** root){
    if(*root==NULL){
        printf("Tree is empty\n");
        return 1;
    }
    char* key=readline("Enter the key, which you whant to find\n");
    if(key==NULL){
        return 0;
    }
    int ver;
    printf("Enter the version,wich you want to find\n");
    int t= getInt(&ver);
    while(t!=1){
        if(t==-1){
            return 0;
        }
        printf("Error\n");
        t=getInt(&ver);
    }
 //   Node* terk=*root;
/*    terk=terk->right;
    printf("point =%d\n", terk->key);*/
 //   char* key=readline("Enter the key, wich you want to find\n");
    Node* temp=find(*root, key);
    if(temp==NULL){
        printf("Not found\n");
        return 1;
    }
    if(temp->size<ver){
        printf("Not found this version\n");
        return 1;
    }
    printf("key=%s info=%s\n", temp->key, temp->data[ver-1]);
 //   printf("key= %s, info = %s", rc.key, rc.info);
    free(key);
    return 1;
}

int D_Delete(Node** root){
    if(*root==NULL){
        printf("Tree is free\n");
        return 1;
    }
    char*   key=readline("Enter the key, which you whant to delete\n");
    if(key==NULL){
        return 0;
    }
    int ver;
    printf("Enter the version\n");
    int t= getInt(&ver);
    while(t!=1){
        if(t==-1){
            return 0;
        }
        printf("Error\n");
        t=getInt(&ver);
    }
    if(ver==0){
    free(key);
	printf("Error in version\n");
	return 1;
   }
    *root=deleteel(*root, key, ver);
 //   printf("%s:  %d\n", errmsgs[rc], key);
    free(key);
    return 1;
}
int impttb(Node** table, char* name){
        FILE *file;
        char str1[80];
        int records=0;
        char str2[80];
	char* key;
	char* info;
        int rc;
        int k=0;
        file=fopen(name, "r");
        free(name);
        if(file==NULL){
                return 4;
        }
        int read=0;
        while(read=fscanf(file, "%80[^\n]%*c%80[^\n]%*c", str1,str2)!=EOF){
                if(read!=1 && feof(file)){
                        return 4;
                }
        key=strdup(str1);
        info=strdup(str2);
        printf("key = %s, info= %s\n", key, info);
        *table=insert(*table, key, info);
        free(key);
        free(info);
   //    free(key);
    //    free(info);
        k++;
//        printf("%s:  %d\n", errmsgs[rc], k);
        printf("OK:  %d\n", k);
 /*       if(rc==2){
            return 0;
            break;
        }*/
        if(read==1) records++;
        }while(!feof(file));
         fclose(file);
        return 0;
}
char *rd(int len) {
    char alf[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char *rdstr = NULL;
    rdstr = malloc(sizeof(char) * (len +1));
        if (rdstr) {
            for (int n = 0; n < len; n++) {
                int key = rand() % (int)(sizeof(alf) -1);
                rdstr[n] = alf[key];
            }

            rdstr[len] = '\0';
        }

    return rdstr;
}
int D_Timing(Node**){
    Node *root=NULL;
         char* k;
//      char* key=malloc(10000*sizeof(char*));
        char* info=rd(rand()%30);
    int n=10, cnt=1000, i, m;
    clock_t first, last;
    char* tk;
    srand(time(NULL));
    while(n-->0){
 /*       for(i=0; i<10000; ++i)
            key[i]=rand()*rand();*/
        for(i=0; i<cnt;){
            k=rd(rand()%30);
            root=insert(root, k, info);
            ++i;
            free(k);
        }
        m=0;
        first=clock();
       for(i=0; i<1000; ++i){
	tk=rd(rand()%30);
        if(find(root,tk))
        ++m;
	free(tk);
	}
        last=clock();
//      printf("%d tm\n", last);
        printf("%d items was found\n", m);
        printf("test #%d, number of nodes = %d, time = %lf\n", 10-n, (10-n)*cnt, (double)(last-first)/CLOCKS_PER_SEC);
    }
	free(info);
        deleteTree(root);
        return 1;
    }
int D_Tidelete(Node**){
    Node *root=NULL;
         char* k;
//      char* key=malloc(10000*sizeof(char*));
        char* info=rd(rand()%30);
    int n=10, cnt=1000, i, m;
    clock_t first, last;
    char* tk;
    srand(time(NULL));
    while(n-->0){
 /*       for(i=0; i<10000; ++i)
            key[i]=rand()*rand();*/
        for(i=0; i<cnt;){
            k=rd(rand()%30);
            root=insert(root, k, info);
            ++i;
	    free(k);
        }
        m=0;
        first=clock();
        for(i=0; i<1000; ++i){
	tk=rd(rand()%30);
        if(deleteel(root,tk,1)==0)
        	++m;
	free(tk);
	}
        for(i=0; i<m; i++){
                k=rd(rand()%30);
                root=insert(root,k,info);
		free(k);
        }
        last=clock();
//      printf("%d tm\n", last);
        printf("%d deleted was found\n", m);
        printf("test #%d, number of nodes = %d, time = %lf\n", 10-n, (10-n)*cnt, (double)(last-first)/CLOCKS_PER_SEC);
    }
        deleteTree(root);
	free(info);
        return 1;
    }
int D_TInsrt(Node**){
            Node *root=NULL;
	char* k;
//	char* key=malloc(10000*sizeof(char*));
	char* info=rd(rand()%30);
    int n=10, cnt=1000,ktm=1000, i, m;
    double temp=0;
    clock_t first, last;
    srand(time(NULL));
    while(n-->0){
  //     for(i=0; i<10000; ++i)
   //        key[i]=rd(rand()%30);
        first=clock();
        for(i=0; i<ktm;){
            k=rd(rand()%30);
            root=insert(root, k, info);
            ++i;
	    free(k);
        }
        last=clock();
        deleteTree(root);
        root=NULL;
        ktm+=1000;
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
	free(info);
      //  deleteTree(root);
        return 1;
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

static int (*fptr[])(Node**)={NULL, D_Add, D_Find, D_Delete, D_Show, D_Import, D_Indtask, D_Traversal, D_TInsrt, D_Tidelete,D_Timing};

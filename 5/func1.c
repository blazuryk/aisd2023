#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<readline/readline.h>
#include<readline/history.h>
#include <stdbool.h>
#include <limits.h>
#include <unistd.h>
#include <sys/types.h>
#include"func.h"
#define MV 500
static const char* msgs[]={"0.Quit", "1.Add_Room", "2.Add_Corridor", "3.Delete Room", "4.Delete_Corrodor", "5.Show","6.TranslatorInWidth", "7. DistanceBetween", "8.ChangeVer", "9.Closset"};
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
Maze* initializeMaze(Maze* temp);
void addRoom(Maze* maze, char* id, int type);
void BFS(Maze* maze,char* startVertex1);
void changeVer(Maze* maze, char* room);
void addCorridor(Maze* maze, const char* id1, const char* id2, int length);
void removeRoom(Maze* maze, Room* roomToRemove);
void findtodel(Maze* maze, char* id);
void removeRoom(Maze* maze, Room* roomToRemove);
void removeCorridor(Maze* maze, char* id1, char* id2);
void bellmanFord(Maze* maze, char* start1, char* end1);
void FloydWarshall(Maze* maze,char* sourceVertex1);

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
int D_TranslatorInWidth(Maze* maze){
    if(maze->head==NULL){
        printf("Maze is empty\n");
        return 1;
    }


    char* name;
    name=readline("Enter the start of find\n");
    if(name==NULL){
        return 0;
    }
    BFS(maze, name);
    free(name);
    return 1;
}
int D_Addroom(Maze* maze){
    int rc, ver, p;
//    int key;
    int type;
    char* name=readline("Enter the name of room, which you whant to add\n");
    if(name==NULL){
        return 0;
    }
    printf("Enter the type of room\n");
    int t= getInt(&type);
    while(t!=1 || (type>=3)){
        if(t==-1){
            return 0;
        }
        printf("Error\n");
        t=getInt(&type);
    }
    addRoom(maze, name, type);
    free(name);
    return 1;
}
int D_DistanceBetween(Maze* maze){
    if(maze->head==NULL){
        printf("Maze if empty\n");
        return 1;
    }
    char* name1=readline("Enter the name1 of room, which you whant to corr\n");
    if(name1==NULL){
        return 0;
    }
    char* name2=readline("Enter the name2 of room, which you whant to corr\n");
    if(name2==NULL){
        free(name1);
        return 0;
    }
    bellmanFord(maze, name1, name2);
    free(name1);
    free(name2);
    return 1;
}
int D_ChangeVer(Maze* maze){
    char* name=readline("Enter the name of room, which you whant to change\n");
    if(name==NULL){
        return 0;
    }
    changeVer(maze, name);
    free(name);
    return 1;


}
int D_Closset(Maze* maze){
    if(maze->head==NULL){
        printf("Maze if empty\n");
        return 1;
    }
    char* name1=readline("Enter the name1 of room, which you whant to corr\n");
    if(name1==NULL){
        return 0;
    }
    FloydWarshall(maze, name1);
    free(name1);
    return 1;
}
int D_Addcorr(Maze* maze){
    int rc, ver, p;
//    int key;
    int length;
    char* name1=readline("Enter the name1 of room, which you whant to corr\n");
    if(name1==NULL){
        return 0;
    }
    char* name2=readline("Enter the name2 of room, which you whant to corr\n");
    if(name2==NULL){
        free(name1);
        return 0;
    }
    
    printf("Enter the length of room\n");
    int t= getInt(&length);
    while(t!=1){
        if(t==-1){
            return 0;
        }
        printf("Error\n");
        t=getInt(&length);
    }
 //   addRoom(maze, name1, name2, length);
    addCorridor(maze, name1, name2, length); 
    free(name1);
    free(name2);
    return 1;
}
int D_Delete_Room(Maze* maze){
    if(maze->head==NULL){
        printf("Maze if empty\n");
        return 1;
    }
    char* name=readline("Enter the name of room, which you whant to delete\n");
    if(name==NULL){
        return 0;
    }
    findtodel(maze, name);
 //   printf("key=%s info=%s\n", temp->key, temp->data[ver-1]);
 //   printf("key= %s, info = %s", rc.key, rc.info);
    free(name);
    return 1;
}

int D_Delete_Corrodor(Maze* maze){
   if(maze->head==NULL){
        printf("Maze if empty\n");
        return 1;
    }
    char* name1=readline("Enter the 1 room\n");
    if(name1==NULL){
        return 0;
    }
    char* name2=readline("Enter the 2 room\n");
    if(name2==NULL){
        free(name1);
        return 0;
    } 
    removeCorridor(maze, name1, name2);
    free(name1);
    free(name2);
    return 1;
}
void printMaze(Room* room){
        while (room != NULL) {
        printf("Room ID: %s, Type: %d\n", room->id, room->type);
        room = room->next;
    }
}
int D_Show(Maze * maze){
	    int i, j;
    int n=maze->numRooms;
    Room* temp=maze->head;
    if(temp==NULL){
		printf("Maze is empty\n");
		return 1;
	}
    // Вывод обозначений вершин
    printf("  ");
    for (i = 0; i < n; i++) {
        printf("\t%s", temp->id);
	temp=temp->next;
    }
    printf("\n");
    temp=maze->head;
    for (i = 0; i < n; i++) {
        // Вывод обозначения текущей вершины
        printf("%s\t ", temp->id);
        for (j = 0; j < n; j++) {
            int length = maze->corridors[i][j].length;
	    if(length!=-1){
            	printf("\t%d\t ", length);
	    }
/*	    else{
		printf("\t-\t ");
		}*/
	    else if(i==j){
			printf("\t0\t ");
		}
	    else{
			printf("\t-\t ");
		}
        }
	temp=temp->next;
        printf("\n");
    }
}


static int (*fptr[])(Maze*)={NULL, D_Addroom, D_Addcorr, D_Delete_Room, D_Delete_Corrodor, D_Show, D_TranslatorInWidth, D_DistanceBetween, D_ChangeVer, D_Closset};
Maze* initializeMaze(Maze* temp) {
    Maze* maze=(Maze*)malloc(sizeof(Maze));
    maze->numRooms=0;
    maze->head=NULL;
    maze->corridors=NULL;
    return maze;
}
void addRoom(Maze* maze, char* id, int type) {
    Room* temp=maze->head;
    while(temp!=NULL){
	if(strcmp(temp->id, id)==0){
		printf("Dublicate\n");
		return;
		break;
	}
	temp=temp->next;
    }
    Room* room=malloc(sizeof(Room));
    room->id=strdup(id);
 //   strcpy(room->id, id);
    room->type = type;
    room->next=NULL;
   if(maze->head==NULL){
        maze->head=NULL;
        maze->head=room;
        maze->numRooms++;
        maze->corridors=malloc(sizeof(Corridor*));
        maze->corridors[0]=malloc(sizeof(Corridor));
        maze->corridors[0][0].length=-1;
        return;
    }
//     printf("JUJA\n");
    temp =maze->head;
    while(temp->next!=NULL){
        if(strcmp(temp->id, id)==0){
            free(room->id);
//            free(id);
            return;
        }
        temp=temp->next;

    }
    temp->next=room;
    maze->numRooms++;
    maze->corridors=realloc(maze->corridors, maze->numRooms*sizeof(Corridor*));
    maze->corridors[maze->numRooms-1]=calloc(maze->numRooms,sizeof(Corridor));
    for(int j=0; j<maze->numRooms-1; j++){
        maze->corridors[j]=realloc(maze->corridors[j], maze->numRooms*sizeof(Corridor));
    }
    for(int i=0; i<maze->numRooms; i++){
        maze->corridors[maze->numRooms-1][i].length=-1;
        maze->corridors[i][maze->numRooms-1].length=-1;
    }
    return;
}
typedef struct {
    int* queue;
    int fr;
    int size;
} Queue;
void initializeQueue(Queue* q, int n) {
    q->fr = -1;
    q->size = -1;
    q->queue=malloc(n*sizeof(int));
}
void enqueue(Queue* q, int vr) {
    if (q->size == MV - 1) {
        printf("Ошибка: очередь переполнена\n");
        return;
    }
    if (q->fr == -1) {
        q->fr = 0;
    }
    q->size++;
    q->queue[q->size] = vr;
}
int dequeue(Queue* q) {
    if (q->fr == -1 || q->fr > q->size) {
        printf("Ошибка: очередь пуста\n");
        return -1;
    }
    int vr = q->queue[q->fr];
    q->fr++;
    return vr;
}
bool isQueueEmpty(Queue* q) {
    return (q->fr == -1 || q->fr > q->size);
}
void prvd(int* dist, int* par, bool* visited, Room* head, int nV){
    Room* temp=head;
    printf("Вершина\t\tРасстояние\t\tТип вершины\n");
    for (int i = 0; i < nV; i++) {

        if(dist[i]<INT_MAX){
            printf("%s\t\t%d\t\t\t%d", temp->id, dist[i], temp->type);
        }
        else{
            printf("%s\t\t-\t\t\t%d",temp->id, temp->type);
        }
        printf("\n");
        temp=temp->next;
    }


}
void BFS(Maze* maze,char* startVertex1) {
    int nV=maze->numRooms;
    Corridor** graph=maze->corridors;
    Room* temp=maze->head;
    int k=0;
    while(temp!=NULL){
        if(strcmp(temp->id, startVertex1)==0){
                break;
        }
        k++;
        temp=temp->next;
    }
    if(temp==NULL){
	printf("Not found\n");
        return;
    }
    int startVertex=k;
    bool* visited=malloc(maze->numRooms*sizeof(bool));
    int* dist=malloc(maze->numRooms*sizeof(int));
    int* par=malloc(maze->numRooms*sizeof(int));
    for (int i = 0; i < nV; i++) {
        visited[i] = false;
        dist[i] = INT_MAX;
        par[i] = -1;
    }

    Queue q;
    initializeQueue(&q, maze->numRooms);
    visited[startVertex] = true;
    dist[startVertex] = 0;
    enqueue(&q, startVertex);
    while (!isQueueEmpty(&q)) {
        int currentVertex = dequeue(&q);
        for (int i = 0; i < nV; i++) {
            if (graph[currentVertex][i].length != -1 && !visited[i]) {
                visited[i] = true;
                dist[i] = dist[currentVertex] + graph[currentVertex][i].length;
                par[i] = currentVertex;
                enqueue(&q, i);
            }
        }
    }
    temp=maze->head;
    prvd(dist, par, visited, maze->head, nV);
     free(q.queue);
     free(par);
     free(dist);
     free(visited);
     return;
}
void changeVer(Maze* maze, char* room){
        Room* temp=maze->head;
        while(temp!=NULL){
             if(strcmp(room, temp->id)==0){
                        break;
                }
             temp=temp->next;
        }
        if(temp!=NULL){
//                printf("Write new name\n");
		char* name=readline("Write new name\n");
		if(name==NULL){
			return;
		}
		free(temp->id);
		temp->id=strdup(name);
		free(name);
		return;
        }
        else{
                printf("Not found\n");
        }
        return;
}
void addCorridor(Maze* maze, const char* id1, const char* id2, int length) {
    int index1 = -1, index2 = -1;
    if(maze->head==NULL){
	printf("Maze is empty\n");
        return;
    }
    if(strcmp(id1, id2)==0){
		printf("Error\n");
		return;
	}
    Room* temp=maze->head;
    for (int i = 0; i < maze->numRooms; i++) {
        if (strcmp(temp->id, id1) == 0) {
            index1 = i;
            if (index2 != -1)
                break;
        }
        if (strcmp(temp->id, id2) == 0) {
            index2 = i;
            if (index1 != -1)
                break;
        }
        temp=temp->next;
    }

    if (index1 == -1 || index2 == -1) {
        printf("Error: Room(s) not found.\n");
        return;
    }

    maze->corridors[index1][index2].length = length;
}
void removeRoom(Maze* maze, Room* roomToRemove);
void findtodel(Maze* maze, char* id){
    Room* temp=maze->head;
    while(temp!=NULL){
        if(strcmp(temp->id, id)==0){
            removeRoom(maze,temp);
            return;
        }
        temp=temp->next;
    }
    printf("Not found\n");
    return;

}
void removeRoom(Maze* maze, Room* roomToRemove) {
    if (maze == NULL || roomToRemove == NULL) {
        return;
    }
    Room* currRoom = maze->head;
    Room* prevRoom = NULL;
    int k=0;
    while (currRoom != NULL) {
        if (currRoom == roomToRemove) {
            if (prevRoom == NULL) {
                maze->head = currRoom->next;
            } else {
                prevRoom->next = currRoom->next;
            }
            if(maze->head==NULL){
                free(maze->corridors[0]);
                free(maze->corridors);
            }
            else{
            for(int i=0; i<maze->numRooms; i++){
               for(int j=k; j<maze->numRooms-1; j++){
                   maze->corridors[i][j]=maze->corridors[i][j+1];
                }
                printf("check1\n");
                maze->corridors[i]=realloc(maze->corridors[i], (maze->numRooms-1)*sizeof(Corridor));
            }
            free(maze->corridors[k]);
            for(int i=k; i<maze->numRooms-1; i++){
                maze->corridors[i]=maze->corridors[i+1];
            }
                maze->corridors=realloc(maze->corridors, (maze->numRooms-1)*sizeof(Corridor*));
            }
            free(currRoom->id);
            free(currRoom);
            maze->numRooms--;
            return;
        }

        k++;
        prevRoom = currRoom;
        currRoom = currRoom->next;
    }
    return ;
}
void removeCorridor(Maze* maze, char* id1, char* id2){
    int index1 = -1, index2 = -1;
    if(maze->head==NULL){
        return;
    }
    Room* temp=maze->head;
    for (int i = 0; i < maze->numRooms; i++) {
        if (strcmp(temp->id, id1) == 0) {
            index1 = i;
            if (index2 != -1)
                break;
        }
        if (strcmp(temp->id, id2) == 0) {
            index2 = i;
            if (index1 != -1)
                break;
        }
        temp=temp->next;
    }

    if (index1 == -1 || index2 == -1) {
        printf("Error: Room(s) not found.\n");
        return;
    }

    maze->corridors[index1][index2].length = -1;
}
void bellmanFord(Maze* maze, char* start1, char* end1) {
    int* dist=malloc(maze->numRooms*sizeof(int));
    int nV=maze->numRooms;
    Room* temp=maze->head;
    int k=0;
    while(temp!=NULL){
        if((strcmp(start1,temp->id)==0)){
                break;
        }
        k++;
        temp=temp->next;
    }
    if(temp==NULL){
                printf("Not found this room\n");
		free(dist);
                return;
        }
    temp=maze->head;
    int start=k;
    k=0;
    while(temp!=NULL){
        if(strcmp(end1,temp->id)==0){
                break;
        }
        k++;
        temp=temp->next;

    }
    if(temp==NULL){
                printf("Not found this room\n");
		free(dist);
                return;
        }
    int end=k;
        printf("start %d, end %d\n", start, end);
    for (int i = 0; i < nV; ++i) {
        dist[i] = INT_MAX;
    }
    dist[start] = 0;
    for (int k = 0; k < nV - 1; ++k) {
        for (int i = 0; i < nV; ++i) {
            for (int j = 0; j < nV; ++j) {
                if (maze->corridors[i][j].length != -1 && dist[i] != INT_MAX && dist[i] + maze->corridors[i][j].length < dist[j]) {
                    dist[j] = dist[i] + maze->corridors[i][j].length;
                }
            }
        }
    }
    for (int i = 0; i < nV; ++i) {
        for (int j = 0; j < nV; ++j) {
            if (maze->corridors[i][j].length != -1 && dist[i] != INT_MAX && dist[i] + maze->corridors[i][j].length < dist[j]) {
                free(dist);
		return;
            }
        }
    }
    if(dist[end]!=INT_MAX){
                printf("Distance %d\n", dist[end]);
		free(dist);
                return;
        }
    else{
                printf("Error not found \n");
		free(dist);
                return;
        }
	free(dist);
        return;
}
void frpr(Room* head, int sourceVertex, int** dist, char* sourceVertex1, int nV){
    Room* temp=head;
    printf("Расстояния от вершины %s:\n", sourceVertex1);
    for (int i = 0; i < nV; i++) {
        if (i != sourceVertex) {
            printf("От вершины %s до вершины %s тип %d: ", sourceVertex1, temp->id, temp->type);
            if (dist[sourceVertex][i] == INT_MAX) {
                printf("нет пути\n");
            } else {
                printf("%d\n", dist[sourceVertex][i]);
            }
        }
        temp=temp->next;
    }

}
void FloydWarshall(Maze* maze,char* sourceVertex1) {
     int nV=maze->numRooms;
    Corridor** graph=maze->corridors;
    Room* temp=maze->head;
    int k=0;
    while(temp!=NULL){
        if(strcmp(temp->id, sourceVertex1)==0){
                break;
        }
        k++;
        temp=temp->next;
    }
    if(temp==NULL){
        return;
    }
    int** dist;
    dist=malloc(maze->numRooms*sizeof(int*));
     for (int i=0; i<maze->numRooms; i++){
                dist[i]=malloc(maze->numRooms*sizeof(int));
        }

    int sourceVertex=k;
    for (int i = 0; i < nV; i++) {
        for (int j = 0; j < nV; j++) {
            if (graph[i][j].length != -1) {
                dist[i][j] = graph[i][j].length;
            } else {
                dist[i][j] = INT_MAX;
            }
        }
    }
    for (int k = 0; k < nV; k++) {
        for (int i = 0; i < nV; i++) {
            for (int j = 0; j < nV; j++) {
                if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX &&
                    dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
    temp=maze->head;
    frpr(temp, sourceVertex, dist, sourceVertex1, nV);
    for(int i=0; i<maze->numRooms; i++){
		free(dist[i]);
	}
    free(dist);
}
void deletemaze(Maze* maze){
    Room* temp=maze->head;
    Room* next;
    for(int i=0; i<maze->numRooms; i++){
        next=temp->next;
        free(temp->id);
        free(temp);
        temp=next;
    }
    for(int i=0; i<maze->numRooms; i++){
        free(maze->corridors[i]);
    }
     if(maze->head!=NULL){
    free(maze->corridors);
	}
    free(maze);
}

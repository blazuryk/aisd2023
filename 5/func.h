#ifndef FOO_H_
#define FOO_H_
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<readline/readline.h>
#include<readline/history.h>
#include <stdbool.h>
#include <limits.h>
#include <unistd.h>
#include <sys/types.h>
typedef struct Room{
    char* id;
    int type;
    struct Room * next;
} Room;

typedef struct {
    int length;
} Corridor;

typedef struct {
    Room* head;
    Corridor** corridors;
    int numRooms;
} Maze;
int getInt(int* b);
Maze* initializeMaze(Maze* temp);
void addRoom(Maze* maze, char* id, int type);
void BFS(Maze* maze,char* startVertex1);
void changeVer(Maze* maze, char* room);
void addCorridor(Maze* maze, const char* id1, const char* id2, int length);
void removeRoom(Maze* maze, Room* roomToRemove);
void findtodel(Maze* maze, char* id);
void removeCorridor(Maze* maze, char* id1, char* id2);
void bellmanFord(Maze* maze, char* start1, char* end1);
void FloydWarshall(Maze* maze,char* sourceVertex1);
int dialog(const char * msgs[], int N);
int D_TranslatorInWidth(Maze* maze);
int D_Addroom(Maze* maze);
int D_DistanceBetween(Maze* maze);
int D_ChangeVer(Maze* maze);
int D_Closset(Maze* maze);
int D_Addcorr(Maze* maze);
int D_Delete_Room(Maze* maze);
int D_Delete_Corrodor(Maze* maze);
void printMaze(Room* room);
int D_Show(Maze * maze);
void deletemaze(Maze* maze);
#endif

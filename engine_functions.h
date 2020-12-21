#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>

/////////////////////////////Alias///////////////////////////////////////////////////
// create 2 arrays to store alias' names and alias's commands

////////////////////////////////////////////////////////////////////////////////////
void parseLine(char *line, char *arr[]);
int execute(char *const args[]);
void exit1();
void signalHandler(int sig);
void addHistory(char historyArray[10][512], char history[], int counter);
void printHistory(int historySize, char historyArray[10][512]);
void findHistory(int number, char historyArray[10][512]);
void deleteHistory(char historyArray[10][512],int historySize);
void executeHistory(char historyArray[10][512], int historyNumber);
char *getAlias(char *ext);





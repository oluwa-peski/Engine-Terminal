#include "engine_functions.h"


//function for parsing user input commands
void parseLine(char *line, char *arr[])
{
    char *a;
    int i = 0;

    a = strtok(line, " ");
    // if user input command is not null, walk it through
    while (a != NULL)
    {
        arr[i] = a;

        a = strtok(NULL, " ");
        i++;
    }
    for (int j = i; j < 100; j++)
        arr[j] = NULL;
}

//function for user input command execution
int execute(char *const args[])
{
	int i;
	int status;
	pid_t wpid;
	pid_t pid = fork();
	
	if (pid < 0){
		printf("Fork failed\n");
	}

	if (pid == 0){
		if (execvp(args[0], args) == -1){
	//perror("lsh");
	}
		exit(1);
	}
	else if (pid > 0){

	do{
	
	wpid = waitpid(pid,&status,WUNTRACED);
	}while(!WIFEXITED(status) && !WIFSIGNALED(status));

}
	    
	return pid;	
    
}

/*Femi's portion*/

/*function to call if is in user input. Shell is quit when function is executed*/

void exit1(){
	exit(0);
}


void signalHandler(int sig){
	printf("major1> ");

	signal(SIGTSTP, signalHandler);

	signal(SIGINT, signalHandler);
	
}

//function to copy user input commands into history array
void addHistory(char historyArray[10][512], char history[], int counter){
	strcat(historyArray[counter]," ");
	strcat(historyArray[counter],history);
	counter++;
}

//function for history command, prints history array
void printHistory(int historySize, char historyArray[10][512]){

	int i = 0;

	for (i=0;i<historySize; i++){
		if (*historyArray[i] != '\0'){	
			printf("\n%s\n",historyArray[i]);
		}
	}
	
}	

//function for history N command, finds specific command in the history array
void findHistory(int number, char historyArray[10][512]){

	if(historyArray[number] != NULL) {
		printf("\n%s\n", historyArray[number]);
	}
	else{
		printf("Out of index\n");
	}
}

//function for history -c command, clears history array
void deleteHistory(char historyArray[10][512],int historySize){
	int i;
	int j;
	size_t command_size;
	for (i = 0; i<historySize; i++){
		command_size = sizeof(historyArray[i])/sizeof(historyArray[i][0]);
		for(j=0; j<command_size;j++){
			historyArray[i][j] = '\0';
		}

	}
	printf("\nHistory cleared\n");
}
		
//function for history N -e command, finds specific command in the history array and executes it	
void executeHistory(char historyArray[10][512], int historyNumber){
	
	char *arr[512];
 	char *a;
	int i = 0;

    	a = strtok(historyArray[historyNumber], " ");
    	// if user input command is not null, walk it through
    	while (a != NULL)
    	{
        	arr[i] = a;
		 a = strtok(NULL, " ");
        	i++;
    	}
   	 	for (int j = i; j < 100; j++)
        	arr[j] = NULL;
		execute(arr);
}


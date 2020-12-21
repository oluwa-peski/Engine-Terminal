static const int MAX_ARGC = 512;
#include "engine_functions.h"
char  *alias_name[5];
char *alias_command[5];

// create an array to store extracted words from a string
char *ext_wo_arr[5];

////////////////////////////////////////Alias Function//////////////////////////////////////////
char *getAlias(char *ext)
{
    if(strcmp(ext_wo_arr[0], "alias") == 0)
    {
        if(strcmp(ext_wo_arr[1], "-r") == 0)            // check if the argument match -r flag
        {
            //printf("it did come to -r\n");              // test if program goes here

            //scan alias to remove an element
            int i;
            for(i = 0; i < 5; i++)
            {
                //printf("it did come to for loop\n");
                if(strcmp(alias_name[i], ext_wo_arr[2]) == 0)
                {
                    //printf("it did come to comparing\n");
                    //remove that entry from alias array
                    alias_name[i] = '\0';
                    alias_command[i] = '\0';
                    break;
                }
            }
        }
        else if(strcmp(ext_wo_arr[1], "-c") == 0)       // check if the argument match -c flag
        {
            //printf("it did come to -c\n");
            //clear entire alias  name
            int i;
            for(i = 0; i < 20; i++)
            {
                alias_name[i] = '\0';
                alias_command[i] = '\0';
            }
        }
        else 
        {
            //printf("it did come to last else\n");       // test if program goes here

            int i;
            for(i = 0; i < 5; i++)
            {
                if((alias_name[i] == NULL) && (alias_command[i] == NULL))
                {
                    alias_name[i] = ext_wo_arr[1];
                    alias_command[i] = ext_wo_arr[2];
                    break;
                }
                    
            }
        }
		
    }
}


/**Group Portion **/
int main(int argc, char *argv[])
{
	//variable and array declarations
	int historySize = 0; //save the number of commands
	int i = 0;//random counter
	char *cmd = (char *)malloc(sizeof(char));
	char *a;
	char historyArray[10][512]; //2d array to store list of commands
	char *arr[512];
	FILE *batchFile;
	char *line; //save the command being parsed to line

	char *shell_argv[MAX_ARGC + 1];
	int shell_argc;

	size_t len = 512;

	signal(SIGTSTP, signalHandler);//signal handler for ctrl z
	signal(SIGINT, signalHandler); //signal handler for ctrl c


    //batch mode

    //check if the when the output file is executed, an argument is passed along with it.
	if (argc == 2){
		char temp[512];
		int number = 0;
		
		//open user input file
		batchFile = fopen(argv[1], "r");
		
		//if user input file cannot be found, prompt alert message and exit
		if (batchFile == NULL){

			printf("Unable to open batch file, are you sure it exists? Try again.\n");
		
			exit(1);
		}
			
		//while file is not the end of file
		while (!feof(batchFile))
		{
			//get lines from the user input file
			getline(&line, &len, batchFile);

			////////////////////////////////////////////////alias//////////////////////////////////////////////////
            // split words from a string using parseLine function
            // parseLine(line, ext_wo_arr);
            // getAlias(*ext_wo_arr);
			/////////////////////////////////////////////////////////////////////////////////////////////////////////
			
			//parse lines and store them into shell_argv array
			for (shell_argc = 0; shell_argc <= 512; shell_argc++){
				while (*line == ' ' || *line == '\t')
					++line;
				if (*line == '\n' || *line == '\0')
					break;
				shell_argv[shell_argc] = line;

				while (*line != ' ' && *line != '\t' && *line != '\n' && *line != '\0')
				{
					++line;
				}
				if (*line != '\0')
					*(line++) = '\0';
			}
			
			//if user input file has "exit", end the program
			if (strcmp(shell_argv[shell_argc-1],"exit") == 0){
				exit1();
			}		


			//save commands in new array so we can display commands when they are executed 
			for (i=0; i<shell_argc; i++){
				strcat(temp," ");
				strcat(temp, shell_argv[i]);
			}
			
			shell_argv[shell_argc]=NULL;
			

			//Add history consecutively
			addHistory(historyArray, temp, historySize);

			//increment counter for future reference
			historySize++;
			printf("\n[engine]$: Command is - %s\n",temp);
			
			//if first argument of parsed user input line is history, go into this if statement
			if (strcmp(shell_argv[0], "history")==0)
			{
				//if second argument is null, print history array using printHistory function
				if(shell_argv[1] == NULL)
				{
					printHistory(historySize, historyArray);
				}
				//if second argument is "-c", clear history array using deleteHistory function
				else if (strcmp(shell_argv[1],"-c")==0)
				{
					deleteHistory(historyArray, historySize);
					historySize = 0;
				}
				//if second argument is number, find the element in history array that is stored in
				//the index of that user input number using findHistory function
				else if (isdigit(*shell_argv[1]) != 0)
				{
					if(shell_argv[2] == NULL)
					{
						int numnum;
						numnum = atoi(shell_argv[1]);
						findHistory(numnum, historyArray);
					}
					//if second argument is number and third argument is "-e", execute that command in
					//history array using executeHistory function
					else if(strcmp(shell_argv[2], "-e") == 0)
					{
						int numnum;
						numnum = atoi(shell_argv[1]);
						executeHistory(historyArray, numnum);
					}
				}
			} 

			//if user command doesn't equal to history, alias, path
			//then execute built-in commands
			else
			{
				execute(shell_argv);
			}

			//free memory
			for(i=0; i<shell_argc; i++){
				temp[i] = '\0';
			}
			
			printf("\n");	
	   
		}
		//close file
		fclose(batchFile);
    }
    //interactive mode
    else if (argc == 1)
    {
        while (1)
        {
            printf("[engine]$> ");
            scanf(" %[^\n]", cmd); //read in user input command
			//Add history consecutively
	    	addHistory(historyArray,cmd,historySize);
			//increment counter for future reference
			historySize++; 

			////////////////////////////////////////////////////////alias////////////////////////////////////////////////////
            // split words from a string using parseLine function
            // parseLine(cmd, ext_wo_arr);
            // getAlias(*ext_wo_arr);
			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

            // if user enters quit, exit shell
            if ((strcmp(cmd, "exit") == 0))
            {
                exit1();
            }

			//parse user input command and store it into arr array
			parseLine(cmd, arr);

			//if first argument of parsed user input line is history, go into this if statement
			if (strcmp(arr[0], "history")==0)
			{
				//if second argument is null, print history array using printHistory function
				if(arr[1] == NULL)
				{
					printHistory(historySize, historyArray);
				}
				////if second argument is "-c", clear history array using deleteHistory function
				else if (strcmp(arr[1],"-c")==0)
				{
                    deleteHistory(historyArray, historySize+1);
					historySize = 0;
                }
				//if second argument is number, find the element in history array that is stored in
				//the index of that user input number using findHistory function
				else if (isdigit(*arr[1]) != 0)
				{
					if(arr[2] == NULL)
					{
						int numnum;
						numnum = atoi(arr[1]);
						findHistory(numnum, historyArray);
					}

					//if second argument is number and third argument is "-e", execute that command in
					//history array using executeHistory function
					else if(strcmp(arr[2], "-e") == 0)
					{
						int numnum;
						numnum = atoi(arr[1]);
						executeHistory(historyArray, numnum);
					}
				}
			}
			//if user command doesn't equal to history, alias, path
			//then execute built-in commands
    		else
			{
				execute(arr);
			}   

			//free memory
			for (i = 0; i<100; i++){
				arr[i] = '\0';
			}
		}
	}
}

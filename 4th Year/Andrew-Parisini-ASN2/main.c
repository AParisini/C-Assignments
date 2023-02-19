#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <sys/wait.h>

#define MAX_LINE 80
#define TOK_DELIM " \t\r\n\a"

/**
* After reading user input, the steps are:
* (1) Fork a child process using fork()
Note that: The fork() system call is invoked inside a while
loop. If the while loop is not well programmed, it will
invoke fork() continuously, potentially leading to many
child processes. When there are too many dangling processes
under your account, your CSID will be suspended. You are
encouraged to use the commands in Appendix 2 to monitor your
processes. And if you cannot log into “csci3120.cs.dal.ca”
using your CSID any more, you need to contact with
cshelp@cs.dal.ca to unlock your CSID.


* (2) The child process will invoke execvp()
Note that:

(i) If the user input is an invalid command, execvp() will
not replace the child process with a binary executable.
Instead, execvp() returns the value of “-1”. In this case,
the child process should check the return value and invoke
exit() system call to terminate itself. Otherwise, the child
process will keep running, potentially leading to the
situation where the parent waits for the child to terminate
and the child becomes a clone of the parent (note that, in
this case, the child would create its own child process if
the user enters another command).

(ii) If the user input is a valid command, exit() does not
need to be invoked because the child process will be
replaced with the binary executable corresponding to the
valid command, and the executable can be terminated
properly. The details can be found in Section 3.4.b.c.


* (3) Parent will invoke wait()
*/

/**
 * @brief This function will run the asked command. Depending on the result of the fork creation,
 * The system will either run, bring out an error, or wait
 * 
 * @param args input line
 * @param should_wait should wait flag
 * @return execute status (either 0 or 1)
 */
int execute(char ** args, int should_wait) {

    pid_t pid;

    //Second input check    
    int status;
        
    //Fork creation
    pid = fork();
    
    if (pid == 0) {
        
        status = execvp(args[0], args);
        if(status == -1){
            exit();
        }
        exit();

    } 
    //Error has ocured upon forking
    else if (pid < 0) {    
        return 1;

    } 
    //Parent Process
    else if (pid > 0) {       
        
        if (!should_wait) {
            // wait if the user hasn't entered an '&'
            wait(NULL);
        }
    }
    return 0;
}

/**
 * @brief tokenize_input will tokenize the input given from main(). 
 * Upon return, tokenize_input will return an array with each input on a single element.
 * If the input is invalid, then this function will return 1 (False in C). So execvp will not be run.
 * 
 * @param inputLine Input line
 * @param sw Should Wait pointer
 * @return char** 
 */
char **tokenize_input(char *inputLine, int *sw){
    
    int bufsize = MAX_LINE;
    int index = 0;
    char **input = malloc(bufsize * sizeof(char*));
    char *tok_input;

    //If input fails to be created - this is a premature death of the function
    if (!input){        
        exit(1);
    }

    //If the code passes this point, then input mallocing was created correctly.

    tok_input = strtok(inputLine, TOK_DELIM);
    while (tok_input != NULL) {
        if (strcmp(tok_input, "&") == 0) {
            // check if the user entered an ampersand, if so, increment
            // index without adding the character to the array
            sw[0] = 1;
            index++;
        }
        else{
            input[index] = tok_input;
            index++;
        }
        //  If the index is bigger than buffer size, then the program will reallocate some more memory - if it is false; to do so,
        //  then we kill the program prematurely
        if (index > bufsize){
            input = realloc(tok_input, bufsize * sizeof(char*)); 
            if (!input){
                exit(1);
            }
        }
        
        tok_input = strtok(NULL, TOK_DELIM);
    }

    //Inserting a NULL pointer at the end, so there is a proper END character to read
    input[index] = NULL; 
    
    return input;
}

/**
 * @brief This function checks the input before going ahead - mainly for "exit" and for an empty / invalid argument
 * 
 * @param args input line
 * @return should run status
 */
int check_input(char **args){

    // "Exit" was entered - this starts the kill process - changes should_run to 0 (stopping the main while loop)
    if (strcmp(args[0], "exit") == 0) {
        return 0;
    }
    if (!args[0]) {
        return 0;
    }
    return 1;
}

/**
 * @brief Simple reverse array print for history array
 * 
 * @param history history array 
 * @param count command count
 */
void print_history(char **history, int count){

    //Less than full history list
    if (count < 10) {
        
        int i = 0;
        for (i = count - 1; i >= 0; i--){
            printf(" %d %s\n", i, history[i]);
        }

    } 
    //Full history list
    else {
        
        int number = count - 1;
        int index = 0;
        
        while (index < 10) {

            printf("%d %s\n", number, history[number % 10]);
            number = number - 1;
            index += 1;
        }
    }
}

// ---------------------------------------------MAIN()--------------------------------------------------------


int main(void)
{
    int i;
    char *line;
    char **args;
    int execute_status;
    int should_run = 1;
    
    //History Array
    char **history = (char **)malloc(sizeof(char *) * 10);    
    for(i = 0; i < 10; i++){
        history[i] = (char *)malloc(sizeof(char) * 100);
    }

    int command_count = 0;
    //Temporary char array to hold input
    char temp[100];    

    //Create checkpoint flag which will be set as 1 when User enters &
    int should_wait[1]; 

    //Pointer for Should Wait
    int *sw;
    sw = should_wait;
    sw[0] = 0;

    while(should_run) {

        printf("CSCI320>");           
        
        fgets(line, 100, stdin);
        
        strcpy(temp, line);
        args = tokenize_input(temp, sw);

        //If there is no argument, default message will print out
        if (!args[0]) {
            printf("Please enter a valid command.\n");
        }

        // !!
        else if (strcmp(args[0], "!!") == 0){ 
           if (command_count == 0){
                printf("No commands in history.\n");
           } 
           else{
                strcpy(history[(command_count) % 10], history[(command_count - 1) % 10]);
                execute_status = execute(tokenize_input(history[(command_count - 1) % 10], sw), sw[0]);

                command_count++;
            }
        }

        // !N
        else if (args[0][0] == '!') {
            
            int number;
            char *string = args[0];
            char *newstring = string + 1;
            char spot = newstring[0];
            int flag = 1;
            int i = 0;

            while (spot) {
                if (!isdigit(spot)) {
                    flag = 0;
                }
                i++;
                spot = newstring[i];
            }

            if (flag) {

                //Change string to integer               
                number = atoi(newstring);
             
                if (number > command_count || number < 0) {                
                    printf("No such command in history.\n");            
                }
                else {

                    //Line gets entered just as saved                    
                    number = (number) % 10; 
                    strcpy(history[(command_count + 1) % 10], history[command_count % 10]);
                    execute_status = execute(tokenize_input(history[number % 10], sw), sw[0]);
                    command_count++;            
                    }
            } 
            //Default Message if incorrect command is entered
            else {
                printf("Not a valid command.\n");
            }
        } 
        //Print out history
        else if (strcmp(args[0], "history") == 0) {
            
            if (command_count == 0) {
                printf("No commands in history.\n");
            }
            
            print_history(history, command_count);
        } 
        //History was not called, so the program will just run the command without checking history (it willl add to the hsitory however)
        else {
        
            strcpy(history[command_count % 10], line);
            command_count++;
            should_run = check_input(args);
            
            if (should_run) {
                execute_status = execute(args, sw[0]);
            }            
        }

        fflush(stdout);    
    } 
    return 0;
}

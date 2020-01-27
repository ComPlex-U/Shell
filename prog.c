#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>



#define MAXCOM 1000 // max number of letters to be supported
#define MAXLIST 100 // max number of commands to be supported

char *argvectorglob[MAXLIST];
// Greeting shell during startup

void init_shell()
{
    printf("\n\n\n\n******************"
           "******************************");
    printf("\n\n\n\t****Simple Shell****");
    printf("\n\n João Estevão");
    printf("\n\n\n\n*******************"
           "******************************");
    char* username = getenv("USER");
    printf("\n\n\nBem-vindo: @%s", username);
    printf("\n");

    sleep(1);
}

char * inputfunc()
{
   char * palavra;
    palavra = malloc(10);
    printf( "Introduza um comando:\n" );
    fgets(palavra, MAXLIST, stdin);
    if(strlen(palavra) != 0)
    {
        return palavra;

    } else
    { return "Ensira um comando";}

}


void GetCommand(char command[]) {

    printf("Comando: ");
    printf(command);
    printf("Type quit to exit\n");
    char * exit;
    int true = 1 ;
    while(true == 1)
    {
   scanf("%s",exit);
    if (strcmp(exit, "quit") == 0)
    {
        true = 0;
    } else{
        printf("Type quit to exit\n");
    }
    }
    free(exit);


}

int PrintArguments(char command[])
{
    printf("Argumentos:\n");
    char* args;
    char* cmd = command;
    int i = 0;

    while ((args = strtok_r(cmd, " ", &cmd))) {
        if(i==1) {
            printf("%s\n", args);

        } else{
            i=1;
        }
    }
    free(args);
    free(cmd);


}



void makeArgVector(char command[], char *argVector[])
{

    char* args;
    char* cmd = command;
    int i = -1;

    args = strtok(cmd, " ");

    while(args != NULL){
        if(i>=0) {
            printf("Argumento nº%i: ", i+1);
            printf("%s", args);
            printf("\n");
            argvectorglob[i] = args;
            argvectorglob[i] = malloc(MAXLIST*sizeof(char));

            i++;
            args=strtok(NULL," ");
        } else{i++;
        printf("Comando: ");
        printf(args);
            printf("\n");
            args=strtok(NULL," ");


        }

    }


}


int main() {
    init_shell();
    char quit = 1;
    while(quit == 1) {
        char *inputcmd;
        inputcmd = inputfunc();
        if (strcmp(inputcmd, "quit\n")== 0)
        {
            quit=0;
            exit(0);

        }

        //GetCommand(inputcmd);
        //PrintArguments(inputcmd);
        makeArgVector(inputcmd, argvectorglob);

        // Forking a child
        pid_t pid = fork();

        if (pid == -1) {
            printf("\nFailed forking child!!");
        } else if (pid == 0) {
            if (execvp(inputcmd, argvectorglob) < 0) {
                printf("\nCould not execute command..");
            }

            exit(0);
        } else {
            // waiting for child to terminate
            wait(NULL);
        }
    }
}

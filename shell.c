#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>


void parseCommand(char *line, char ** argv){

    const char delim[]={'\t','\n',' '};
    int i;
    i= 0;

    argv[i] = strtok(line, " ");

    while(argv[i] != NULL)
    {
        argv[++i]= strtok(NULL, delim);
    }
    if(line[strlen(line - 1)] == '\n')
        line[strlen(line - 1)] = '\0';

    /*while (*line != '\0')
    {
        while (*line == ' ' || *line == '\t' || *line == '\n')
            *line++ = '\0';

        *argv++ = line;

        while (*line != '\0' && *line != ' ' &&
               *line != '\t' && *line != '\n')

            line++;
    }

    *argv = '\0';*/


}
int main()
{
    int status, pid;
    char  line[1024];
    char  *argv[10];

    while(1) {
        fgets(line, sizeof(line), stdin);

        parseCommand(line, argv);

        if ((pid = fork()) == -1)
        {
            perror("fork");
            return EXIT_FAILURE;
        }
        if (pid == 0)
        {

            if (execvp(*argv, argv) < 0)
            {
                printf("*** ERROR: exec failed\n");
                exit(1);
            }

        } else
        {
            waitpid(-1, &status, 0) ;
        }

    }

}


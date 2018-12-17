#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_NUMBER_OF_PARAMS 10

void parse_command(char *line, char ** argv){
    /*int i;
    if((argv==NULL) || (*argv==NULL))
        return;
    i=0;
    argv[i] = strtok( line, '\0' );
    while(argv[i] != NULL  )
    {
        argv[++i] = strtok( NULL, '\0' );
    }
*/

    while (*line != '\0')
    {
        while (*line == ' ' || *line == '\t' || *line == '\n')
            *line++ = '\0';

        *argv++ = line;

        while (*line != '\0' && *line != ' ' &&
               *line != '\t' && *line != '\n')

            line++;
    }

    *argv = '\0';
}
int main()
{
    int status, pid;
    char  line[1024];
    char  *argv[10];

    while(1) {

        fgets(line, sizeof(line), stdin);
        parse_command(line, argv);

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


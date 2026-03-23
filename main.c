#include <stdlib.h>
#include <stdio.h>
#define LSH_BUFSIZE 1024

void lsh_loop(void)
{
    char *line;  // The pointer here points at a string in buffer that is the user's input
    char **args; // The arguments in the user's input which is needed to be parsed
    int status;

    // This is the shell loop that awaits the user input and then parses it and finally excutes it
    do
    {

        printf("> ");
        line = lsh_read_line;
        args = lsh_split_line(line);
        status = lsh_execute(args);

        free(line);
        free(args);
    }

    while (status);
}

void *lsh_read_line() {

    int bufsize = LSH_BUFSIZE;
    int position = 0;
    char *buffer = malloc(sizeof(char) * bufsize);
    int c;
    
    if (!buffer)
    {
        fprintf(stderr, "lsh: allocation error\n");
        exit(EXIT_FAILURE);
    }

    c = getchar();

    if (c == EOF || c == '\n')
    {
        
    }

    while(1)
    {
        c = getchar();
    }
};
void **lsh_split_line(char *line) {};

int main(int argc, char **argv)
{
}
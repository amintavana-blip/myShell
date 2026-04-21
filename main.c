#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#define LSH_BUFSIZE 1024
#define LSH_TOK_BUFSIZE 64
#define LSH_TOK_DELIM " \t\r\n\a"

// Prototypes
char *lsh_read_line(void);
char **lsh_split_line(char *line);
int lsh_execute(char **args);

void lsh_loop(void);

void lsh_loop(void)
{
    char *line;  // The pointer here points at a string in buffer that is the user's input
    char **args; // The arguments in the user's input which is needed to be parsed
    int status;

    // This is the shell loop that awaits the user input and then parses it and finally excutes it
    do
    {

        printf("> ");
        line = lsh_read_line();
        args = lsh_split_line(line);
        status = lsh_execute(args);

        free(line);
        free(args);
    }

    while (status);
}

char *lsh_read_line(void)
{

    int bufsize = LSH_BUFSIZE;
    int position = 0;
    char *buffer = malloc(sizeof(char) * bufsize);
    int c;

    if (!buffer)
    {
        fprintf(stderr, "lsh: allocation error\n");
        exit(EXIT_FAILURE);
    }

    while (1)
    {

        c = getchar(); // Read a character from the standard input system (stdin)

        // If we hit EOF, replace it with a null character and return.
        // It essentially means if the user hit enter we catch the string and put a \0 at the end of it.

        if (c == EOF || c == '\n')
        {
            buffer[position] = '\0';
            return buffer;
        }

        else
        {
            buffer[position] = c;
        }
        position++;

        // If we have exceeded the buffer, reallocate.
        if (position >= bufsize)
        {
            bufsize += LSH_BUFSIZE;
            buffer = realloc(buffer, bufsize);

            if (!buffer)
            {
                fprintf(stderr, "lsh: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }
    }
}

char **lsh_split_line(char *line)
{
    int bufsize = LSH_TOK_BUFSIZE;
    int position = 0;
    char **tokens = malloc(bufsize * sizeof(char *));
    char *token;

    // This function does the process of tokenasition for us.
    token = strtok(line, LSH_TOK_DELIM);

    while (token != NULL)
    {
        tokens[position] = token;
        position++;

        // If the buffer size excceds its limit we are going to reallocate

        if (position >= bufsize)
        {
            bufsize += LSH_BUFSIZE;
            tokens = realloc(tokens, bufsize * sizeof(char *));

            if (!tokens)
            {
                fprintf(stderr, "lsh: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, LSH_TOK_DELIM);
    }

    tokens[position] = NULL;
    return tokens;
}

int lsh_launch(char **args)
{
    pid_t pid, wpid;
    int status;

    pid = fork();
    if (pid == 0)
    {
        if (execvp(args[0], args) == -1)
        {
            perror("lsh");
        }

        exit(EXIT_FAILURE);
    }

    else if (pid < 0)
    {
        perror("lsh");
    }

    else
    {
        
    }
}

int main(int argc, char **argv)
{
}
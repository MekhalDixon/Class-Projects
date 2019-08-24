#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/wait.h>

extern char **Ggetline();
int main()
{
    int i;
    char **args;
    while (1)
    {
        //Shell Header
        blue();
        printf("\nUSER");
        white();
        printf("@");
        yellow();
        printf("WISH\n");
        yellow();
        printf("# ");
        cyan();
        //Shell Header

        //Command Prompt
        args = Ggetline();

        for (i = 0; args[i] != NULL; i++)
        {

            printf("Argument %d: %s\n", i, args[i]);

            if (strcasecmp("exit", args[0]) == 0) //Check for exit command
            {
                if (strcmp("exit", args[i]) == 0)
                    exit(0);

                printf("Error: command 'exit' is case sensitive...\n");
            }

            if (args[i + 1] == NULL) // Run command
            {
                runcommand(args);
            }
        }
    }
}

void runcommand(char **args)
{
    if (appendcontains(args) != 0) // If you append to a file, run this:
    {
        int f, p;
        int i = contains(">", args); //returns index of '>'
        if ((p = fork()))
        {
            waitpid(p, (void *)0, 0); //wait if parent
        }
        else
        {
            args[i] = NULL;
            f = open(args[i + 2], O_WRONLY | O_APPEND);
            lseek(f, 0, SEEK_SET);
            close(1);
            dup(f);
            close(f);
            execvp(args[0], args);
        }
    }
    else if (contains(">", args)) // If there's file redirection, run this:
    {
        int f, p;
        int i = contains(">", args);
        if (p = fork())
        {
            waitpid(p, (void *)0, 0); //wait if parent
        }
        else
        {
            args[i] = NULL; //removes '>' symbol from command
            f = open(args[i + 1], O_TRUNC | O_CREAT | O_WRONLY, 0666);
            close(1);
            dup(f);
            close(f);
            execvp(args[0], args);
        }
    }
    else if (contains("<", args)) // If there's output redirection, run this:
    {
        int f, p;
        int i = contains("<", args);
        if (p = fork())
        {
            waitpid(p, (void *)0, 0); //wait if parent
        }
        else
        {
            args[i] = NULL; //removes '<' symbol from command
            f = open(args[i + 1], O_RDONLY, 0666);
            close(0);
            dup(f);
            close(f);
            execvp(args[0], args);
        }
    }
    else // Any other command
    {
        pid_t pid = fork();

        if (pid == 0) //If baby process
        {
            execvp(args[0], args);
            exit(0);
        }
        else //if Big Boy process
        {
            waitpid(pid, (void *)0, 0);
        }
    }
}

int contains(char *a, char **b)
{
    for (int i = 0; b[i] != NULL; i++)
    {

        if (strcmp(a, b[i]) == 0)
        {
            return i;
        }
    }
    return 0;
}

int appendcontains(char **b)
{
    for (int i = 0; b[i] != NULL; i++)
    {

        if (strcmp(">", b[i]) == 0) //If the first
        {
            if (strcmp(">", b[i + 1]))
            {
                return i;
            }
        }
    }
    return 0;
}

void red() { printf("\033[0;31m"); }
void blue() { printf("\033[0;34m"); }
void green() { printf("\033[2;32m"); }
void cyan() { printf("\033[0;36m"); };
void yellow() { printf("\033[0;33m"); };
void mustard() { printf("\033[2;33m"); };
void ocean() { printf("\033[2;34m"); };
void white() { printf("\033[0m"); };

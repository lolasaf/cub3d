#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include "gnl/get_next_line.h"


int ft_popen(const char *file, char *const argv[], char type)
{
    int fd[2];
    pid_t pid;
    int stream;
    int status;
    
    if (type != 'r' && type != 'w')
        return -1;
    if (pipe(fd) == -1)
        return -1;
    
    pid = fork();
    if (pid < 0)
    {
        close(fd[0]);
        close(fd[1]);
        return -1;
    }
    if(pid == 0)
    {
        if (type == 'r')
        {
            // close(fd[0]);
            dup2(fd[1], STDOUT_FILENO);
        }
        else
        {
            // close(fd[1]);
            dup2(fd[0], STDIN_FILENO);
        }
        // close(fd[1 - (type == 'r')]);
        execvp(file, argv);
        exit(EXIT_FAILURE);
    }
    
    if (type == 'r')
    {
        //close(fd[1]);
        stream = fd[0];
    }
    else
    {
        //close(fd[0]);
        stream = fd[1];
    }
    wait(&status);
    printf("%d\n", status);
    return stream;
}

int	main() {
	int	fd = ft_popen("ls", (char *const []){"ls", NULL}, 'w');
	char	*line;
	while ((line = get_next_line(fd)))
		printf("%s\n", line);
}
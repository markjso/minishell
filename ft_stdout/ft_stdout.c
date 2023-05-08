#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <time.h>
#include <sys/wait.h>
#include <fcntl.h>

#include "../minishell.h"

int	ft_stdout(char *command, char *out_file)
{
	int pid = fork();
	if (pid == -1)
		return (1);
	if (pid == 0)
	{
		int file = open(*out_file, O_WRONLY | O_CREAT, 0777); //bitwise 'or' because both have octal numbers. 
		if (file == -1)
			return 2;
		printf("FD file = open is: %d\n", file);
		// dup2(FD to duplicate, the value the new FD will have)
		int file2 = dup2(file, STDOUT_FILENO);
		printf("The duplicated fd: %d\n", file2);
		close(file);

		/*Only need these 2 lines: */
		dup2(file, STDOUT_FILENO);
		close(file);


		int err = execlp("ping", "ping", "-c", "3", "google.com", NULL);
		if (err == -1) {
			printf("Could not find program to execute.\n");
			return 3;
		}
	} else {
		//Parent process. 
		int waitStatus;
		wait(&waitStatus);
		if (WIFEXITED(waitStatus)) {
			//statusCode is the return value in the child process. 
			int statusCode = WEXITSTATUS(waitStatus);
			if (statusCode == 0) {
				printf("Sucess\n");
			} else {
				printf("Failure with status code %d\n", statusCode);
			}
		}
		
		printf("\n\nWait status number: %d\n", waitStatus);
		printf("PID is: %d\n", pid);
	}
	return 0;
}

int main(int argc, char *argv[])
{
	if (ft_stdout == 0)
		return (0);
	else
		return (1);
}
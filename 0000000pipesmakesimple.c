#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char * argv[]) {
	int fd[2];
	if (pipe(fd) == -1) {
		return 1;
	}
	int pid1 = fork();
	if (pid1 < 0) {
		return 2;
	}

	if (pid1 == 0) {
		//Child process 1(ping)
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		if (execlp("ping", "ping", "-c", "5", "google.com", NULL) == -1) {
			return 3;
		}
	} 

	int pid2 = fork();
	if (pid2 < 0) {
		return 3;
	}
	if (pid2 == 0) { 
		//Child process 2 (grep)
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		execlp("grep", "grep", "rtt", NULL);
	} 

	close(fd[0]);
	close(fd[1]);

	waitpid(pid1, NULL, 0); //process, status, options
	waitpid(pid2, NULL, 0);
	return 0;
}
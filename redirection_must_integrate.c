#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <time.h>
#include <sys/wait.h>
#include <fcntl.h>

//Make these a struct: 
int file;
int file2_out;
int temp_out;
int file2_in;
int	temp_in;


/*Redirect file descriptor 1 to a file.*/
void	ft_output()
{
	file = open("out.txt", O_WRONLY | O_CREAT, 0777); //bitwise 'or' because both have octal numbers. 
	if (file == -1) { exit(2); }
	printf("Still outside: The output fd: %d\n", file);
	temp_out = dup(STDOUT_FILENO);
	file2_out = dup2(file, STDOUT_FILENO);
	close(file);
}

/*Redirect file descriptor 0 to a file.*/
void	ft_input()
{
	file = open("in.txt", O_RDONLY, 0644);
	if (file == -1) {exit(1); }
	printf("The input fd: %d\n", file);
	temp_in = dup(STDIN_FILENO);
	file2_in = dup2(file, STDIN_FILENO);
	close(file);
}

/*Reset file descriptors 0 and 1 to default.*/
void	ft_reset()
{
	close(file2_out);
	dup2(temp_out, STDOUT_FILENO);
	close(temp_out);

	close(file2_in);
	dup2(temp_in, STDIN_FILENO);
	close(temp_in);
}

/*Run the command 'cat'. 
If input file descriptors are changed, then data will be passed as a 
parameter into cat, instead of cat reading what to use. 
*/
void	ft_write()
{
	int pid = fork();
	if (pid == -1) { exit(1); }
	if (pid == 0) {

	execlp("/bin/cat", "/bin/cat", NULL);
	} else {
		int wstatus;
		wait(&wstatus);
		if (WIFEXITED(wstatus)) {
			int statusCode = WEXITSTATUS(wstatus);
			if (statusCode == 0) { printf("Success\n"); }
			else {printf("Failure with staus code %d\n", statusCode); }
		}
		printf("Post processing here\n");
	}
}

int main(int argc, char *argv[])
{
	printf("outise item 0\n");
	ft_output();
	printf("inside item 1\n");
	ft_input();
	printf("inside item 2\n");
	ft_write();
	printf("inside item 3\n");
	ft_reset();
	printf("outside item 4\n");
	printf("hi there again\n");
	return 0;
}
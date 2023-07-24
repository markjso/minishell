#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <time.h>
#include <sys/wait.h>
#include <fcntl.h>


/*Redirect file_temp descriptor 1 to a file_temp.*/
void	ft_output(int *out_backup, int *out_file)
{
	int	file_temp;

	file_temp = open("out.txt", O_WRONLY | O_CREAT, 0777); //bitwise 'or' because both have octal numbers. 
	if (file_temp == -1) { exit(2); }
	printf("Still outside: The output fd: %d\n", file_temp);
	*out_backup = dup(STDOUT_FILENO);
	*out_file = dup2(file_temp, STDOUT_FILENO);
	close(file_temp);
}

/*Redirect file_temp descriptor 0 to a file_temp.*/
void	ft_input(int *in_backup, int *in_file)
{
	int	file_temp;

	file_temp = open("in.txt", O_RDONLY, 0644);
	if (file_temp == -1) {exit(1); }
	printf("The input fd: %d\n", file_temp);
	*in_backup = dup(STDIN_FILENO);
	*in_file = dup2(file_temp, STDIN_FILENO);
	close(file_temp);
}

/*Reset file_temp descriptors 0 and 1 to default.*/
void	ft_reset(int *out_file, int *out_backup, int *in_file, int *in_backup)
{
	close(*out_file);
	dup2(*out_backup, STDOUT_FILENO);
	close(*out_backup);

	close(*in_file);
	dup2(*in_backup, STDIN_FILENO);
	close(*in_backup);
}

/*Run the command 'cat'. 
If input file_temp descriptors are changed, then data will be passed as a 
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
	int out_file;
	int out_backup;
	int in_file;
	int	in_backup;

	printf("outise item 0\n");
	ft_output(&out_backup, &out_file);
	printf("inside item 1\n");
	ft_input(&in_backup, &in_file);
	printf("inside item 2\n");
	ft_write();
	printf("inside item 3\n");
	ft_reset(&out_file, &out_backup, &in_file, &in_backup);
	printf("outside item 4\n");
	printf("hi there again\n");
	return 0;
}
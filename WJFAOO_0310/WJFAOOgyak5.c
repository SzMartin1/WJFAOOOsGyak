#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

int main(void){
	int pid;
	int status;
	if ((pid=fork())<0)
	{
		perror("fork error");
	}
	else if (pid==0)
	{
		exit(7);
	}
	if (wait(&status)!=pid)
	{
		perror("wait error");
	}
	if (WIFEXITED(status))
	{
		printf("Normalis a befejezodes,a visszaadott ertek:%d\n", WEXITSTATUS(status));
	}
	return 0;
}
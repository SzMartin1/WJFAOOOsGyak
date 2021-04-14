#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#define MSIZE 128
int main(){
char inBuffer[MSIZE];
int p[2], nbytes, pid;
if (pipe(p) < 0)
{
	perror("Pipe error");
	exit(1);
}
pid = fork();
if (pid < 0)
	exit(2);
//Child beleír a pipe-ba
if (pid == 0)
{
	printf("Child: pipe-ba iras\n");
	write(p[1], "SzM WJFAOO", MSIZE);
	printf("Child: sikeres pipe-ba iras\n");
}
//Parent kiolvassa
else if (pid > 0 )
{
	wait(NULL);
	printf("Parent: kiolvasok a pipe-bol\n");
	read(p[0], inBuffer, MSIZE);
	printf("ezt olvastam ki: %s\n", inBuffer);
	printf("Parent: finished\n");
}

return 0;
}

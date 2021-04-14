#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#define MSIZE 128
int main(){
char inBuffer[MSIZE];
int pid, fileDesc;
char input[] = "Szabo Martin";
char * fifo = "/tmp/WJFAOO;
mkfifo(fifo, 0666);
pid = fork();
if (pid < 0)
	exit(2);
//Child beleír a pipe-ba
if (pid == 0)
{
	printf("Child: fifo pipe-ba iras\n");
	fileDesc = open(fifo, O_WRONLY);
	write(fileDesc, input, strlen(input)+1);
	printf("Child: sikeres pipe-ba iras\n");
}
//Parent kiolvassa
else if (pid > 0 ){
	fileDesc = open(fifo, O_RDONLY);
	read(fileDesc, inBuffer, strlen(input)+1);
	printf("Parent jelenti: Ezt kaptam: %s\n", inBuffer);
	close(fileDesc);
}

return 0;
}

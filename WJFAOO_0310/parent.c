#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(void){
	int pid;
	
	if ((pid = fork()) < 0){
		perror("Fork error");
	} else if (pid == 0){
		if (execl("./child", "child", (char *)NULL) < 0){
			perror("Execl error");
		}
	}
	
	if (waitpid(pid, NULL, 0) < 0{
		perror("Wait error");
	}
	
	return 0;
}
		
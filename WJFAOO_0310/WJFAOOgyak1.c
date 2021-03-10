#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

int main(void){
	int sts;

	if ( (sts = system("date")) < 0){
		perror("system() error");
	}

	if (WIFEXITED(sts)){
		printf("Normális befejeződés, visszaadott érték = %d\n", WEXITSTATUS(sts));
	}

	return 0;
}
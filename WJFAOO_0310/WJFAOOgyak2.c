#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>

int main(void){

	char bekertparancs[100];
    printf("Adjon meg egy parancsot, amelyet futtatni szeretne: ");
    scanf("%s", bekertparancs);

	system(bekertparancs);

	return 0;
}
#include <unistd.h>
#include <signal.h>
#include <stdio.h>

void do_nothing();

int main()
{
signal(SIGALRM, do_nothing);
printf("Varok, de meddig varjak?\n");
pause();
printf("Itt is van az alarm!\n");
}
void do_nothing()
{
    ;
}

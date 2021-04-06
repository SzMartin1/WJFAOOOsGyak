#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

void handleSignal(int sig);

int main()
{
    signal(SIGINT, handleSignal); //Az Interrupt Signal-t �tadom a handleSignal-nak
    signal(SIGQUIT, handleSignal); //A Quit Signal-t �tadom ugyan �gy a handleSignal-nak
    for (int i=0; i<10; i++)
    { //10x v�runk jelet a felhaszn�l�t�l
	    printf("Varunk...\n");
	    pause();
    }
    return 0;
}

void handleSignal(int sig)
{
    char desc[50];
    switch(sig)
    {
	    case 1:
        {
	      strcpy(desc, "Hangup Signal");
          break;
	    }

	    case 2:
        {//Interrupt Signal 2-essel j�n ide, ez�rt az �zenetet �t�rjuk
	      strcpy(desc, "Interrupt Signal");
	      signal(SIGINT, SIG_DFL);//A C feladatnak megfelel�en �t�ll�tjuk az interruptot az eredeti �llapot�ra
	      printf("\nA CTRL + C megnyom�sa most m�r ki fogja l�ptetni a programb�l!");
	      break;
	    }

	    case 3:
        {//A Quit 3-as k�ddal t�r ide, ez�rt ezt itt kezelj�k
	      strcpy(desc, "Quit Signal");
	      break;
	    }

	    case 4:
        {
	      strcpy(desc, "Illegal Instruction Signal");
	      break;
	    }

	    case 5:
        {
	      strcpy(desc, "Trace Trap Signal");
	      break;
	    }

	    case 6:
        {
	      strcpy(desc, "Abort Signal");
	      break;
	    }
}
printf("\nAz elkapott jel: %s\n", desc);
}



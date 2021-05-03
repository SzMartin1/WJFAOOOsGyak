#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"

void report_and_exit(const char* msg);

int main() {

  int i, j = 1;
  int numberFromFile;
  int numberOf;
  long typeIterator = 2;
  char payloads[10];

  key_t key = ftok(PathName, ProjectId);
  if (key < 0)
    report_and_exit("couldn't get key...");

  int qid = msgget(key, 0666 | IPC_CREAT);
  if (qid < 0)
    report_and_exit("couldn't get queue id...");

  FILE* file = fopen (InputFile, "r");

  //első sor a feladatok száma
  fscanf (file, "%d", &i);
  numberOf = i;
  int types[numberOf];
  //int types[feladatszámhosszú] = { 2, 3, 4 ...};
  char numberstring[numberOf * 3];
  char numberAsChar;

  //type 1 es üzenetbe elküldöm hogy hány darab feladat lesz
  queuedMessage msg;
  msg.type = 1;
  char temp = numberOf + '0';
  msg.payload[0] = temp;
  msgsnd(qid, &msg, sizeof(msg), IPC_NOWAIT);
  int num = msg.payload[0] - '0';
  printf("char=%s, int=%d sent as type %i\n", msg.payload, num, (int) msg.type);
  
  while (!feof (file)){
    for (int numberOfNumbers = 0; numberOfNumbers < 3; numberOfNumbers++){
      fscanf (file, "%d ", &numberFromFile);
      //intet char rá alakítom
      numberAsChar = numberFromFile + '0';
      printf("int=%d char=%c\n", numberFromFile, numberAsChar);
      msg.payload[numberOfNumbers] = numberAsChar;
    }
    msg.type = typeIterator;
    msgsnd(qid, &msg, sizeof(msg), IPC_NOWAIT);
    typeIterator += 1;
    printf("char=%s sent as type %i\n", msg.payload, (int) msg.type);
  }
  fclose (file); 
  return 0;
}

void report_and_exit(const char* msg) {
  perror(msg);
  exit(-1);
}
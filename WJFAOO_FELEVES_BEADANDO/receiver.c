#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <math.h>
#include "queue.h"

void report_and_exit(const char* msg);

void quadraticToFile(FILE* file, float a, float b, float c);

int main() {

  int numberOfTasks;
  int a, b, c;

  key_t key= ftok(PathName, ProjectId); /* key to identify the queue */
  if (key < 0)
    report_and_exit("key not gotten...");

  int qid = msgget(key, 0666 | IPC_CREAT); /* access if created already */
  if (qid < 0)
    report_and_exit("no access to queue...");

  queuedMessage msg;

  //type 1 es message tartalmazza a feladatok számát
  if (msgrcv(qid, &msg, sizeof(msg), 1, MSG_NOERROR | IPC_NOWAIT) < 0)
    puts("msgrcv trouble...");
  numberOfTasks = msg.payload[0] - '0';
  printf("Number of tasks = %d \n", numberOfTasks);
  long types[numberOfTasks];

  for (int iterator = 2; iterator < numberOfTasks + 2; iterator++){
    types[iterator - 2] = iterator; 
  }

  FILE* file = fopen (OutputFile, "w");
  for (int messageIterator = 0; messageIterator < numberOfTasks; messageIterator++){
    if (msgrcv(qid, &msg, sizeof(msg), types[messageIterator], MSG_NOERROR | IPC_NOWAIT) < 0)
      puts("msgrcv trouble...");
    printf("\n%s   received as type %i\n", msg.payload, (int) msg.type);
    a = msg.payload[0] - '0';
    b = msg.payload[1] - '0';
    c = msg.payload[2] - '0';
    printf("a=%d\tb=%d\tc=%d\n",a ,b ,c);
    quadraticToFile(file, a, b, c);
  }
  fclose (file); 

  //befejezés
  if (msgctl(qid, IPC_RMID, NULL) < 0)
    report_and_exit("trouble removing queue...");

  return 0;
}


void report_and_exit(const char* msg) {

  perror(msg);
  exit(-1);

}

void quadraticToFile(FILE* file, float a, float b, float c){

  float discriminant = b * b - 4 * a * c;
 
  if(discriminant < 0){

    printf("Roots are complec numbers.\n");
    float realPart = -b / (2 * a);
    float imagPart = sqrt(-discriminant) / (2 * a);
    printf("Roots of quadratic equation are: ");
    printf("%.5lf+%.5lfi, %.5f-%.5fi", realPart, imagPart, realPart, imagPart);
    fprintf(file, "%.2f %.2f %.2f %.5lf+%.5lfi %.5f-%.5fi\n", a, b, c, realPart, imagPart, realPart, imagPart);

  }
  else if(discriminant == 0){

   printf("Both roots are equal.\n");
   float root1 = -b /(2 * a);
   printf("Root of quadratic equation is: %.5f ", root1);
   fprintf(file, "%.2f %f.2f %.2f \n", a, b, c);

  }
  else{

   printf("Roots are real numbers.\n");
   float root1 = ( -b + sqrt(discriminant)) / (2 * a);
   float root2 = ( -b - sqrt(discriminant)) / (2 * a);
   printf("Roots of quadratic equation are: %.5f , %.5f", root1, root2);
   fprintf(file, "%.2f %.2f %.2f %.5f %.5f\n", a, b, c, root1, root2);

  }

}
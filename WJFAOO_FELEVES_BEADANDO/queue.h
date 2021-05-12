#define ProjectId 123
#define PathName  "queue.h"
#define MsgLen 4
#define MsgCount 4
#define InputFile "input.txt"
#define OutputFile "output.txt"

typedef struct {
  long type;                 // üzenet azonosítója
  char payload[MsgLen + 1];  // az üzenet tartalma
} queuedMessage;
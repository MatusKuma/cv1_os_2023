#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  if (argc != 2){
    fprintf(2,"sleep usage: sleep <ticks>\n");
    exit(1);
  }
  int ticks = atoi(argv[1]);
  fprintf(1,"System bude spat %d tikov\n",ticks);
  sleep(ticks);
  fprintf(1,"System sa zobudil\n");
  exit(0); 
}

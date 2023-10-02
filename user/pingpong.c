#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main (int argc, char *argv[]){

  int to_child[2];
  int to_parent[2];

  int pipe1 = pipe(to_child);
  int pipe2 = pipe(to_parent);
  if((pipe1<0)||(pipe2<0)){
    fprintf(2,"pipe error");
    exit(1);
  }
  int ret_fork = fork();
  if(ret_fork==0){
    //child 
    char received;
    int count_read = read(to_child[0],&received,1);
    if(count_read != 1){
      fprintf(2,"read() error");
      exit(1);
    }
    else{
      fprintf(1,"%d: received ping\n",getpid());
    }
    write(to_parent[1],"x",1);
  }
  else if(ret_fork > 0)
  //parent
  {

    write(to_child[1],"x",1);
    char received;
    int count_read = read(to_parent[0],&received,1);
    if(count_read == 1){
      fprintf(1,"%d: received pong\n",getpid());
    }
    else{
      fprintf(2,"read error");
      exit(1);
    }
  }
  else {
  fprintf(2,"fork() error");
  }

  exit(0);
}

#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void
exec_rura(int fd){
  //nacita prve cislo  z citacej strany vloyenej rury
  int num;
  read(fd,&num,4);
  fprintf(1,"prime %d\n",num);
  //vytvorenie rury
  int rura[2];
  pipe(rura);

  int tmp = -1;

  //cyklus ktory nacitava cisla ktore niesu delitelne cislo, ktore bolo prve v rure
  while (1){
    int n = read(fd,&tmp,4);
    if(n<=0){
      break;
    }
    if (tmp % num !=0){
      //zapisu do rury tie ktore niesu nelitelne
      write(rura[1],&tmp,4);
    }
  }
  //zisti sa ci nahodou bolonieco nacitane ci uz neni koniec inak sa vsetko zavre a vrati
  if(tmp == -1){
    close(rura[1]);
    close(rura[0]);
    close(fd);
    return;
  }
  //vytvori sa dalsi proces cez fork ked je pid =0 teda je v deckom procese tak pozatvara zapisovaciu cast rury a rekurzivne sa znovu zavola funkcia exec_rura
  int pid = fork();
  if(pid ==0){
    close(rura[1]);
    close(fd);
    exec_rura(rura[0]);
    close(rura[0]);
  }
  //ked je v procesy rodica tak vsetko pozatvara a caka
  else{
    close(rura[1]);
    close(rura[0]);
    close(fd);
    wait(0);
  }
 }



int
main(int argc, char *argv[])
{
  int rura[2];
  pipe(rura);
  //nahadze do rury vsetky cisla od 2 po 35
  for(int i = 2; i<=35;i++){
    write(rura[1],&i,4);
  }
  //zavre zapisovaciu stranu rury
  close(rura[1]);
  //vojde do funkcie exec_rury
  exec_rura(rura[0]);
  //zavre citaciu stranu rury
  close(rura[0]);

  exit(0); 
}

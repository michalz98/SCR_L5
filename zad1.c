#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

#define buff_size 10
int main(int argc, char **argv)
{
  int filedes, fd[2], pid, nbytes, i=0;
  char buff[buff_size];

  if(pipe(fd) == -1) {
    perror("pipe");
    exit(EXIT_FAILURE);
  }
  pid = fork();
  if(pid > 0){
    //kod rodzica
    filedes = open(argv[1], O_RDONLY);
    while((nbytes=read(filedes,buff,sizeof(buff))) > 0){
      write(fd[1],buff,sizeof(buff));
    }
  } else if(pid == 0) {
    // kod dziecka
    while ((nbytes = read(fd[0], buff, sizeof(buff))) > 0){
      printf("#%s#", buff);
      i++;
    }
  } else {
    //blad
    printf("ERROR");
  }
  close(fd[0]);
  close(fd[1]);
  return(0);
}

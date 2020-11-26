#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
  int filedes, fd[2], pid, nbytes, i;

  if(pipe(fd) == -1) {
    perror("pipe");
    exit(EXIT_FAILURE);
  }
  pid = fork();
  if(pid > 0){
    //kod rodzica
    close(fd[0]);
    filedes = open(argv[1], O_RDONLY);
    while((nbytes=read(filedes,&i,1)) > 0){
      write(fd[1],&i, 1);
    }
    close(fd[1]);
  } else if(pid == 0) {
    // kod dziecka
    close(fd[1]);
    sleep(2);
    close(0);
    dup(fd[0]);
    execlp("/usr/bin/display","display", (char *)NULL);
    read(fd[0], &i, 1);
  } else {
    //blad
    printf("ERROR");
  }
  close(fd[0]);
  close(fd[1]);
  return(0);
}

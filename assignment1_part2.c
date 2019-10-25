#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char* argv[]){

  int temp;
  int fd[2];
  pid_t pid;
 
  if (pipe(fd) < 0){ // check for a pipe error
    perror("pipe error");
    exit(0);
  } 

  pid = fork();
  if (pid < 0) { // check for a fork error
    perror("fork error");
    exit(0);
  }

  if(pid > 0) //parent
  {
    int i = getpid();
    int x = atoi(argv[1]);
    printf("\n A pipe is created for communication between parent (PID %d) and child\n", i);
    printf("\n parent (PID %d) created a child (PID %d)\n", i, pid);
    printf("\n parent (PID %d) Reading X = %d from the user\n", i, x);
    wait(NULL); // waits for child process to finish
    read (fd[0],&temp,1); // reads Y input and stores it in temp
    printf("\n parent (PID %d) Reading Y from the pipe (Y = %d)\n", i, temp);
    printf("\n parent (PID %d) adding X + Y = %d\n\n", i, x + temp);
    
  } else //child
   
  {
    int i = getpid();
    int y = atoi(argv[2]);
    printf("\n child (PID %d) Reading Y = %d from the user\n", i, y);
    printf("\n child (PID %d) Writing Y into the pipe\n", i);
    write (fd[1],&y,1);

  }

  return 0;

}
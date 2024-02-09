#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdlib.h>
#include <iostream>

using namespace std;
// 32:57
int main(){
  size_t Maxsize = 80;
  int fd[2], nbytes;
  pid_t childpid; 
  char readbuffer[80];
  char sharedStr[] = "Hello, CS442!\n";
  if(pipe(fd) < 0){// Create a pipe
    exit(1); //Error. No Pipe was created
  } 

  if((childpid = fork()) == -1){
    perror("fork did not work; Sorry!");
    exit(1);
  }
  
  if(childpid == 1){
    //Child proccess closes up input side of pipe
    //This is because you can only use one side at a time
    close(fd[0]); // 0 is the input side
    write(fd[1], sharedStr, (strnlen(sharedStr, Maxsize)));
    exit(0);
  } else {
    wait(NULL);
    // Non-child closes the output side
    close(fd[1]);
    nbytes = read(fd[0], readbuffer, sizeof(readbuffer));
    cout << "From Parent: Recieved String: " << readbuffer << endl;
  }
  return 0;

  /*
   * I haven't verified the documentation but I believe both read and write are as follows
   * - pipe to read from
   * - string to write or buffer to fill
   * - lenght that we can read or write
  */
}

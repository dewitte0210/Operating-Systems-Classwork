#include<iostream>
#include<unistd.h>
#include<stdlib.h>
#include<fcntl.h>
#include<string>

using namespace std;


/*
* The dup sys call creates a copy of the file descriptor oldfd, 
* using the lowest-numbered unusede file descriptor for the new descriptor.
* This is useful for implementing piping and redirection in linux shell
*/
int main(){
  //system call open() returns a file descriptor fd to a file
  //"duptest.txt" sored in the same location
  int fd = open("duptest.txt", O_WRONLY | O_APPEND);
  if(fd < 0) {
    cout << "Can not open the file" << endl;
    exit(1);
  }

  //dup() will create the copy of fd as the copy_fd then both can be used interchangeably as needed
  int copyFd = dup(fd);

  //write() will write msg1 and msg2 to the file using the file descriptors
  string msg1 = "I am Evan Dewitt\n";
  string msg2 = "I live in Menomonie\n";

  //writing via the copy file descriptors
  write(copyFd, (char *)msg1.c_str(), msg1.size());
  
  //writing via the original file descriptor
  write(fd, (char *)msg2.c_str(), msg2.size());

  return 0;
}

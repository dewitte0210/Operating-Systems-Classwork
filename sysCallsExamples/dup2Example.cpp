#include<unistd.h>
#include<stdlib.h>
#include<iostream>
#include<string>
#include<fcntl.h>
using namespace std;
//performs the same task as dup but instead of using the lowest unused file descriptor,
//it uses the file descriptor specified in newfd. int dup2(int oldfd, int newfd)
int main(){
  int fd = open("dup2test.txt", O_WRONLY | O_APPEND);
  if(fd < 0){
    cout << "Can not open the file" << endl;
    exit(1);
  }
  //here the newfd is the file descriptor of stdout
  dup2(fd, 1);

  //All the output stateements will be written in the file dup2test.txt
  cout << "I will be written to the file dup2test.txt" << endl;

  //write will write msg1 and msg2 to the file
  string msg1 = "I am Evan Dewitt\n";
  string msg2 = "I live in Menomonie\n";
  cout << msg1;

  write(fd, (char *)msg2.c_str(), msg2.size());
  close(fd);
  return 0;
}

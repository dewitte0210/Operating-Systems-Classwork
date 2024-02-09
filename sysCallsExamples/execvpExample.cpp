/*
This example shows how to change the execution image for a child process with
execvp system call.
*/
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <sys/wait.h>
using namespace std;

char * commandString[3];
void child (){
  if( execvp(commandString[0], commandString) <0 ){
  cout<<"Sorry. Couldn't change the execution image for the child process"<< endl;
  //I would use an exception
  }
  cout<<"This statement will never be executed, if execvp was successfull";
}

void parent(){
  cout<<"Back to the parent"<<endl;
}

int main(){
  string command="./myname"; // this is the ls unix command
  //string argument1="-l"; // this is an argument for the ls
  commandString[0]=(char*) command.c_str(); //this is how to convert a string variable to a c_string
 // commandString[1]=(char*) argument1.c_str();
  commandString[1]=NULL;
  pid_t pid;
  pid= fork();
  if (pid== 0){ // a child was created and you are inside it
    child();
  } 
  else if (pid< 0) // no new child was created (fail)
  {
    cout<<"No New Child Was created \n";
    return 1; // 1 is something bad happended
  }
  else // must be the parent
  {
    wait(0);
    parent();
  }
  return 0;
}

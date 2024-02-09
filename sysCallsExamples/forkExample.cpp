/*
This example shows how to create a new child process using fork system call.
//Note: No guarantee which process will be scheduled first
(could be parent, most likely for this small program, or the child).
But it is unpredictable
*/
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <sys/wait.h>
using namespace std;

void child (){
  for(int i=0; i<100; ++i){ // uncomment the loop and run the code multiple times if you need a proof that it is unpredectible output
    cout<<"++++++++++++++++++++++++++++++A New Child was created \n";

  }
}

void parent(){
  for (int i=0; i< 100; ++i){ //uncomment the loop if you want a proof
    cout<< "-----------------------------------------------------------I am theparent :)\n";
  }
}

int main(){
  cout<<"Welcome from the paren process :) "<<endl;
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

#include <iostream>
#include <unistd.h>
#include <bits/stdc++.h>
#include <vector>
#include <fcntl.h>
#include <sys/wait.h>

using namespace std;

void child(char* command[], const char* FILENAME){
  int fileFD = open(FILENAME, O_WRONLY | O_CREAT,0666);
  dup2(fileFD, 1);

  if(execvp(command[0], command) < 0){
    perror("execvp failed\n");
    exit(1);
  }
}

int main(){
  const char FILENAME[] = "outputredir.txt\0";
  cout << "Please enter your command" << endl;
  string command;
  getline(cin, command);
  stringstream lineStream(command); 
  string token;

  vector<string> tokens;
  while(getline(lineStream, token, ' ')){
    tokens.push_back(token);
  }

  int size = tokens.size();
  char* commands[size + 1];
  commands[size] = NULL;

  for(int i = 0; i < tokens.size();i++) {
    char* word = (char*)tokens.at(i).c_str();
    commands[i] = word;
  }
  
  pid_t childPID;
  if((childPID = fork()) == -1){
    perror("failed to create child");
  }

  if(childPID == 0){
    child(commands, FILENAME);
  }
  wait(0);
  fflush(stdout);
  return 0;
}

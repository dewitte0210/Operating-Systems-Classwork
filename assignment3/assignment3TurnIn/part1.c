#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <string.h>
#include <fcntl.h>

void child(int fdSend[2], int fdRecieve[2], const int READ_SIZE, const int WRITE_SIZE, const char* FILENAME){
  char readBuffer[READ_SIZE];
  char responseBuffer[WRITE_SIZE];
  close(fdRecieve[1]); 
  int nBytes = read(fdRecieve[0], readBuffer, sizeof(readBuffer));

  if(nBytes == 0){
    perror("ERROR, readBuffer was empty");
    exit(1);
  }
   
  bool found = false; 
  FILE *file;
  char line[READ_SIZE];
  file = fopen(FILENAME, "r");
  if (file == NULL){
    perror("Unable to open file");
    exit(1);
  }

  while(fgets(line, READ_SIZE, file) != NULL){
   if (strncmp(line, readBuffer, strlen(line) - 1) == 0){
      found = true;
    }
  }

  close (fdSend[0]);
  if(found){
    strcpy(responseBuffer, "FOUND\0");
  } else {
    strcpy(responseBuffer, "NOT FOUND\0");
  }
  write(fdSend[1], responseBuffer, sizeof(responseBuffer));
  exit(0);

}

void parent(int sendFD[2], int recieveFD[2], const int WRITE_SIZE, const int READ_SIZE){

    char writeBuffer[WRITE_SIZE];
    printf("Please enter your passkey\n");
    scanf("%19s", writeBuffer);

    close(sendFD[0]); //Close the input side of the passkey pipe 
    write(sendFD[1], writeBuffer, WRITE_SIZE + 1);
    
    wait(0);
    
    char readBuffer[READ_SIZE];
    close(recieveFD[1]); //Close the ouptput side of the reponse pipe;
    int nBytes = read(recieveFD[0], readBuffer, READ_SIZE);
    if(nBytes == -1){
      perror("ERROR, No response from child");
      exit(1);
    }
    printf(readBuffer);
}

int main(){
  int passkeySendFD[2], responseFD[2], nBytes;
  const int READ_SIZE = 20, RESPONSE_SIZE = 10;
  const char FILENAME[] = "./passkeys.txt\0";
  pid_t childPID;

  if(pipe(passkeySendFD) < 0 || pipe(responseFD) < 0){
    perror("ERROR, Unable to create pipes");
    exit(1);
  }
  
  if((childPID = fork()) == -1){
    perror("ERROR, Unable to fork child");
    exit(1);
  }
  
  if(childPID == 0){//we are in the child
    child(responseFD, passkeySendFD, READ_SIZE, RESPONSE_SIZE, FILENAME);
  } else if (childPID < 0) {
    perror("Child Creation failed");
    exit(1);
  } else{ //we are in the parent
    parent(passkeySendFD, responseFD,READ_SIZE, RESPONSE_SIZE); 
  }
  return 0;
}

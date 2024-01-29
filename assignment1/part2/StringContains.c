#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int main(){
  char line[256];
  printf("Enter your line\n");
  fgets(line, sizeof(line) -1, stdin);

  char word[64];
  printf("Enter the word to search for\n");
  scanf("%63s", word);

  char *token = strtok(line, " ");
  bool found = false;

  while (token != NULL){
    if(strncmp(word, token, strlen(word)) == 0){
      found = true;
    }
    token = strtok(NULL, " ");
  }
  
  if(found){
    printf("FOUND\n");
  } else{
    printf("NOT FOUND\n");
  }
  
}

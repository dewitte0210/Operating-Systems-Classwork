#include<string>
#include<iostream>
#include <bits/stdc++.h>
using namespace std;

int main(){

  string line;

  cout << "Please enter your line" << endl;
  getline(cin, line);
  
  string word;
  cout << "please enter the word to search for" << endl;
  getline(cin, word);
  
  stringstream lineStream(line);
  string token;
  
  bool found = false;
  while(getline(lineStream, token, ' ')){
    if(word.compare(token) == 0){
      found = true;
    }
  }

  if(found){
    cout << "FOUND" << endl;
  } else{
    cout << "NOT FOUND" << endl;
  }
}

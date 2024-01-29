#include<iostream> 
#include<bits/stdc++.h>
#include<vector>
#include<string>
using namespace std;

int main(){
  cout << "Please enter your line" << endl;
  string line;
  getline(cin, line);

  stringstream lineStream(line); 
  string token;
  vector<string> tokens;
  while(getline(lineStream, token, ' ')){
    tokens.push_back(token);
  }
  int size = tokens.size();
  char* cStrings[size] = new char[size][64];
  
  for(int i = 0; i < tokens.size();i++) {
    char* word = (char*)tokens.at(i).c_str();
    cStrings[i] = *word;
  }
  
  for(int i = 0; i < tokens.size(); i++){
    cout << cStrings[i] << endl;
  }
  delete[] cStrings;
  return 0;
}

#include<bits/stdc++.h>
#include<vector>
#include<string>
#include<fstream>
using namespace std;

vector<string> tokenize(string line){
  vector<string> tokens;
  stringstream lineStream(line);
  string token;
  while(getline(lineStream, token, ' ')){
    tokens.push_back(token);
  }
  return tokens;
}

vector<string> getCommands(string filePath){
  ifstream inFile;
  inFile.open(filePath);
  vector<string> commands; 
  string line; 
  while(!inFile.eof()){
    getline(inFile, line);
    commands.push_back(line);
  }
  inFile.close();
  return commands;
}

string parseString(string command, int commandID){
  vector<string> tokens = tokenize(command);
  int found[] = {-1, -1, -1};
  
  for(int i = 0; i < tokens.size(); i++){
    if(tokens.at(i) == "|"){
      found[0] = i; 
    } else if(tokens.at(i) == "<"){
      found[1] = i;
    } else if(tokens.at(i) == ">"){
      found[2] = i;
    }
  }
 
  string pipe = (found[0] != -1) ? "| found in position " + to_string(found[0]) + ", " : "No |,";
  string left = (found[1] != -1) ? "< found in position " + to_string(found[1]) + ", ": "No <,";
  string right = (found[2] != -1) ? "> found in position " + to_string(found[2]) : "No >";
  return "Command " + to_string(commandID) + ": " + pipe + left + right;
}

int main(){
 
  vector<string> commands = getCommands("commands.txt");  
  ofstream outFile;
  outFile.open("parseresults.txt");

  for(int i = 0; i < commands.size(); i++){
    outFile << parseString(commands.at(i), i) << endl;
  }
  outFile.close();
  return 0;
}

#include <chrono>
#include <iostream>
#include <vector>
using namespace std;
using namespace std::chrono;

vector<int> CountingSort(vector<int> array){
  int max = array[0];
  for(int i = 0; i < array.size(); i++){
    if(array[i] > max){
      max = array.at(i);
    }
  }
  
  vector<int> counts(max+1, 0);
  for(int i = 0; i < array.size(); i++){
    counts.at(array.at(i))++;
  }

  for(int i = 1; i <= max; i++){
    counts.at(i) += counts.at(i-1);
  }
 
  vector<int> outputArray(array.size());
  for(int i = array.size()-1; i >= 0; i--){
    outputArray.at(counts.at(array.at(i)) - 1) = array.at(i);
    counts.at(array.at(i))--;
  }

  return outputArray;
}
int partition(vector<int> arr, int low, int high){
  int pivot = arr.at(high);
  int smallest = (low-1);
  
  for(int i=low; i <=high; i++){
    if(arr.at(i) < pivot){
      smallest++;
      
      int temp = arr.at(i);
      arr.at(i) = arr.at(smallest);
      arr.at(smallest) = temp;
    }
  }
 
  int temp = arr.at(smallest + 1);
  arr.at(smallest + 1) = arr.at(high);
  arr.at(high) = temp;
  return(smallest + 1);
}
vector<int> QuickSort(vector<int> arr, int low, int high){

  if(low < high)
  {
    int partitionIndex = partition(arr,low,high);
    QuickSort(arr,low,partitionIndex-1);
    QuickSort(arr,partitionIndex+1, high);
  }
 return arr;
}

int main(){
  vector<int> numbers;
  srand(time(0));
  
  // Had to use 100000 instead of 100 Mil because QuickSort was taking too long
  for(int i = 0; i < 100000; i++){
    numbers.push_back(rand() % 50 + 1);
  }
  auto start = high_resolution_clock::now();
  CountingSort(numbers);
  auto stop = high_resolution_clock::now();
  auto duration = duration_cast<microseconds>(stop - start);
  cout << "Counting Sort took: " << duration.count() << " microseconds" << endl;

  start = high_resolution_clock::now();
  QuickSort(numbers, 0, numbers.size()-1) ;
  stop = high_resolution_clock::now();
  duration = duration_cast<microseconds>(stop - start);
  cout << "QuickSort took: " << duration.count() << " microseconds" << endl;
  return 0;
} 

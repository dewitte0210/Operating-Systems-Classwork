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
int partition(int arr[], int low, int high){

  int pivot = arr[high];
  int smallest = (low-1);
  
  for(int i=low; i <=high; i++){
    if(arr[i] < pivot){
      smallest++;
      
      int temp = arr[i];
      arr[i] = arr[smallest];
      arr[smallest] = temp;
    }
  }
 
  int temp = arr[smallest+1];
  arr[smallest+1] = arr[high];
  arr[high] = temp;
  return(smallest + 1);
}

bool QuickSort(int arr[], int low, int high){
  if(low < high){
    int partitionIndex = partition(arr, low, high);
    QuickSort(arr, low, partitionIndex - 1);
    QuickSort(arr, partitionIndex + 1, high);
  }
  return true;
}

int main(){
 vector<int> numbersVec;
  srand(time(0));
  const int SIZE = 100000;
 int numbers[SIZE];
  for(int i = 0; i < SIZE; i++){
    int random = rand() % 50 + 1; 
    numbers[i] = random;
    numbersVec.push_back(random);
  }
  auto start = high_resolution_clock::now();
  CountingSort(numbersVec);
  auto stop = high_resolution_clock::now();
  auto duration = duration_cast<microseconds>(stop - start);
  cout << "Counting Sort took: " << duration.count() << " microseconds" << endl;

  start = high_resolution_clock::now();
  QuickSort(numbers, 0, SIZE-1) ;
  stop = high_resolution_clock::now();
  duration = duration_cast<microseconds>(stop - start);
  cout << "QuickSort took: " << duration.count() << " microseconds" << endl;
  return 0;
} 

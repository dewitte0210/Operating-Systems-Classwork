import java.util.Random;
public class SortNumbers{

  public static void main(String[] args){
    Random rand = new Random();
    
    int[] numbers = new int[100000];
    for(int i = 0; i < numbers.length; i++){
      numbers[i] = rand.nextInt(50) + 1;
    }

    long start = System.nanoTime();
    CountingSort(numbers);
    long end = System.nanoTime();
    long elapsedTime = end - start;
    System.out.println("Counting Sort took: " + (elapsedTime / 1000) + " microseconds");

    start = System.nanoTime();
    QuickSort(numbers,0,numbers.length - 1);
    end = System.nanoTime();
    elapsedTime = end - start;
    System.out.println("Quick Sort took: "  + (elapsedTime / 1000) + " microseconds");

  }

  static int[] CountingSort(int arr[]){
    int max = arr[0];
    for(int i = 0; i < arr.length; i++) {
      if(max < arr[i]) {
        max = arr[i];
      }
    }

    int counts[] = new int[max+1];
    for(int i = 0; i < arr.length; i++) {
      counts[arr[i]]++;
    }

    for(int i = 1; i <= max;i++){
      counts[i] += counts[i-1]; 
    }
    
    int output[] = new int[arr.length];
    for(int i = arr.length - 1; i >= 0; i--){
      output[counts[arr[i]] - 1]  = arr[i];
      counts[arr[i]]--;
    }
    return output; 
  }
  
  static int[] QuickSort(int arr[], int low, int high) {
    if(low < high)
    {
     int partitionIndex = partition(arr,low,high);
     QuickSort(arr,low,partitionIndex-1);
     QuickSort(arr,partitionIndex+1, high);
    }
    return arr;
  }

  static int partition(int arr[], int low, int high){
    
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
}





public class QuickSort {
   public static void quickSort(int[] list) {
       quickSort(list, 0, list.length - 1);
   }

   public static void quickSort(int[] list, int first, int last) {
       if (last > first) {
           int pivotIndex = partition(list, first, last);
           quickSort(list, first, pivotIndex - 1);
           quickSort(list, pivotIndex + 1, last);
       }
   }

   // Partition the array list[first...last]
   public static int partition(int[] list, int first, int last) {
       int pivot = median(first, first, last); //median as pivot
       int low = first + 1;  // Index for forward search
       int high = last;  // Index for backward search

       while (high > low) {
           // Search forward from left
           while (low <= high && list[low] <= pivot)
               low++;

           // Search backward from right
           while (low <= high && list[high] > pivot)
               high--;

           // Swap two elements in the list
           if (high > low) {
               int temp = list[high];
               list[high] = list[low];
               list[low] = temp;
           }
       }

       while (high > first && list[high] >= pivot)
           high--;

       // Swap pivot with list[high]
       if (pivot > list[high]) {
           list[first] = list[high];
           list[high] = pivot;
           return high;
       }
       else {
           return first;
       }
   }

   // Test QuickSort
   public static void main(String[] args) {
       int[] list = {4, 1, 5, 9, -1, 2, 7};

       System.out.println("before sorting");
       printArray(list);

       quickSort(list);

       System.out.println("after sorting");
       printArray(list);
   }

   public static void printArray(int[] array) {
       for (int item: array) {
           System.out.print(item + " ");
       }
       System.out.println();
   }
   static int median(int one , int teo, int three) {
    return Math.max(Math.min(one, teo), 
        Math.min(Math.max(one, teo), three));
}
}
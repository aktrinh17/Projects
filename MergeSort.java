//MergeSort
import java.util.Arrays;
import java.util.Scanner;

public class MergeSort
{
   private static int[] anArray;
   private static int arrayLength;
   
   public static void main(String[] args)
   {
      //takes input to define "num" as the size of the array
      Scanner input = new Scanner(System.in);
      System.out.println("How many elements would you like the array to contain?");
      int num = input.nextInt();
      
      //creates an array of size num 
      MergeSort sortArray = new MergeSort(num);
      
      //creates a random array and prints it out
      sortArray.createRandArray();
      System.out.println("Random Array: " + Arrays.toString(MergeSort.anArray));
      
      //uses mergesort to sort the array and prints it out
      sortArray = divide(sortArray);
      System.out.println("After Sorting: " + Arrays.toString(MergeSort.anArray));
   }
   
   MergeSort(int currArraySize) 
   {
      arrayLength = currArraySize;
      anArray = new int[arrayLength];
   }

   
   public void createRandArray()
   {
      for (int i = 0; i < arrayLength; i++)
         {
            anArray[i] = (int)(Math.random() * 100 + 1);
         } 
   }
   
   //method to divide an array into individual arrays
   //containing only 1 element each
   public static int[] divide(int[] otherArray)
   {
      int[] result = new int[otherArray.length];
      
      //if the array length is 1, then the division
      //of the arrays are complete, otherwise continue
      if (otherArray.length <= 1)
      {
         return otherArray;
      }
      
      //finds the middle of the array and defines 
      // the left array 
      int middle = otherArray.length/2;
      int[] leftArray = new int[middle];
         
      //if the array is even, the right array can also
      //be the same size as the left array 
      int[] rightArray;
      if (otherArray.length %2 == 0)
      {
         rightArray = new int[middle];
      }
      
      //if the array is odd, the right array will
      //gain an additional element 
      else
      {
         rightArray = new int[++middle];
      }
      
      //fills up the left array with the leftmost
      //contents of the other array
      for (int i = 0; i < middle; i++)
      {
         leftArray[i] = otherArray[i];
      }
      
      //fills up the right array with the rightmost
      //contents of the other array starting at the middle
      int x = 0;
      for (int n = middle; n < otherArray.length; n++)
      {
         rightArray[x++] = otherArray[n];
      }
      
      //recursively divides the left and right portions
      //of the array
      leftArray = divide(leftArray);
      rightArray = divide(rightArray);
      
      result = merge(leftArray, rightArray);
      return result;

   }
   
   public static int[] merge(int[] leftArray, int[] rightArray)
   {
      int totalLength = leftArray.length + rightArray.length;
      int[] result = new int[totalLength];
      int leftPointer = 0;
      int rightPointer = 0;
      int resultPointer = 0;
      
      while (leftPointer < leftArray.length || rightPointer < rightArray.length)
      {
         //if there are still elements in both arrays
         //continue to combine
         if (leftPointer < leftArray.length && rightPointer < rightArray.length)
         {
            //if the left element is smaller, then put it 
            //into the array, otherwise, put the right element
            if (leftArray[leftPointer] <= rightArray[rightPointer])
            {
               result[resultPointer++] = leftArray[leftPointer];
            }
            
            else
            {
               result[resultPointer++] = rightArray[rightPointer];
            }
         }
         
         //if the right array has no more elements,
         //add the remaining elements in the left
         else if (leftPointer < leftArray.length)
         {
            result[resultPointer++] = leftArray[leftPointer++];
         }
         
         else if (rightPointer < rightArray.length)
         {
            result[resultPointer++] = rightArray[rightPointer++];
         }
      }
      
      return result;
   }
}
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
      leftArray = merge(leftArray);
      rightArray = merge(rightArray);
      
      result = merge(leftArray, rightArray);
      return result;

   }
   
   public void merge()
   {
   
   }
}
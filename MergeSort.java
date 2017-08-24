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
   
   public void divide()
   {
   
   }
   
   public void merge()
   {
   
   }
}
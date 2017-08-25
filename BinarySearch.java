import java.util.Arrays;
import java.util.Scanner;

public class BinarySearch
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
      BinarySearch sortArray = new BinarySearch(num);
      
      //creates a random array and prints it out
      sortArray.createRandArray();
      System.out.println("Random Array: " + Arrays.toString(BinarySearch.anArray));
      
   }
   
   BinarySearch(int currArraySize) 
   {
      arrayLength = currArraySize;
      anArray = new int[arrayLength];
   }
   
    //method to create an array with random values from 0 to 100 
   public void createRandArray()  
   {
      for (int i = 0; i < arrayLength; i++)
      {
         anArray[i] = (int)(Math.random() * 100 + 1);
      } 
   }
   
   public static int[] bubbleSort(int[] anArray)
   {
   
   }

   public static int binarySearch(int findNum)
   {
   
   } 

}
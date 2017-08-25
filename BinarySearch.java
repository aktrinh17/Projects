//Uses BubbleSort to sort an array 
//then uses a binary search to find a number
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
      
      //uses bubblesort to sort the array and prints it out
      sortArray.bubbleSort(anArray);
      System.out.println("After Sorting: " + Arrays.toString(BinarySearch.anArray));
      
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
   
   //method to switch the position of two integers
   public void switchVals(int posOne, int posTwo) 
   {
      int temp = anArray[posOne];
      anArray[posOne] = anArray[posTwo];
      anArray[posTwo] = temp;
   }
 
   public int[] bubbleSort(int[] leArray)
   {
      for (int i = leArray.length -1; i > 0; i--)
      {
         for (int n = 0; n < i; n++)
         {
            if (leArray[n] > leArray[n+1])
            {
               switchVals(leArray[n], leArray[n+1]);
            }
            
         }
      }
      return leArray;
   }

   public static int binarySearch(int findNum)
   {
      int left = 0;
      int right = anArray.length -1;
      int middle = (right - left) /2;
      
      if (findNum > middle)
      {
         left = middle +1;
      }
      
      else if (findNum < middle)
      {
         right = middle -1;
      }
      
      else
      {
         return middle;
      }
      return middle;
   } 
}
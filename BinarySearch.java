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
      System.out.println();
      
      //takes input to find "wutNum" in the sorted array
      Scanner input2 = new Scanner(System.in);
      System.out.println( "What number would you like to find?");
      int wutNum = input2.nextInt();
      sortArray.binarySearch(wutNum);
      
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
      //goes through the array starting from the highest index
      for (int i = leArray.length -1; i > 1; i--)
      {
         //goes through the array starting from the lowest index
         for (int n = 0; n < i; n++)
         {
            //switches the place of two integers if the first is larger
            if (leArray[n] > leArray[n +1])
            {
               switchVals(n, n +1);
            }     
         }
      }
      return leArray;
    }

   //method to use binary search to look for the 
   //index of a desired integer
   public void binarySearch(int findNum)
   {
      int left = 0;
      int right = anArray.length -1;
      
      //keeps searching until the index is found
      while (left <= right)
      {
         //cuts the array in half with each iteration
         int middle = (right + left) /2;
      
         //if the middle is less than the number,
         //the search cuts out the lower half
         if (anArray[middle] < findNum)
         {
            left = middle +1;
         }
         
         //if the middle is greater than the number,
         //the search cuts out the upper half
         else if (anArray[middle] > findNum)
         {
            right = middle -1;
         }
      
         /*once this is reached, the number is found to be
           at index "middle" and left is made greater
           than the right to stop the search*/
         else
         {
            left = right +1;
            System.out.println("The number " + findNum + " is located at the array index of " + middle);
         }
      }           
    }
}
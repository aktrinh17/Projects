//This is an example that shows how quicksort operates
import java.util.Arrays;
import java.util.Scanner;

public class QuickSort
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
      QuickSort sortArray = new QuickSort(num);
      
      //creates a random array and prints it out
      sortArray.createRandArray();
      System.out.println("Random Array: " + Arrays.toString(QuickSort.anArray));
      
      //uses quicksort to sort the array and prints it out
      sortArray.quickSort(0, num -1);
      System.out.println("After Sorting: " + Arrays.toString(QuickSort.anArray));
   }
      
   QuickSort(int currArraySize) 
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
    
   public void quickSort(int leftP, int rightP)
   {
      //when this is true, the array must be sorted
      if (rightP - leftP <= 0)
      {
         return;
      }
      
      //if the above is not true, more sorting is required
      //through recursive means
      else
      {
         int pivotP = anArray[rightP];
         int pivotPosition = partition(leftP, rightP, pivotP);
         
         //goes through again to sort the left side of the array
         quickSort(leftP, pivotPosition -1);
         
         //goes throught again to sort the right side of the array
         quickSort(pivotPosition +1, rightP);
      }      
   }
   
   //method takes in left and right pointers and a pivot point   
   public int partition(int leftP, int rightP, int pivotP) 
   {
      int leftPoint = leftP -1;
      int rightPoint = rightP;
      while (true)
      {
         //operates until an integer smaller than the pivot
         //is found or reaches the pivot point
         while (anArray[++leftPoint] < pivotP); 
         
         //operates until an integer larger than the pivot
         //is found or reaches the pivot point
         while (rightPoint > 0 && anArray[--rightPoint] > pivotP);
         
         /*if a number on the left side is found to be
           greater than a number on the right side,
           the points will stop and switch the two */
         if (leftPoint >= rightPoint)
         {
            break;
         }   
         
         else
         {
            switchVals(leftPoint, rightPoint);
         }
      }
      
      switchVals(leftPoint, rightP);
      return leftPoint;
   }            
}

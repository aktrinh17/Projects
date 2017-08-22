//This is an example that shows how quicksort operates
import java.util.Arrays;

public class QuickSort
{
   private static int[] anArray;
   private static int arrayLength; 
   
   public static void main(String[] args)
   {
      QuickSort hArray = new QuickSort(10);
      hArray.createRandArray();
      System.out.println(Arrays.toString(QuickSort.anArray));
   }
      
   QuickSort(int currArraySize) 
   {
      arrayLength = currArraySize;
      anArray = new int[arrayLength];
   }
    
   public void createRandArray() //method to create an array with random values from 10 to 100 
   {
      for (int i = 0; i < arrayLength; i++)
      {
         anArray[i] = (int)(Math.random() * 91) + 10;
      } 
   }
   
   public void switchVals(int posOne, int posTwo) //method to switch the position of two integers
   {
      int temp = anArray[posOne];
      anArray[posOne] = anArray[posTwo];
      anArray[posTwo] = temp;
   }
    
   public void quickSort()
   {
      
   }
      
   public void partition()
   {
      
   }            
}

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Queens;

/**
 *
 * @author J-P
 * 
 * X=an occupied square
 * O=a non-occupied square
 * Changed as an aftertought to help reading, thus the (slight) discrepancy between output and saving the states as ints
 */

public class NQueen {
    static int SIZE=8, CNT=0; //Size (and the amount of queens, so change THIS) and the amount of found solutions
    static int[][] board=new int[SIZE][SIZE]; //a square n*n board
    
    public static void main(String[] args) 
    {
        recursive(SIZE,0);
        System.out.println("Total solutions: "+CNT);
    }
    
    public static boolean check(int n, int row, int col) //Size of the board, and the square to be checked given as arguments
    {
        for (int i=0;i<row;i++) //check for threat in column, ie. loop through previous rows and check the squares
        {
            if(board[i][col]==1) //found a piece, the current square is threatened
                return false;                             
        }
        
        int i=row-1, j=col-1; //check for threat in left diagonal, starting from the NW square in relation to the square to be checked
        while(i>=0 && j>=0)
        {
            if(board[i][j]==1) //found a piece, the current square is threatened
                return false;
            i--;
            j--;
        }
        
        i=row-1;
        j=col+1; //check for threat in right diagonal, starting from the NE square in relation to the square to be checked
        while(i>=0 && j<n)
        {
            if(board[i][j]==1) //found a piece, the current square is threatened
                return false;
            i--;
            j++;
        }         
        
        return true; //Square is not threatened
    }
    
    //Recursive algorithm to find the solutions
    public static void recursive(int n, int row) //Size of the board and the row to be processed are given as arguments
    {
        if(n==row) //n being equal to row means the last queen was placed succesfully -> solution found, print it out
        {               
            CNT++;
            System.out.println("Solution "+CNT+":");
            for (int i=0;i<SIZE;i++)
            {
                
                for(int j=0;j<SIZE;j++)
                {
                    if(board[i][j]==1)
                        System.out.print("X ");
                    else
                        System.out.print("O ");
                }       
                System.out.println();
            }
            
            System.out.println();
            return;
        }
        
       for(int i=0;i<n;i++) //Loop through each square in a row
       {
           if(check(n,row,i)) //Check whether the square is threatened or not
           {
               board[row][i]=1; //If it is not, mark it as occupied
               recursive(n,row+1); //Move on to the next row    
               board[row][i]=0; //After returning from the next loop, set back to 0 (ie. not occupied) and move on to the next square
           }
           
       }
       //The piece has reached the end of the row -> return to previously initiated loop. Return to main, if this was the first row
    }
   
}

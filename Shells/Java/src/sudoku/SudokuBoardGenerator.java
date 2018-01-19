package sudoku;
import java.util.Random;


public class SudokuBoardGenerator {

	public static SudokuFile generateBoard(int N, int p, int q, int numAssignments)
	{	
		return generateBoard(N, p, q, numAssignments, 5000);
	}
	
	public static SudokuFile generateBoard(int N, int p, int q, int numAssignments, long timeout)
	{
		//given a SudokuFile with N, P, Q, creates a board with the given params
		//and assigns it to the board of the SudokuFile.
		//timeout represents the time in ms allowed to created the SudokuFile
		SudokuFile sf = new SudokuFile(N, p, q);
		int[][] tempBoard = new int[sf.getN()][sf.getN()];
		if(numAssignments > sf.getN()*sf.getN())
		{
			System.out.println("Number of assignments exceeds available spaces in board. Returning SudokuFile with an empty board");
			return sf;
		}
		Random integerPicker = new Random();
		long startTime = System.currentTimeMillis();
		long currentTime;
		for(int i = 0; i < numAssignments; i++)
		{
			int randomRow = integerPicker.nextInt(sf.getN()); //0 to N-1
			int randomColumn = integerPicker.nextInt(sf.getN()); //0 to N-1
			int randomAssignment = integerPicker.nextInt(sf.getN())+1; //1 to N
			if(tempBoard [randomRow][randomColumn] == 0 && checkConstraints(randomRow, randomColumn, randomAssignment, sf, tempBoard) )
			{
				tempBoard[randomRow][randomColumn] = randomAssignment;
			}
			else
			{
				i--;
				currentTime = System.currentTimeMillis();
				if(currentTime - startTime > timeout)
				{
					System.out.println("Timeout at "+i+" elements");
					tempBoard = new int[sf.getN()][sf.getN()];
					break;
				}
			}
		}
		sf.setBoard(tempBoard);
		return sf;
	}


	private static boolean checkConstraints(int row, int col, int value, SudokuFile sf, int[][] board)
	{
		if(checkRow(row, value, sf.getN(), board) 
				&& checkColumn(col, value, sf.getN(), board) 
				&& checkBox(row, col, value, sf.getP(), sf.getQ(), board))
		{
			return true;
		}
		
		return false; 
	}

	public static boolean checkRow(int row, int value, int N, int[][] board)
	{
		for(int i = 0; i < N; i++)
		{
			if(board[row][i] == value)
			{
				return false;
			}
		}
		return true;
	}

	public static boolean checkColumn(int column, int value, int N, int[][] board)
	{
		for (int i = 0; i < N; i++)
		{
			if(board[i][column] == value)
			{
				return false;
			}
		}

		return true;
	}

	public static boolean checkBox(int row, int column, int value, int p, int q, int[][] board)
	{
		int rDiv = row/p;
		int cDiv = column/q;
		for(int i = rDiv * p; i < (rDiv + 1) * p; i++)
		{
			for(int j = cDiv * q; j < (cDiv + 1) * q; j++)
			{
				try{
				if(board[i][j] == value)
				{
					return false;
				}
				}catch(ArrayIndexOutOfBoundsException e)
				{
					System.out.println(p + " "+ q);
				}
			}
		}
		return true;
	}
}

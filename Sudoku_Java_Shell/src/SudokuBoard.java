import java.io.Reader;
import java.io.FileReader;
import java.io.File;
import java.io.IOException;
import java.util.Scanner;
import java.util.Random;

/**
 * Represents a Sudoku Board. This is converted to a constraint network,
 * so BTSolver can interface with it as a CSP.
 */

public class SudokuBoard
{

	// =================================================================
	// Properties
	// =================================================================

	private int p; // number of rows in a block && number of block columns
	private int q; // number of columns in a block && number of block rows

	private int[][] board = null;

	// =================================================================
	// Constructors
	// =================================================================

	protected SudokuBoard ( )
	{
		this( 3, 3, null );
	}

	public SudokuBoard ( int p, int q )
	{
		this( p, q, null );
	}

	// Will initialize a board
	public SudokuBoard ( int p, int q, int[][] board )
	{
		this.p = p;
		this.q = q;
		this.board = board == null ? new int[9][9] : board;
	}

	// Will generate a random Sudoku board
	public SudokuBoard ( int p, int q, int m )
	{
		this.p = p;
		this.q = q;
		int N = p*q;
		board = new int[N][N];

		if ( m > N*N )
			m = N*N;

		Random integerPicker = new Random();

		for ( int i = 0; i < m; )
		{
			int randomRow = integerPicker.nextInt( N );
			int randomCol = integerPicker.nextInt( N );
			int randomAssignment = integerPicker.nextInt( N ) + 1;
			if ( board[randomRow][randomCol] == 0 && check( randomRow, randomCol, randomAssignment ) )
			{
				board[randomRow][randomCol] = randomAssignment;
				i++;
			}
		}
	}

	// Will load a Sudoku board from file
	public SudokuBoard ( File file )
	{
		try
		{
			Reader reader = new FileReader(file);
			Scanner scanner = new Scanner(reader);
			this.p = scanner.nextInt();
			this.q = scanner.nextInt();
			int N = p*q;
			this.board = new int[N][N];

			for ( int i = 0; i < N; ++i )
			{
				for ( int j = 0; j < N; ++j )
				{
					if ( ! scanner.hasNext() )
						System.out.println("Incomplete or Emtpy board for file " + file +". Please be advised");

					board[i][j] = odometerToInt( scanner.next() );
				}
			}
		}
		catch ( Exception e )
		{
			e.printStackTrace();
		}
	}

	// =================================================================
	// Accessors
	// =================================================================

	public int getP ( )
	{
		return p;
	}

	public int getQ ( )
	{
		return q;
	}

	public int getN ( )
	{
		return p*q;
	}

	public int[][] getBoard ( )
	{
		return board;
	}

	// =================================================================
	// String representation
	// =================================================================

	public String toString ( )
	{
		int N = getN();
		StringBuilder sb = new StringBuilder();
		sb.append("P: ");
		sb.append(p);
		sb.append("\tQ: ");
		sb.append(q);
		sb.append("\n");
		for(int i = 0; i < N; i ++)
		{
			for(int j = 0; j < N; j++)
			{
				sb.append( intToOdometer(board[i][j]) + " " );
				if((j+1)%q==0 && j!= 0 && j != N-1)
				{
					sb.append("| ");
				}
			}
			sb.append("\n");
			if((i+1)%p == 0 && i != 0 && i != N-1)
			{
				for(int k = 0; k < N+p-1;k++)
				{
					sb.append("- ");
				}
				sb.append("\n");
			}
		}
		return sb.toString();
	}

	// =================================================================
	// Private Helper Methods
	// =================================================================

	private boolean check ( int row, int col, int value )
	{
		return checkRow( row, value ) && checkCol( col, value ) && checkBox( row, col, value );
	}

	private boolean checkRow ( int row, int value )
	{
		for ( int i = 0; i < p*q; ++i )
		{
			if ( board[row][i] == value )
			{
				return false;
			}
		}

		return true;
	}

	private boolean checkCol ( int col, int value )
	{
		for ( int i = 0; i < p*q; ++i )
		{
			if ( board[i][col] == value )
			{
				return false;
			}
		}

		return true;
	}

	private boolean checkBox ( int row, int col, int value )
	{
		int rDiv = row / p;
		int cDiv = col / q;
		for ( int i = rDiv * p; i < (rDiv + 1) * p; ++i )
		{
			for ( int j = cDiv * q; j < (cDiv + 1) * q; ++j )
			{
				if ( board[i][j] == value )
				{
					return false;
				}
			}
		}

		return true;
	}

	private int odometerToInt ( String str )
	{
		int x = 0;

		if ( str.charAt(0) >= '0' && str.charAt(0) <= '9' )
			x = str.charAt(0) - '0';

		if ( str.charAt(0) >= 'A' && str.charAt(0) <= 'Z' )
			x = str.charAt(0) - 'A' + 10;

		for ( int i = 1; i < str.length(); ++i )
			x *= 36;

		if ( str.length() > 1 )
			return x + odometerToInt ( str.substring( 1, str.length() ) );

		return x;
	}

	private String intToOdometer ( int n )
	{
		return Integer.toString( n, 36 );
	}
}

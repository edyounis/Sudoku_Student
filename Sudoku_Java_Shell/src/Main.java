import java.io.FileWriter;
import java.io.BufferedWriter;
import java.io.File;
import java.io.IOException;

/**
 * Main driver file, which is responsible for interfacing with the
 * command line and properly starting the backtrack solver.
 */

public class Main
{
	public static void main ( String[] args )
	{
		// Important Variables
		String file   = "";
		String var_sh = "";
		String val_sh = "";
		String cc     = "";

		for ( int i = 0; i < args.length; ++i )
		{
			String token = args[i];

			if ( token.equals( "MRV" ) )
				var_sh = "MinimumRemainingValue";

			else if ( token.equals( "DEG" ) )
				var_sh = "Degree";

			else if ( token.equals( "MAD" ) )
				var_sh = "MRVwithTieBreaker";

			else if ( token.equals( "LCV" ) )
				val_sh = "LeastConstrainingValue";

			else if ( token.equals( "FC" ) )
				cc = "forwardChecking";

			else if ( token.equals( "NOR" ) )
				cc = "norvigCheck";

			else if ( token.equals( "TOURN" ) )
			{
				 var_sh = "tournVar";
				 val_sh = "tournVal";
				 cc     = "tournCC";
			}

			else
				file = token;
		}

		Trail trail = new Trail();

		if ( file == "" )
		{
			SudokuBoard board = new SudokuBoard( 3, 3, 7 );
			System.out.println( board.toString() );

			BTSolver solver = new BTSolver( board, trail, val_sh, var_sh, cc );
			solver.solve();

			if ( solver.hasSolution() )
			{
				System.out.println( solver.getSolution().toString() );
				System.out.println( "Trail Pushes: " + trail.getPushCount() );
				System.out.println( "Backtracks: " + trail.getUndoCount() );
			}
			else
			{
				System.out.println( "Failed to find a solution" );
			}

			return;
		}


		File location = new File ( file );
		Boolean folder = location.isDirectory();

		if ( folder )
		{
			File[] listOfBoards = location.listFiles();

			if ( listOfBoards == null )
			{
				System.out.println ( "[ERROR] Failed to open directory." );
				return;
			}

			int numSolutions = 0;
			for ( int i = 0; i < listOfBoards.length; ++i )
			{
				System.out.println ( "Running board: " + listOfBoards[i] );

				SudokuBoard board = new SudokuBoard( listOfBoards[i] );

				BTSolver solver = new BTSolver( board, trail, val_sh, var_sh, cc );
				solver.solve();

				if ( solver.hasSolution() )
					numSolutions++;

				trail.clear();
			}

			System.out.println( "Solutions Found: " + numSolutions );
			System.out.println( "Trail Pushes: " + trail.getPushCount() );
			System.out.println( "Backtracks: "  + trail.getUndoCount() );
			return;
		}

		SudokuBoard board = new SudokuBoard( location );
		System.out.println( board.toString() );

		BTSolver solver = new BTSolver( board, trail, val_sh, var_sh, cc );
		solver.solve();

		if ( solver.hasSolution() )
		{
			System.out.println( solver.getSolution().toString() );
			System.out.println( "Trail Pushes: " + trail.getPushCount() );
			System.out.println( "Backtracks: " + trail.getUndoCount() );
		}
		else
		{
			System.out.println( "Failed to find a solution" );
		}
	}
}
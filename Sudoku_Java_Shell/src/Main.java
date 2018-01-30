import java.io.FileWriter;
import java.io.BufferedWriter;
import java.io.File;
import java.io.IOException;

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

			if ( token == "MRV" )
				var_sh = "MinimumRemainingValue";

			else if ( token == "DEG" )
				var_sh = "Degree";

			else if ( token == "MAD" )
				var_sh = "MRVwithTieBreaker";

			else if ( token == "LCV" )
				val_sh = "LeastConstrainingValue";

			else if ( token == "FC" )
				cc = "forwardChecking";

			else if ( token == "NOR" )
				cc = "norvigCheck";

			else
				file = token;
		}

		if ( file == "" )
		{
			SudokuBoard board = new SudokuBoard( 3, 3, 7 );
			System.out.println( board.toString() );

			BTSolver solver = new BTSolver( board, val_sh, var_sh, cc );
			solver.solve();

			if ( solver.hasSolution() )
				System.out.println( solver.getSolution().toString() );

			else
				System.out.println( "Failed to find a solution" );

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

			for ( int i = 0; i < listOfBoards.length; ++i )
			{
				System.out.println ( "Running board: " + listOfBoards[i] );

				SudokuBoard board = new SudokuBoard( listOfBoards[i] );

				BTSolver solver = new BTSolver( board, val_sh, var_sh, cc );
				solver.solve();

				if ( solver.hasSolution() )
					System.out.println( solver.getSolution().toString() );

				else
					System.out.println( "Failed to find a solution" );
			}

			return;
		}

		SudokuBoard board = new SudokuBoard( location );
		System.out.println( board.toString() );

		BTSolver solver = new BTSolver( board, val_sh, var_sh, cc );
		solver.solve();

		if ( solver.hasSolution() )
			System.out.println( solver.getSolution().toString() );

		else
			System.out.println( "Failed to find a solution" );
	}
}
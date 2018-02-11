import java.util.*;
import java.util.Map.*;

/**
 * CSP representation of the problem. Contains the variables, constraints, and
 * many helpful accessors.
 */

public class ConstraintNetwork
{

	// =================================================================
	// Properties
	// =================================================================

	private List<Constraint> constraints;
	private List<Variable> variables;

	// =================================================================
	// Constructors
	// =================================================================

	public ConstraintNetwork ( )
	{
		variables = new ArrayList<Variable>();
		constraints = new ArrayList<Constraint>();
	}

	public ConstraintNetwork ( SudokuBoard sboard )
	{
		int [][] board = sboard.getBoard();

		List<Variable> temp = new ArrayList<Variable>();
		int value = 0;

		for ( int i = 0; i < sboard.getN(); i++ )
		{
			for ( int j = 0; j < sboard.getN(); j++ )
			{
				value = board[i][j];
				List<Integer> domain = new ArrayList<Integer>();

				if (value == 0)
				{
					for (int d = 1; d <= sboard.getN(); d++)
					{
						domain.add(d);
					}
				}
				else
				{
					domain.add(value);
				}

				int block = (i/sboard.getP() * sboard.getP()) + j/sboard.getQ();

				temp.add(new Variable(domain, i, j, block));
			}
		}

		Map<Integer, List<Variable>> rows = new HashMap<Integer, List<Variable>>();
		Map<Integer, List<Variable>> cols = new HashMap<Integer, List<Variable>>();
		Map<Integer, List<Variable>> blocks = new HashMap<Integer, List<Variable>>();

		for ( Variable v : temp )
		{
			int row = v.row();
			int col = v.col();
			int block = v.block();

			if (!rows.containsKey(row))
			{
				rows.put(row, new ArrayList<Variable>());
			}

			if (!cols.containsKey(col))
			{
				cols.put(col, new ArrayList<Variable>());
			}

			if (!blocks.containsKey(block))
			{
				blocks.put(block, new ArrayList<Variable>());
			}
			rows.get(row).add(v);
			cols.get(col).add(v);
			blocks.get(block).add(v);
		}

		variables = new ArrayList<Variable>();
		constraints = new ArrayList<Constraint>();

		for ( Variable v : temp )
		{
			add(v);
		}

		for ( Entry<Integer, List<Variable>> e : rows.entrySet() )
		{
			Constraint c = new Constraint();
			for ( Variable v : e.getValue() )
			{
				c.addVariable(v);
			}
			add(c);
		}

		for ( Entry<Integer, List<Variable>> e : cols.entrySet() )
		{
			Constraint c = new Constraint();
			for ( Variable v : e.getValue() )
			{
				c.addVariable(v);
			}
			add(c);
		}

		for ( Entry<Integer, List<Variable>> e : blocks.entrySet() )
		{
			Constraint c = new Constraint();
			for ( Variable v : e.getValue() )
			{
				c.addVariable(v);
			}
			add(c);
		}
	}

	// =================================================================
	// Modifiers
	// =================================================================

	public void add ( Constraint c )
	{
		if ( ! constraints.contains( c ) )
		{
			constraints.add( c );
		}
	}

	public void add ( Variable v )
	{
		if ( ! variables.contains( v ) )
		{
			variables.add( v );
		}
	}

	// =================================================================
	// Accessors
	// =================================================================

	public List<Constraint> getConstraints ( )
	{
		return constraints;
	}

	public List<Variable> getVariables ( )
	{
		return variables;
	}

	// Returns all variables that share a constraint with v
	public List<Variable> getNeighborsOfVariable ( Variable v )
	{
		Set<Variable> neighbors = new HashSet<Variable>();

		for ( Constraint c : constraints )
		{
			if ( c.contains( v ) )
			{
				neighbors.addAll( c.vars );
			}
		}

		neighbors.remove( v );
		return new ArrayList<Variable>( neighbors );
	}

	// Returns true is every constraint is consistent
	public boolean isConsistent ( )
	{
		for ( Constraint c : constraints )
			if ( ! c.isConsistent() )
				return false;

		return true;
	}

	// Returns a list of constraints that contains v
	public List<Constraint> getConstraintsContainingVariable ( Variable v )
	{
		List<Constraint> outList = new ArrayList<Constraint>();

		for ( Constraint c : constraints )
			if ( c.contains( v ) )
				outList.add( c );

		return outList;
	}

	/**
	 * Returns the constraints that contain variables whose domains were
	 * modified since the last call to this method.
	 *
	 * After getting the constraints, it will reset each variable to
	 * unmodified.
	 *
	 * Note* The first call to this method returns the constraints containing
	 * the initialized variables.
	 */
	public List<Constraint> getModifiedConstraints ( )
	{
		List<Constraint> mConstraints = new ArrayList<Constraint>();

		for ( Constraint c : constraints )
			if ( c.isModified() )
				mConstraints.add( c );

		for ( Variable v : getVariables() )
			v.setModified( false );

		return mConstraints;
	}

	// =================================================================
	// String Representation
	// =================================================================

	public String toString ( )
	{
		StringBuilder sb = new StringBuilder();
		sb.append( variables.size() + " Variables: {" );
		String delim = "";

		for ( Variable v : variables )
		{
			sb.append( delim ).append( v.getName() );
			delim = ",";
		}
		sb.append( "}" );

		sb.append( "\n" + constraints.size() + " Constraints:" );
		delim = "\n";
		for ( Constraint c : constraints )
		{
			sb.append( delim ).append( c.toString() );
		}
		return sb.toString();
	}

	// =================================================================
	// Sudoku Board Representation
	// =================================================================

	public SudokuBoard toSudokuBoard ( int p, int q )
	{
		int n = p*q;
		int [][] board = new int[n][n];
		int row = 0, col = 0;
		for ( Variable v : getVariables() )
		{
			board[row][col++] = v.getAssignment();
			if ( col == n )
			{
				col = 0;
				row++;
			}
		}
		return new SudokuBoard( p, q, board );
	}
}

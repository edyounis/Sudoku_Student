import java.util.Collections;
import java.util.Comparator;
import java.util.List;

public class BTSolver
{

	//===============================================================================
	// Properties
	//===============================================================================

	private ConstraintNetwork network;
	private Trail trail;
	private boolean hasSolution = false;
	private SudokuBoard sudokuGrid;

	public String varHeuristics;
	public String valHeuristics;
	public String cChecks;

	//===============================================================================
	// Constructors
	//===============================================================================

	public BTSolver ( SudokuBoard sboard, Trail trail, String val_sh, String var_sh, String cc )
	{
		this.network    = new ConstraintNetwork( sboard );
		this.sudokuGrid = sboard;
		this.trail      = trail;

		varHeuristics = var_sh;
		valHeuristics = val_sh;
		cChecks       = cc;
	}

	// =================================================================
	// Consistency Checks
	// =================================================================

	// Basic consistency check, no propagation done
	private boolean assignmentsCheck()
	{
		for ( Constraint c : network.getConstraints() )
		{
			if ( ! c.isConsistent() )
			{
				return false;
			}
		}
		return true;
	}

	/**
	 * Part 1 TODO: Implement the Forward Checking Heuristic
	 *
	 * Note: remember to trail.push variables before you assign them
	 * Return: true is assignment is consistent, false otherwise
	 */
	private boolean forwardChecking()
	{
		return false;
	}

	/**
	 * Part 2 TODO: Implement both of Norvig's Heuristics
	 *
	 * Note: remember to trail.push variables before you assign them
	 * Return: true is assignment is consistent, false otherwise
	 */
	private boolean norvigCheck()
	{
		return false;
	}

	// =================================================================
	// Variable Selectors
	// =================================================================

	// Basic variable selector, returns first unassigned variable
	private Variable getfirstUnassignedVariable()
	{
		for ( Variable v : network.getVariables() )
		{
			if ( !v.isAssigned() )
			{
				return v;
			}
		}
		return null;
	}

	/**
	 * Part 1 TODO: Implement the Minimum Remaining Value Heuristic
	 *
	 * Return: The unassigned variable with the smallest domain
	 */
	private Variable getMRV()
	{
		return null;
	}

	/**
	 * Part 2 TODO: Implement the Degree Heuristic
	 *
	 * Return: The unassigned variable involved in the most constraints
	 */
	private Variable getDegree()
	{
		return null;
	}

	/**
	 * Part 2 TODO: Implement the Minimum Remaining Value Heuristic
	 *                with Degree Heuristic as a Tie Breaker
	 *
	 * Return: The unassigned variable with the smallest domain and involved
	 *             in the most constraints
	 */
	private Variable MRVwithTieBreaker()
	{
		return null;
	}

	// =================================================================
	// Variable Selectors
	// =================================================================

	// Default Value Ordering
	public List<Integer> getValuesInOrder ( Variable v )
	{
		List<Integer> values = v.getDomain().getValues();

		Comparator<Integer> valueComparator = new Comparator<Integer>(){

			@Override
			public int compare(Integer i1, Integer i2) {
				return i1.compareTo(i2);
			}
		};
		Collections.sort(values, valueComparator);
		return values;
	}

	/**
	 * Part 1 TODO: Implement the Least Constraining Value Heuristic
	 *
	 * Return: A list of v's domain sorted by the LCV heuristic
	 */
	public List<Integer> getValuesLCVOrder ( Variable v )
	{
		return null;
	}

	//==================================================================
	// Engine Functions
	//==================================================================

	/**
	 * Method to start the solver
	 */
	public void solve()
	{
		solve ( 0 );
	}

	private void solve ( int level )
	{
		if ( hasSolution )
			return;

		// Variable Selection
		Variable v = selectNextVariable();

		if ( v == null )
		{
			for ( Variable var : network.getVariables() )
			{
				// If all variables haven't been assigned
				if ( !var.isAssigned() )
				{
					System.out.println( "Error" );
					return;
				}
			}

			// Success
			hasSolution = true;
			return;
		}

		// Attempt to assign a value
		for ( Integer i : getNextValues( v ) )
		{
			// Store place in trail and push variable's state on trail
			trail.placeTrailMarker();
			trail.push(v);

			// Assign the value
			v.assignValue( i );

			// Propagate constraints, check consistency, recurse
			if ( checkConsistency() )
				solve ( level + 1 );

			// If this assignment succeeded, return
			if ( hasSolution )
				return;

			// Otherwise backtrack
			trail.undo();
		}
	}

	private boolean checkConsistency()
	{
		switch ( cChecks )
		{
			case "forwardChecking":
				return forwardChecking();

			case "norvigCheck":
				return norvigCheck();

			default:
				return assignmentsCheck();
		}
	}

	private Variable selectNextVariable()
	{
		switch ( varHeuristics )
		{
			case "MinimumRemainingValue":
				return getMRV();

			case "Degree":
				return getDegree();

			case "MRVwithTieBreaker":
				return MRVwithTieBreaker();

			default:
				return getfirstUnassignedVariable();
		}
	}

	public List<Integer> getNextValues ( Variable v )
	{
		switch ( valHeuristics )
		{
			case "LeastConstrainingValue":
				return getValuesLCVOrder(v);

			default:
				return getValuesInOrder(v);
		}
	}

	public boolean hasSolution()
	{
		return hasSolution;
	}

	public SudokuBoard getSolution()
	{
		return network.toSudokuBoard ( sudokuGrid.getP(), sudokuGrid.getQ() );
	}

	public ConstraintNetwork getNetwork()
	{
		return network;
	}
}

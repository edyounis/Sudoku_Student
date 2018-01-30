import java.util.Collections;
import java.util.Comparator;
import java.util.List;

public class BTSolver
{

	//===============================================================================
	// Properties
	//===============================================================================

	private ConstraintNetwork network;
	private static Trail trail = Trail.getTrail();
	private boolean hasSolution = false;
	private SudokuBoard sudokuGrid;

	public String varHeuristics;
	public String valHeuristics;
	public String cChecks;

	//===============================================================================
	// Constructors
	//===============================================================================

	public BTSolver ( SudokuBoard sboard, String val_sh, String var_sh, String cc )
	{
		this.network = new ConstraintNetwork( sboard );
		this.sudokuGrid = sboard;
		varHeuristics = var_sh;
		valHeuristics = val_sh;
		cChecks       = cc;
	}

	//===============================================================================
	// Implement Unfinished Methods Here
	//===============================================================================

	private boolean assignmentsCheck()
	{
		for ( Variable v : network.getVariables() )
		{
			if ( v.isAssigned() )
			{
				for ( Variable vOther : network.getNeighborsOfVariable(v) )
				{
					if ( v.getAssignment() == vOther.getAssignment() )
					{
						return false;
					}
				}
			}
		}

		return true;
	}

	private boolean forwardChecking()
	{
		return false;
	}

	private boolean norvigCheck()
	{
		return false;
	}

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

	private Variable getMRV()
	{
		return null;
	}

	private Variable getDegree()
	{
		return null;
	}

	private Variable MRVwithTieBreaker()
	{
		return null;
	}

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

	public List<Integer> getValuesLCVOrder ( Variable v )
	{
		return null;
	}

	//===============================================================================
	// Accessors
	//===============================================================================

	public boolean hasSolution()
	{
		return hasSolution;
	}

	/**
	 * @return solution if a solution has been found, otherwise returns the unsolved puzzle.
	 */
	public SudokuBoard getSolution()
	{
		return network.toSudokuBoard ( sudokuGrid.getP(), sudokuGrid.getQ() );
	}

	public ConstraintNetwork getNetwork()
	{
		return network;
	}

	//===============================================================================
	// Engine Functions
	//===============================================================================

	/**
	 * Method to start the solver
	 */
	public void solve()
	{
		solve ( 0 );
		Trail.clearTrail();
	}

	/**
	 * Solver
	 * @param level How deep the solver is in its recursion.
	 * @throws VariableSelectionException
	 */
	private void solve(int level)
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
				}
			}

			// Success
			hasSolution = true;
			return;
		}

		// Attempt to assign a value
		for ( Integer i : getNextValues(v) )
		{
			trail.placeBreadCrumb();

			// Check a value
			v.updateDomain(new Domain(i));

			// Move to the next assignment
			if ( checkConsistency() )
			{
				solve ( level + 1 );
			}

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
}

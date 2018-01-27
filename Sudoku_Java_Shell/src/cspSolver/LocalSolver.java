package cspSolver;

import java.util.ArrayList;
import java.util.List;

import sudoku.Converter;
import sudoku.SudokuFile;

/**
 * Basic local search solver
 *
 */
public class LocalSolver implements Runnable{

	//===============================================================================
	// Properties
	//===============================================================================

	private ConstraintNetwork network;
	private int n;

	private int numTotalAttempts; 
	private int numAttempts = 0; //used for restarts
	private int limitAttempts = 1000; //used for restarts
	private long startTime, endTime;

	private SudokuFile sudokuGrid;

	//===============================================================================
	// Constructor
	//===============================================================================

	public LocalSolver (SudokuFile sf)
	{
		this.network = Converter.SudokuFileToConstraintNetwork(sf);
		n = sf.getN();
		sudokuGrid = sf;
	}

	//===============================================================================
	// Accessors
	//===============================================================================

	public boolean hasSolution()
	{
		return isSolution();
	}

	/**
	 * @return solution if a solution has been found, otherwise returns the unsolved puzzle.
	 */
	public SudokuFile getSolution()
	{
		return sudokuGrid;
	}

	public void printSolverStats()
	{
		System.out.println("Time taken:" + (endTime-startTime) + " ms");
		System.out.println("Steps until convergence:" + numTotalAttempts + " steps");
	}

	//===============================================================================
	// Helper Methods
	//===============================================================================

	public boolean isSolution()
	{
		for(Constraint c : network.getConstraints())
		{
			if(!c.isConsistent())
			{
				return false;
			}
		}
		return true;
	}

	/**
	 * Restarts the local search after a predefined number of attempts. 
	 */
	public void restartCounter()
	{
		numTotalAttempts++;
		if (numAttempts++ > limitAttempts)
		{
			System.out.println("restart");
			numAttempts = 0;
			generateStartState();
		}
	}

	/**
	 * Assigns random values to each non-initial variable in the puzzle
	 */
	public void generateStartState()
	{
		for(Variable v : network.getVariables())
		{
			if(v.isChangeable())
			{
				v.assignValue((int)(Math.random()*n+1));
			}
		}
	}

	public void generateSuccessor()
	{
		List<Assignment> assignments = getAllPossibleAssignments();
		Assignment nextAssignment = assignments.get((int)(Math.random()*assignments.size()));
		network.pushAssignment(nextAssignment);
	}
	/**
	 * @return list of all possible Variable/Value assignments in the puzzle
	 */
	public List<Assignment> getAllPossibleAssignments()
	{
		List<Assignment> assignments = new ArrayList<Assignment>();
		for(Variable v : network.getVariables())
		{
			if(v.isChangeable())
			{
				for(int val = 1; val <= n; val++)
				{
					Assignment a = new Assignment (v, val);
					assignments.add(a);
				}
			}
		}
		return assignments;
	}

	private void success()
	{
		endTime = System.currentTimeMillis();
		System.out.println("Solution found!");
		sudokuGrid = Converter.ConstraintNetworkToSudokuFile(network, sudokuGrid.getN(), sudokuGrid.getP(), sudokuGrid.getQ());
	}

	public int getNetworkScore()
	{
		int networkScore = 0;
		for(Constraint c : network.getConstraints())
		{
			networkScore += c.getConflicts();
		}
		return networkScore;
	}

	//===============================================================================
	// Solver
	//===============================================================================

	public void solve()
	{
		if (!Thread.currentThread().isInterrupted())
		{
			startTime = System.currentTimeMillis();
			generateStartState();

			while(!isSolution())
			{
				restartCounter();
				generateSuccessor();
				//int score = getNetworkScore();
			}

			success();
		}
	}

	@Override
	public void run() {
		solve();
	}
}

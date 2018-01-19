package examples;

import sudoku.SudokuBoardGenerator;
import sudoku.SudokuFile;
import cspSolver.LocalSolver;

public class LocalSolverExample {

	public static void main(String[] args)
	{
		SudokuFile sf = SudokuBoardGenerator.generateBoard(16, 4, 4, 25);
		LocalSolver solver = new LocalSolver(sf);
		
		Thread t1 = new Thread(solver);
		try
		{
			t1.start();
			t1.join(60000);
			if(t1.isAlive())
			{
				t1.interrupt();
			}
		}catch(InterruptedException e)
		{
		}
		
		if(solver.hasSolution())
		{
			solver.printSolverStats();
			System.out.println(solver.getSolution());	
		}
		
		else
		{
			System.out.println("Failed to find a solution");
		}
		
	}
}

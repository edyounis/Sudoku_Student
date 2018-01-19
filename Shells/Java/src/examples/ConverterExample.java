package examples;

import sudoku.Converter;
import sudoku.SudokuBoardGenerator;
import sudoku.SudokuFile;
import cspSolver.ConstraintNetwork;

public class ConverterExample {

	public static void main(String[] args)
	{
		SudokuFile sf = SudokuBoardGenerator.generateBoard(16, 4, 4, 25);
		ConstraintNetwork cn = Converter.SudokuFileToConstraintNetwork(sf);
		
		System.out.println("*****************************************");
		System.out.println("below is a randomly generated SudokuFile:");
		System.out.println("*****************************************");
		System.out.println(sf);
		System.out.println("*****************************************");
		System.out.println("below is the constraint network representation of the above SudokuFile:");
		System.out.println("*****************************************");
		System.out.println(cn);


	}
}

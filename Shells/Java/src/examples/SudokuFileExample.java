package examples;

import sudoku.SudokuBoardGenerator;
import sudoku.SudokuBoardReader;
import sudoku.SudokuFile;

public class SudokuFileExample {

	public static void main(String[] args)
	{
		int N = 16;
		int p = 4;
		int q = 4;
		int m = 25;
		
		SudokuFile generatedSudokuFile = SudokuBoardGenerator.generateBoard(N, p, q, m);
		
		System.out.println("*****************************************");
		System.out.println("below is a randomly generated SudokuFile:");
		System.out.println("*****************************************");
		System.out.println(generatedSudokuFile);

		SudokuFile SudokuFileFromFile = SudokuBoardReader.readFile("ExampleSudokuFiles/PH5.txt");
		
		System.out.println("*****************************************");
		System.out.println("below is a SudokuFile generated from a file:");
		System.out.println("*****************************************");
		System.out.println(SudokuFileFromFile);
	}
}

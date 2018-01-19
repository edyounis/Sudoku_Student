package sudoku;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.io.Reader;


public class SudokuBoardReader {

	public static SudokuFile readFile(String filePath)
	{
		//Get filePath. from path and filename. If path is null, 
		//it'll default to the current directory

		try (Reader reader = new FileReader(filePath)) {
			try(BufferedReader br = new BufferedReader(reader)){
				SudokuFile sF = new SudokuFile();
				String line;
				int lineCounter = 0;

				while((line = br.readLine()) != null)
				{	
					String[] lineParts = line.split("\\s+");
					if(lineCounter == 0)
					{
						setSudokuFileParameters(sF, lineParts);//parameter line: contains p, q, N
					}
					else
					{
						parseLineOfSudokuBoard(sF, lineParts, lineCounter-1);//obo due to parameters taking up first line
					}
					lineCounter++;
				}
				if(lineCounter == 0)
				{
					System.out.println("Input file \""+filePath+"\" was empty");
				}
				else if(lineCounter < sF.getN())
				{
					System.out.println("Incomplete or Emtpy board for file " + filePath+". Please be advised");
				}
				return sF;
			} 
		} catch (IOException e1) {
			// TODO Auto-generated catch block
			System.err.print("Invalid file:"+filePath+". Skipping to the next file.\n");
		} catch (NumberFormatException e2) {
			e2.printStackTrace();
		}
		//Something wrong happened if it reaches here
		return new SudokuFile();
	}

	//helpers
	private static void setSudokuFileParameters(SudokuFile sf, String[] params) throws IOException
	{
		if(params.length != 3) throw new IOException("Params invalid in file.");
		sf.setN(Integer.parseInt(params[0]));
		sf.setP(Integer.parseInt(params[1]));
		sf.setQ(Integer.parseInt(params[2]));
	}
	
	private static void parseLineOfSudokuBoard(SudokuFile sf, String[] values, int rowNumber) 
	{
		//writes values to the row set in param rowNumber
		if(sf.getBoard() == null)
		{
			sf.setBoard(new int[sf.getN()][sf.getN()]);
		}
		int[][] board = sf.getBoard();
		for(int i = 0; i < values.length; i++)
		{
			board[rowNumber][i] = Odometer.odometerToInt(values[i]);
		}
	}
}
package sudoku;
import java.util.Arrays;


public class Odometer {
	public static int odometerToInt(String value) {
		int retVal = Arrays.binarySearch(ODOMETER, value.toUpperCase());
		if(retVal < 0)
		{
			System.err.println("odometerToInt failed. Invlaid value " + value + "Replaced with 0");
			retVal = 0;
		}
		return retVal;
	}
	
	public static String intToOdometer(int num)
	{
		String retVal;
		try{
			retVal = ODOMETER[num];
		}catch(IndexOutOfBoundsException e){
			System.err.println("intToOdometer failed. Invalid number " + num + " Replaced with 0");
			retVal = "0";
		}
		return retVal;
	}

	private static final String[] ODOMETER = 
		{"0","1","2","3","4","5","6","7","8","9",
		 "A","B","C","D","E","F","G","H","I","J",
		 "K","L","M","N","O","P","Q","R","S","T",
		 "U","V","W","X","Y","Z"};
}

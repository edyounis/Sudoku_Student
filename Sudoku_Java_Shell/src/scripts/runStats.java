package scripts;

public class runStats {

	private static int numStat = 1;
	private long runtime;
	private int numAssignments;
	private int numBacktracks;
	private boolean isSolution;
	
	private String puzzleID;
	
	public runStats(long runtime, int numAssignments, int numBacktracks, boolean isSolution)
	{
		this.runtime = runtime;
		this.numAssignments = numAssignments;
		this.numBacktracks = numBacktracks;
		this.isSolution = isSolution;
		this.puzzleID = "puzzle" + numStat++;
	}
	
	public long getRuntime() {
		return runtime;
	}


	public int getNumAssignments() {
		return numAssignments;
	}


	public int getNumBacktracks() {
		return numBacktracks;
	}


	public boolean isSolution() {
		return isSolution;
	}
	
	public String toString()
	{
		StringBuilder sb = new StringBuilder();
		sb.append(puzzleID + ":");
		sb.append(runtime + " ms, " + numAssignments + " assignments, " + numBacktracks + " backtracks" + (isSolution?"":" Not a Solution"));
		return sb.toString();
	}
}

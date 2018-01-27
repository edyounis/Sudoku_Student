package cspSolver;
/**
 * Assignments represent assigned variables and values associated with them.
 *   
 * @see LocalSolver
 */
public class Assignment implements Comparable<Assignment>{

	//===============================================================================
	// Properties
	//===============================================================================
	
	private Variable variable;
	private int value;
	private int score;
	
	//===============================================================================
	// Constructors
	//===============================================================================
	
	public Assignment(Variable v, int val)
	{
		this.variable = v;
		this.value = val;
	}
	
	public Assignment(Variable v, int val, int score)
	{
		this.variable = v;
		this.value = val;
		this.score = score;
	}
	
	//===============================================================================
	// Accessors
	//===============================================================================
	
	public Variable getVariable() {
		return variable;
	}

	public int getValue() {
		return value;
	}	
	
	public int getScore() {
		return score;
	}

	//===============================================================================
	// Modifiers
	//===============================================================================
	
	public void setValue(int val)
	{
		this.value = val;
	}
	
	public void setScore(int score)
	{
		this.score = score;
	}
	//===============================================================================
	// Comparable<Assignment>
	//===============================================================================
	
	@Override
	public int compareTo(Assignment a) {
		return this.score - a.score;
	}
	//===============================================================================
	// String Methods
	//===============================================================================
		
	public String toString()
	{
		StringBuilder sb = new StringBuilder();
		sb.append("Variable: " + variable.getName());
		sb.append("\tValue: " + value);
		sb.append("\tscore: " + score);
		
		return sb.toString();
		
	}
}

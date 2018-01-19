package cspSolver;

import java.util.EmptyStackException;
import java.util.Stack;

/**
 * Represents the trail of changes made. This allows backtracking to occur. 
 * Trail follows the singleton design pattern. 
 */
public class Trail {
	
	//===============================================================================
	// Properties
	//===============================================================================
	
	private static Stack<Object[]> trail = new Stack<Object[]>();
	private static final Trail TRAIL = new Trail();
	private static Stack<Integer> breadcrumbs = new Stack<Integer>();
	private Trail()
	{}
	
	/**
	 * returns the trail.
	 * @return
	 */
	public static Trail getTrail()
	{
		return TRAIL;
	}
	
	public static void clearTrail()
	{
		trail.clear();
	}
	//===============================================================================
	// Accessors
	//===============================================================================
	
	public int size()
	{
		return trail.size();
	}
	
	//===============================================================================
	// Modifiers
	//===============================================================================
	
	/**
	 * places a marker at the current point in the trail. Each time undo is called, the 
	 * latest marker is popped and the trail 
	 */
	public void placeBreadCrumb()
	{
		breadcrumbs.add(trail.size());
	}
	/**
	 * Adds a deep copy of a variable and its domain onto the trail.
	 * @param v Variable to copy onto the trail
	 */
	public void push(Variable v)
	{
		Object[] vPair = { v, new Domain(v.getDomain())};
		trail.push(vPair);
	}
	
	/**
	 * Pops changes pushed onto the trail until it reaches the latest marker. 
	 * Also pops the latest marker. 
	 * @param targetSize target position on the trail to backtrack to
	 * @throws EmptyStackException if trail is empty
	 */
	public void undo() throws EmptyStackException 
	{
		int targetSize = breadcrumbs.pop();
		for (int size = trail.size(); size > targetSize; size--)
		{
			Object[] vPair = trail.pop();
			Variable v = (Variable) vPair[0];
			v.setDomain((Domain) vPair[1]);
		}
	}
}


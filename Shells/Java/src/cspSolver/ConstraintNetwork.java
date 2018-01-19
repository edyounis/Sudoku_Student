package cspSolver;

import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

/**
 * CSP representation of the problem. Contains the variables, constraints, and 
 * many helpful accessors. 
 *
 */
public class ConstraintNetwork {
	
	//===============================================================================
	// Properties
	//===============================================================================
	
	private List<Constraint> constraints;
	private List<Variable> variables;
	
	//===============================================================================
	// Constructor 
	//===============================================================================
	
	public ConstraintNetwork()
	{
		variables = new ArrayList<Variable>();
		constraints = new ArrayList<Constraint>();
	}
	
	//===============================================================================
	// Modifiers
	//===============================================================================
	
	public void add(Constraint c)
	{
		if (!constraints.contains(c))
		{
			constraints.add(c);
		}
	}
	
	public void add(Variable v)
	{
		if(!variables.contains(v))
		{
			variables.add(v);
		}
	}
	
	/**
	 * Used for Local Search. Assigns a value to a variable based on the parameter a
	 * @param a Assignment to actualize 
	 */
	public void pushAssignment(Assignment a) {
		a.getVariable().assignValue(a.getValue());
	}
	
	//===============================================================================
	// Accessors
	//===============================================================================
	
	public List<Constraint> getConstraints()
	{
		return constraints;
	}
	
	public List<Variable> getVariables()
	{
		return variables;
	}
	
	public List<Variable> getNeighborsOfVariable(Variable v)
	{
		Set<Variable> neighbors = new HashSet<Variable>();
		
		for(Constraint c : constraints)
		{
			if(c.contains(v))
			{
				neighbors.addAll(c.vars);
			}
		}
		neighbors.remove(v);
		return new ArrayList<Variable>(neighbors);
	}
	
	/**
	 * Used for local search. Determines if the current assignment is consistent.
	 * @return
	 */
	public boolean isConsistent()
	{
		for (Constraint c : constraints)
		{
			if (!c.isConsistent())
			{
				return false;
			}
		}
		return true;
	}
	
	/**
	 * @param v variable to check
	 * @return list of constraints that contains v
	 */
	public List<Constraint> getConstraintsContainingVariable(Variable v)
	{
		List<Constraint> outList = new ArrayList<Constraint>();
		for(Constraint c : constraints)
		{
			if(c.contains(v))
			{
				outList.add(c);
			}
		}
		return outList;
	}
	
	/**
	 * Returns the constraints that contain variables whose domains were 
	 * modified since the last call to this method. 
	 * 
	 * After getting the constraints, it will reset each variable to
	 * unmodified.
	 * 
	 * Note* The first call to this method returns the constraints containing
	 * the initialized variables. 
	 * 
	 * @return ArrayList of modified constraints
	 */
	public List<Constraint> getModifiedConstraints()
	{
		List<Constraint> mConstraints = new ArrayList<Constraint>();

		for (Constraint c : constraints)
		{
			if (c.isModified())
			{
				mConstraints.add(c);
			}
		}

		for (Variable v : getVariables())
		{
			v.setModified(false);
		}
		return mConstraints;
	}

	//===============================================================================
	// String Representation 
	//===============================================================================
	
	public String toString()
	{
		StringBuilder sb = new StringBuilder();
		sb.append(variables.size() + " Variables: {");
		String delim = "";
		
		for (Variable v : variables)
		{
			sb.append(delim).append(v.getName());
			delim = ",";
		}
		sb.append("}");
		
		sb.append("\n" + constraints.size() + " Constraints:");
		delim = "\n";
		for (Constraint c: constraints)
		{
			sb.append(delim).append(c.toString());
		}
		return sb.toString();
	}
}

package cspSolver;

import java.util.ArrayList;
import java.util.List;

/**
 * Constraint represents a NotEquals constraint on a set of variables. 
 * Used to ensure none of the variables contained in the constraint have the same assignment. 
 */
public class Constraint{ 
	
	//===============================================================================
	// Properties 
	//===============================================================================

	public List<Variable> vars;

	//===============================================================================
	// Constructors
	//===============================================================================

	public Constraint()
	{
		vars = new ArrayList<Variable>();
	}
	
	public Constraint(List<Variable> vars)
	{
		this.vars = vars;
	}
	
	//===============================================================================
	// Modifiers
	//===============================================================================

	public void addVariable(Variable v)
	{
		vars.add(v);
	}
		
	//===============================================================================
	// Accessors
	//===============================================================================
	
	public int size()
	{
		return vars.size();
	}
	
	/**
	 * 
	 * @param v a Variable
	 * @return true if v is in the constraint, false otherwise
	 */
	public boolean contains(Variable v)
	{
		return vars.contains(v) ? true: false;
	}
	
	/**
	 * Returns whether or not the a variable in the constraint has been modified.
	 * 
	 * @return
	 */
	public boolean isModified()
	{
		for (Variable var : vars)
		{
			if (var.isModified())
			{
				return true;
			}
		}
		return false;
	}

	/**
	 * Used for local search
	 * @return
	 */
	public int getConflicts()
	{
		int numConflicts = 0;
		for(Variable var : vars)
		{
			for (Variable otherVar : vars)
			{
				if(var.equals(otherVar))
				{
					continue;
				}
				else if(var.getAssignment().equals(otherVar.getAssignment()))
				{
					numConflicts++;
				}
			}
		}
		
		return numConflicts;
	}
	
	//===============================================================================
	// Modifiers
	//===============================================================================
	
	/**
	 * Attempts to propagate the notequal constraint through the variables in 
	 * the constraint. If it fails to do so, the propagation stops midway
	 * and does not reset the changes to the domains of the variables made
	 * so far. 
	 * @return true if the constraint is consistent and propagation succeeds, 
	 * false otherwise
	 */
	public boolean propagateConstraint()
	{
		//compares assignments and determines if the assigment breaks the constraints
		for(Variable var : vars)
		{
			if(!var.isAssigned())
				continue;
			Integer varAssignment = var.getAssignment();
			for (Variable otherVar : vars)
			{
				if(var.equals(otherVar))
				{
					continue;
				}
				if (otherVar.size() == 1 && otherVar.getAssignment() == varAssignment)
				{
					return false;
				}
				otherVar.removeValueFromDomain(varAssignment);
			}
		}
		return true;
	}
	
	/**
	 * Used for local search. Same as propagate constraint. 
	 * @return true if constraint is consistent, false otherwise. 
	 */
	public boolean isConsistent()
	{
		return propagateConstraint();
	}

	//===============================================================================
	// String representation
	//===============================================================================
	
	public String toString()
	{
		StringBuilder sb = new StringBuilder("{");
		String delim = "";
		for(Variable v : vars)
		{
			sb.append(delim).append(v.getName());
			delim = ",";
		}
		sb.append("}");
		return sb.toString();
	}

	
}

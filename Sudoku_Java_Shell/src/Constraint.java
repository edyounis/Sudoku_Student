import java.util.ArrayList;
import java.util.List;

/**
 * Constraint represents a NotEquals constraint on a set of variables.
 * Used to ensure none of the variables contained in the constraint have the same assignment.
 */

public class Constraint
{

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

	public Constraint ( List<Variable> vars )
	{
		this.vars = vars;
	}

	//===============================================================================
	// Modifiers
	//===============================================================================

	public void addVariable ( Variable v )
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

	public boolean contains ( Variable v )
	{
		return vars.contains(v) ? true : false;
	}

	public boolean isModified()
	{
		for ( Variable var : vars )
		{
			if ( var.isModified() )
			{
				return true;
			}
		}
		return false;
	}

	public int getConflicts()
	{
		int numConflicts = 0;
		for ( Variable var : vars )
		{
			for ( Variable otherVar : vars )
			{
				if ( var.equals(otherVar) )
					continue;

				if ( var.getAssignment().equals(otherVar.getAssignment()) )
					numConflicts++;
			}
		}

		return numConflicts;
	}

	public boolean isConsistent()
	{
		for ( Variable var : vars )
		{
			if ( ! var.isAssigned() )
				continue;

			for ( Variable otherVar : vars )
			{
				if ( var.equals( otherVar ) )
					continue;

				if ( otherVar.isAssigned()
				     && otherVar.getAssignment() == var.getAssignment() )
					return false;
			}
		}

		return true;
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

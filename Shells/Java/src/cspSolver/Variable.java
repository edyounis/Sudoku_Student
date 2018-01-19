package cspSolver;

import java.util.Iterator;
import java.util.List;

public class Variable implements Iterable<Integer> 
{
	//===============================================================================
	// Properties
	//===============================================================================
	
	private static int namingCounter = 1;
	private Domain domain;	
	private int row, col, block;
	private boolean modified;
	private boolean unchangeable;
	private String name;
	private static Trail trail = Trail.getTrail();
	
	private int oldSize;
	
	//===============================================================================
	// Constructors
	//===============================================================================
	
	public Variable(List<Integer> possible_Values, int row, int col, int block)
	{	
		this.domain = new Domain(possible_Values);
		if (size() == 1)
		{
			modified = true;
			unchangeable = true;
		}
		this.row = row;
		this.col = col;
		this.block = block;
		this.name = "v" + namingCounter++;
		this.oldSize = size();
	}
	
	public Variable(Variable v)
	{
		this.domain = v.domain;
		this.row = v.row;
		this.col = v.col;
		this.block = v.block;
		this.modified = v.modified;
		this.name = v.name;
	}
	
	//===============================================================================
	// Accessors
	//===============================================================================
	
	/**
	 * Used for local search. Used to differentiate between intialized assignments
	 * and user assignments.
	 * @return false if this variable was assigned at initialization.
	 */
	public boolean isChangeable()
	{
		return !unchangeable;
	}
	
	public boolean isAssigned()
	{
		return size() == 1 ? true : false;
	}
	
	public boolean isModified()
	{
		return modified;
	}
	
	public void setModified(boolean modified)
	{
		this.modified = modified;
		this.domain.setModified(modified);
	}
	
	public int row()
	{
		return row;
	}
	
	public int col()
	{
		return col;
	}
	
	public int block()
	{
		return block;
	}
	
	/**
	 * Returns the value currently assigned to the IntVariable.
	 * If the IntVariable is currently unassigned, returns 0
	 * @return 0 if IntVariable is unassigned, Assignment otherwise
	 */
	public Integer getAssignment()
	{
		if (!this.isAssigned())
		{
			return 0;
		}
		else
		{
			return domain.getValues().get(0);
		}
	}
	
	public List<Integer> Values()
	{
		return domain.getValues();
	}
	
	public int size()
	{
		return domain.size();
	}
	
	public Domain getDomain()
	{
		return domain;
	}
	
	public String getName()
	{
		return name;
	}
	
	//===============================================================================
	// Modifiers
	//===============================================================================
	
	/** 
	 * Used for local Search
	 * @param val new assignment
	 */
	public void assignValue(int val)
	{
		setDomain(new Domain(val));
	}
	
	/**
	 * Used for Backtracking. Adds the changed domain to the Trail.
	 * @param d new domain
	 */
	public void updateDomain(Domain d)
	{
		methodModifiesDomain();
		
		if(!domain.equals(d))
		{
			domain = d;
			modified = true;
		}
	}
	
	/**
	 * Performs a change to the domain without changing the Trail.
	 * @param d new domain 
	 */
	public void setDomain(Domain d)
	{
		if(!domain.equals(d))
		{
			domain = d;
			modified = true;
		}
	}
	
	/**
	 * Removes a single value from the domain of V.
	 * @param val value to remove
	 */
	public void removeValueFromDomain(int val) {
		methodModifiesDomain();
		domain.remove(val);
		this.modified=domain.isModified();
	}
	
	//===============================================================================
	// Helper Methods
	//===============================================================================
	
	public void methodModifiesDomain()
	{
		int newSize = size();
		if (oldSize > newSize)
		{
			oldSize = newSize;
		}
			
		trail.push(this);
	}
	
	//===============================================================================
	// Iterator
	//===============================================================================
	
	@Override
	public Iterator<Integer> iterator() {
		return domain.iterator();
	}
	
	//===============================================================================
	// String Representation
	//===============================================================================
	public String toString()
	{
		//prints node stats
		StringBuilder sb = new StringBuilder();
		sb.append(" Name: "+name);
		sb.append("\tdomain: {");
		for(Integer i : domain)
		{
			sb.append(i + ",");	
		}
		sb.deleteCharAt(sb.length()-1);
		sb.append("}");
		return sb.toString();
	}

	
}

package cspSolver;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

/**
 * Represents the domain of a variable, i.e. the possible values that each
 * variable may assign. 
 */
public class Domain implements Iterable<Integer>{
	
	//===============================================================================
	// Properties
	//===============================================================================
	
	private ArrayList<Integer> values = new ArrayList<Integer>();
	private boolean modified;
	
	//===============================================================================
	// Constructors
	//===============================================================================
	
	/**
	 * Constructs a domain with a single value
	 * @param value the sole value within the domain
	 */
	public Domain(int value)
	{
		values.add(value);
	}
	
	/**
	 * Constructs a domain with an array of values
	 * @param values all possible values for the domain
	 */
	public Domain(int[] values)
	{
		for(int i = 0; i < values.length; i++)
		{
			this.values.add(values[i]);
		}
	}
	
	/**
	 * Constructs a domain with an ArrayList<Integer> of values
	 * @param values all possible values for the domain
	 */
	public Domain(List<Integer> values)
	{
		this.values.clear();
		this.values.addAll(values);
	}
	
	/**
	 * Copy Constructor. Used to keep a copy of assignments in the Trail.
	 * @param d the domain to copy
	 * @see Trail
	 */
	public Domain(Domain d)
	{
		for(Integer value : d.getValues())
		{
			this.values.add(value);
		}
	}
	
	//===============================================================================
	// Accessors
	//===============================================================================
	
	/**
	 * *Note, Domain is iterable. You can use
	 * 	for(Integer i : Domain)
	 *  {
	 *  	...
	 *  }
	 *  
	 * @return ArrayList of values in Domain
	 */
	public ArrayList<Integer> getValues()
	{
		return values;
	}
	
	/**
	 * Checks if a value exists within the domain
	 * @param value to check
	 * @return true if <tt>value</tt> exists within the domain, false otherwise.
	 */
	public boolean contains(int value)
	{
		if (values.contains(value))
		{
			return true;
		}
		return false;
	}
	
	/** 
	 * @return number of values in the domain
	 */
	public int size()
	{
		return values.size();
	}
	
	/**
	 * @return true if no values are contained in the domain. 
	 */
	public boolean isEmpty()
	{
		return values.isEmpty();
	}
	
	/**
	 * Returns whether or not the domain has been modified.
	 * 
	 * @return true if the domain has been modified
	 */
	public boolean isModified()
	{
		return modified;
	}
	
	//===============================================================================
	// Modifiers
	//===============================================================================

	/**
	 * Removes <tt>value</tt> from the domain.
	 * @param value the int to be removed
	 */
	public boolean remove(int value)
	{
		Integer v = value;
		
		if(!contains(value))
		{
			return false;
		}
		
		setModified(true);
		values.remove(v);
		return true;
	}
	
	/**
	 * Sets modified flag.
	 * @param modified value to set the modified flag. 
	 */
	public void setModified(boolean modified)
	{
		this.modified = modified;
	}

	//===============================================================================
	// Iterator
	//===============================================================================
	
	@Override
	public Iterator<Integer> iterator() {
		return values.iterator();
	}
	
	//===============================================================================
	// String representation
	//===============================================================================
	
	public String toString()
	{
		StringBuilder sb = new StringBuilder("{");
		String delim = "";
		for (Integer i : values)
		{
			sb.append(delim).append(i);
			delim = ",";
		}
		sb.append("}");
		return sb.toString();
	}
}


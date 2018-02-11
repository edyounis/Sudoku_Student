import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

/**
 * Represents the domain of a variable, i.e. the possible values that each
 * variable may assign.
 */

public class Domain implements Iterable<Integer>
{

	// =================================================================
	// Properties
	// =================================================================

	private ArrayList<Integer> values = new ArrayList<Integer>();
	private boolean modified;

	// =================================================================
	// Constructors
	// =================================================================

	// Constructs a domain with a single value
	public Domain ( int value )
	{
		values.add(value);
	}

	// Constructs a domain with an array of values
	public Domain ( int[] values )
	{
		for ( int i = 0; i < values.length; ++i )
		{
			this.values.add( values[i] );
		}
	}

	// Constructs a domain from a list of values
	public Domain ( List<Integer> values )
	{
		this.values.clear();
		this.values.addAll( values );
	}

	// Copy Constructor
	public Domain ( Domain d )
	{
		for ( Integer value : d.getValues() )
		{
			this.values.add( value );
		}
	}

	// =================================================================
	// Accessors
	// =================================================================

	// Note, Domain is iterable. You can use "for ( Integer i : Domain )"
	public ArrayList<Integer> getValues()
	{
		return values;
	}

	// Checks if value exists within the domain
	public boolean contains ( int value )
	{
		if ( values.contains( value ) )
			return true;

		return false;
	}

	// Returns number of values in the domain
	public int size ( )
	{
		return values.size();
	}

	// Returns true if no values are contained in the domain
	public boolean isEmpty ( )
	{
		return values.isEmpty();
	}

	// Returns whether or not the domain has been modified
	public boolean isModified()
	{
		return modified;
	}

	// =================================================================
	// Modifiers
	// =================================================================

	// Adds a value to the domain
	public void add ( int value )
	{
		if ( ! contains( value ) )
			this.values.add( value );
	}

	// Remove a value from the domain
	public boolean remove ( int value )
	{
		Integer v = value;

		if ( ! contains( value ) )
			return false;

		setModified( true );
		values.remove( v );
		return true;
	}

	// Sets the modified flag
	public void setModified ( boolean modified )
	{
		this.modified = modified;
	}

	// =================================================================
	// Iterator
	// =================================================================

	@Override
	public Iterator<Integer> iterator ( )
	{
		return values.iterator();
	}

	// =================================================================
	// String representation
	// =================================================================

	public String toString ( )
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


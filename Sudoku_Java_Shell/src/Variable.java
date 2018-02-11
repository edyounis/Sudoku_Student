import java.util.Iterator;
import java.util.List;

/**
 * Represents a variable in a CSP
 */

public class Variable implements Iterable<Integer>
{
	// =================================================================
	// Properties
	// =================================================================

	private static int namingCounter = 1;
	private Domain domain;
	private int row, col, block;
	private boolean modified;
	private boolean changeable;
	private String name;

	private int oldSize;

	// =================================================================
	// Constructors
	// =================================================================

	public Variable ( List<Integer> possible_Values, int row, int col, int block )
	{
		this.domain = new Domain( possible_Values );
		if ( size() == 1 )
		{
			modified = true;
			changeable = false;
		}
		this.row = row;
		this.col = col;
		this.block = block;
		this.name = "v" + namingCounter++;
		this.oldSize = size();
		this.changeable = true;
	}

	public Variable ( Variable v )
	{
		this.domain = v.domain;
		this.row = v.row;
		this.col = v.col;
		this.block = v.block;
		this.modified = v.modified;
		this.name = v.name;
		this.changeable = v.changeable;
	}

	// =================================================================
	// Accessors
	// =================================================================

	public boolean isChangeable ( )
	{
		return changeable;
	}

	public boolean isAssigned ( )
	{
		return size() == 1;
	}

	public boolean isModified ( )
	{
		return modified;
	}

	public int row ( )
	{
		return row;
	}

	public int col ( )
	{
		return col;
	}

	public int block ( )
	{
		return block;
	}

	public int size ( )
	{
		return domain.size();
	}

	// Returns the assigned value or 0 if unassigned
	public Integer getAssignment ( )
	{
		if ( isAssigned() )
			return domain.getValues().get( 0 );

		return 0;
	}

	public Domain getDomain ( )
	{
		return domain;
	}

	public String getName ( )
	{
		return name;
	}

	public List<Integer> getValues ( )
	{
		return domain.getValues();
	}

	// =================================================================
	// Modifiers
	// =================================================================


	public void setModified ( boolean modified )
	{
		if ( ! changeable )
			return;

		this.modified = modified;
		this.domain.setModified( modified );
	}

	// Assign a value to the variable
	public void assignValue ( int val )
	{
		if ( ! changeable )
			return;

		setDomain( new Domain( val ) );
	}

	// Sets the domain of the variable
	public void setDomain ( Domain d )
	{
		if ( ! changeable )
			return;

		if ( ! domain.equals( d ) )
		{
			domain = d;
			modified = true;
		}
	}

	// Removes a value from the domain
	public void removeValueFromDomain ( int val )
	{
		if ( ! changeable )
			return;

		domain.remove( val );
		this.modified = domain.isModified();
	}

	// =================================================================
	// Iterator
	// =================================================================

	@Override
	public Iterator<Integer> iterator()
	{
		return domain.iterator();
	}

	// =================================================================
	// String Representation
	// =================================================================

	public String toString ( )
	{
		//prints node stats
		StringBuilder sb = new StringBuilder();
		sb.append(" Name: "+name);
		sb.append("\tdomain: {");

		for ( Integer i : domain )
			sb.append(i + ",");

		sb.deleteCharAt(sb.length()-1);
		sb.append("}");
		return sb.toString();
	}
}

import java.util.EmptyStackException;
import java.util.Stack;

/**
 * Represents the trail of changes made. This allows backtracking to occur.
 */

public class Trail
{
	// =================================================================
	// Properties
	// =================================================================

	private Stack<Object[]> trailStack  = new Stack<Object[]>();
	private Stack<Integer>  trailMarker = new Stack<Integer>();

	private static int numPush = 0;
	private static int numUndo = 0;

	// =================================================================
	// Constructor
	// =================================================================

	public Trail ( )
	{
	}

	// =================================================================
	// Accessors
	// =================================================================

	public int size ( )
	{
		return trailStack.size();
	}

	public static int getPushCount ( )
	{
		return numPush;
	}

	public static int getUndoCount ( )
	{
		return numUndo;
	}

	// =================================================================
	// Modifiers
	// =================================================================

	// Places a marker in the trail
	public void placeTrailMarker ( )
	{
		trailMarker.add( trailStack.size() );
	}

	/**
	 * Before you assign a variable in constraint propagation,
	 * use this function to save its initial domain on the
	 * backtrack trail. This way if the path you are on fails,
	 * you can restore propagated domains correctly.
	 */

	public void push ( Variable v )
	{
		numPush++;
		Object[] vPair = { v, new Domain( v.getDomain() )};
		trailStack.push( vPair );
	}

	// Pops and restores variables on the trail until the last trail marker
	public void undo ( )
	{
		numUndo++;
		try
		{
			int targetSize = trailMarker.pop();
			for ( int size = trailStack.size(); size > targetSize; --size )
			{
				Object[] vPair = trailStack.pop();
				Variable v = (Variable) vPair[0];
				v.setDomain((Domain) vPair[1]);
				v.setModified( false );
			}
		}
		catch ( EmptyStackException e )
		{
			clear();
		}
	}

	// Clears the trail
	public void clear ( )
	{
		trailStack.clear();
		trailMarker.clear();
	}
}


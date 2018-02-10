#include "Trail.hpp"

using namespace std;

// Constructor
Trail::Trail ( void )
{
	numPush = 0;
	numUndo = 0;
}

// Accessors
int Trail::size ( void )
{
	return trailStack.size();
}

int Trail::getPushCount ( void )
{
	return numPush;
}

int Trail::getUndoCount ( void )
{
	return numUndo;
}

// Modifiers
void Trail::placeTrailMarker ( void )
{
	trailMarker.push( trailStack.size() );
}

void Trail::push ( Variable* v )
{
	numPush++;
	trailStack.push( pair<Variable*, Domain>( v, v->getDomain() ) );
}

void Trail::undo ( void )
{
	numUndo++;
	int targetSize = trailMarker.top();
	trailMarker.pop();
	for ( int size = trailStack.size(); size > targetSize; --size )
	{
		pair<Variable*, Domain> vPair = trailStack.top();
		trailStack.pop();
		vPair.first->setDomain(vPair.second);
	}
}

void Trail::clear ( void )
{
	while ( ! trailStack.empty() )
		trailStack.pop();

	while ( ! trailMarker.empty() )
		trailMarker.pop();
}
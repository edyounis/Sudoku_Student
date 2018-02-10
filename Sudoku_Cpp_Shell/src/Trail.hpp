#ifndef TRAIL_HPP
#define TRAIL_HPP

#include "Domain.hpp"
#include "Variable.hpp"

#include <stack>
#include <utility>
#include <iostream>

class Trail
{
public:

	// Constructor
	Trail ( void );

	// Accessors
	int size ( void );
	int getPushCount ( void );
	int getUndoCount ( void );

	// Modifiers
	void placeTrailMarker ( void );
	void undo ( void );

	/**
	 * Before you assign a variable in constraint propagation,
	 * use this function to save its initial domain on the
	 * backtrack trail. This way if the path you are on fails,
	 * you can restore propagated domains correctly.
	 */

	void push ( Variable* v );

	void clear ( void );

private:

	std::stack<std::pair<Variable*, Domain> > trailStack;
	std::stack<int> trailMarker;

	int numPush;
	int numUndo;
};

#endif
#ifndef CONSTRAINT_HPP
#define CONSTRAINT_HPP

#include "Domain.hpp"
#include "Variable.hpp"

#include <vector>
#include <sstream>
#include <algorithm>

class Constraint
{
public:
	// Typedefs
	typedef typename std::vector< Variable* > VariableSet;

	// Properties
	VariableSet vars;

	// Constructors
	Constraint ( void );
	Constraint ( VariableSet vars );

	// Modifiers
	void addVariable ( Variable* v );

	// Accessors
	int  size         ( void );
	bool contains     ( Variable* v );
	bool isModified   ( void );
	int  getConflicts ( void );

	// Modifiers
	/**
	 * Attempts to propagate the notequal constraint through the variables in
	 * the constraint. If it fails to do so, the propagation stops midway
	 * and does not reset the changes to the domains of the variables made
	 * so far.
	 * @return true if the constraint is consistent and propagation succeeds,
	 * false otherwise
	 */
	bool propagateConstraint ( void );

	/**
	 * @return true if constraint is consistent, false otherwise.
	 */
	bool isConsistent ( void );

	bool operator== ( const Constraint &other ) const;

	std::string toString ( void );
};

#endif

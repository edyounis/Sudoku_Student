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
	bool isConsistent ( void );

	bool operator== ( const Constraint &other ) const;

	std::string toString ( void );
};

#endif

#ifndef CONSTRAINTNETWORK_HPP
#define CONSTRAINTNETWORK_HPP

#include "Domain.hpp"
#include "Variable.hpp"
#include "Constraint.hpp"
#include "Assignment.hpp"
#include "SudokuBoard.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <unordered_set>
#include <map>
#include <utility>

class ConstraintNetwork
{
public:
	// Typedefs
	typedef typename std::vector< Constraint* > ConstraintRefSet;
	typedef typename std::vector< Constraint > ConstraintSet;
	typedef typename std::vector< Variable* > VariableSet;


	// Constructors
	ConstraintNetwork ( void );
	ConstraintNetwork ( SudokuBoard sboard );

	// Modifiers
	void add ( Constraint c );
	void add ( Variable* v );

	void pushAssignment ( Assignment a );

	// Accessors
	ConstraintSet getConstraints ( void ) const;
	VariableSet   getVariables   ( void ) const;

	VariableSet getNeighborsOfVariable ( Variable* v );

	bool isConsistent ( void ) const;

	/**
	 * @param v variable to check
	 * @return list of constraints that contains v
	 */
	ConstraintRefSet getConstraintsContainingVariable ( Variable* v );

	/**
	 * Returns the constraints that contain variables whose domains were
	 * modified since the last call to this method.
	 *
	 * After getting the constraints, it will reset each variable to
	 * unmodified.
	 *
	 * Note* The first call to this method returns the constraints containing
	 * the initialized variables.
	 *
	 * @return ArrayList of modified constraints
	 */
	ConstraintRefSet getModifiedConstraints ( void );

	SudokuBoard toSudokuBoard ( int _p, int _q ) const;

	std::string toString ( void ) const;

private:
	ConstraintSet constraints;
	VariableSet variables;
};

#endif

#ifndef CONSTRAINT_HPP
#define CONSTRAINT_HPP

#include"Variable.hpp"
#include<vector>
#include<sstream>
#include<algorithm>

class Constraint
{
	// Properties
public:
    std::vector<Variable*> vars;

	// Constructors

    Constraint();
    Constraint(std::vector<Variable*> vars);
    
    bool operator==(const Constraint &other) const;

	// Modifiers
    void addVariable(Variable* v);

	// Accessors
    int size();

	/**
	 * 
	 * @param v a Variable
	 * @return true if v is in the constraint, false otherwise
	 */
    bool contains(Variable* v);

	/**
	 * Returns whether or not the a variable in the constraint has been modified.
	 * 
	 * @return
	 */
    bool isModified();

	/**
	 * Used for local search
	 * @return
	 */
    int getConflicts();

	//===============================================================================
	// Modifiers
	//===============================================================================
	/**
	 * Attempts to propagate the notequal constraint through the variables in 
	 * the constraint. If it fails to do so, the propagation stops midway
	 * and does not reset the changes to the domains of the variables made
	 * so far. 
	 * @return true if the constraint is consistent and propagation succeeds, 
	 * false otherwise
	 */
    bool propagateConstraint();

	/**
	 * Used for local search. Same as propagate constraint. 
	 * @return true if constraint is consistent, false otherwise. 
	 */
    bool isConsistent();

	//===============================================================================
	// String representation
	//===============================================================================
    std::string toString();
};

#endif

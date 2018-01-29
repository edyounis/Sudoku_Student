#ifndef ASSIGNMENT_HPP
#define ASSIGNMENT_HPP

#include "Domain.hpp"
#include "Variable.hpp"

#include <sstream>

class Assignment
{
public:
	// Constructors
	Assignment ( Variable* v, int val );
	Assignment ( Variable* v, int val, int score );

	// Accessors
	Variable* getVariable ( void );

	int getValue ( void ) const;
	int getScore ( void ) const;

	// Modifiers
	void setValue ( int val );
	void setScore ( int score );

	// Comparable<Assignment>
	int compareTo ( Assignment a );


	// String Methods
	std::string toString ( void );

private:
	Variable* variable;
	int value;
	int score;
};

#endif

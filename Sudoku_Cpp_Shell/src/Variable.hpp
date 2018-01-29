#ifndef VARIABLE_HPP
#define VARIABLE_HPP

#include "Domain.hpp"

#include <iterator>
#include <sstream>
#include <vector>
#include <stack>
#include <utility>
#include <iostream>
#include <algorithm>

class Variable
{
public:
	// Properties
	Domain domain;
	int r, c, b;
	bool modified;
	bool unchangeable;
	std::string name;
	int oldSize;
	static int namingCounter;

	// Constructors
	Variable ( Domain::ValueSet possible_Values, int row, int col, int block );
	Variable ( const Variable& v );

	bool operator== ( const Variable &other ) const;
	bool operator!= ( const Variable &other ) const;

	// Accessors
	bool isChangeable ( void ) const;
	bool isAssigned   ( void ) const;
	bool isModified   ( void ) const;

	int row   ( void ) const;
	int col   ( void ) const;
	int block ( void ) const;
	int size  ( void ) const;

	int getAssignment   ( void ) const;
	Domain getDomain    ( void ) const;
	std::string getName ( void ) const;
	Domain::ValueSet getValues ( void ) const;

	// Modifiers
	void modify ( const Variable& other );
	void setModified ( bool modified );
	void assignValue ( int val );
	void updateDomain ( Domain d );
	void setDomain ( Domain d );
	void removeValueFromDomain ( int val );

	// Iterator
	Domain::iterator begin();
	Domain::iterator end();

	// String Representation

	std::string toString ( void );

private:
	void methodModifiesDomain ( void );
};

#endif
